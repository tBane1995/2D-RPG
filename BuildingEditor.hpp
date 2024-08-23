#ifndef BuildingEditor_hpp
#define BuildingEditor_hpp

enum class buildingEditorStates { start, editor };
buildingEditorStates buildingEditorState;
Terrain* terrain;
Floors* floors;

void buildingEditorEventLeftClick();
void buildingEditorEventRightClick();
void saveBuildingToFile();
void addPrefabToLists();

void buildingEditor() {

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    buildingEditorState = buildingEditorStates::start;

    sf::Text* welcomeText = new sf::Text("Building Editor", basicFont, 32);
    welcomeText->setFillColor(titleColor);
    welcomeText->setOrigin(welcomeText->getLocalBounds().width / 2.f, welcomeText->getLocalBounds().height / 2.f);
    welcomeText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* pressText = new sf::Text("press Spacebar to start", basicFont, 16);
    pressText->setFillColor(titleColor);
    pressText->setOrigin(pressText->getLocalBounds().width / 2.f, pressText->getLocalBounds().height / 2.f);
    pressText->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            break;
        }

        window->setView(cam->view);
        welcomeText->setPosition(cam->position.x, cam->position.y - 50);
        pressText->setPosition(cam->position.x, cam->position.y + 50);

        window->clear(sf::Color::Black);
        window->draw(*welcomeText);
        window->draw(*pressText);
        window->display();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

    buildingEditorState = buildingEditorStates::editor;

    terrain = new Terrain(0, 0, 24, 24);
    floors = new Floors(0, 0, 24, 24);

    cam->setPosition(terrain->width/2*tileSide, terrain->height/2*tileSide);

    prefabToPaint = nullptr;
    createBuildingEditorPalette();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            GUIwasHover = false;
            GUIwasClicked = false;

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }

            if (buildingEditorState == buildingEditorStates::editor) {
                
                if (event.type == sf::Event::MouseButtonPressed) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        buildingEditorEventLeftClick();
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        // DELETE GAMEOBJECTS OR FLOORS
                        buildingEditorEventRightClick();
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                        saveBuildingToFile();
                    }
                }
            }
        }

        // UPDATE ///////////////////////////////////////////////////////////////////////

        // calculate delta time
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        if (!GUIwasClicked) {

            if (prefabToPaint != nullptr) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (prefabToPaint->type == gameObjectType::Floor) {
                        floors->edit(worldMousePosition, dynamic_cast<FloorPrefab*>(prefabToPaint));
                    }
                }
            }
        }

        
        updateGameObjects();
        sortGameObjects();
        updatePalette();

        cam->update();
        
        // PALETTE
        for (auto& p : palette) {
            if (p.mouseOvering(worldMousePosition))
                GUIwasHover = true;
        }

        // A PAINTER
        if (prefabToPaint != nullptr) {

            if (prefabToPaint->type != gameObjectType::Floor) {

                // PAINTER USE TO ADD GAMEOBJECT
                prefabToPaint->position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
                prefabToPaint->position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
                prefabToPaint->update(dt);
                prefabToPaint->mouseIsOver = false;
            }
            else {

                // PAINTER USE TO EDIT TERRAIN
                sf::Vector2f position;
                position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
                position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);


                prefabToPaint->collider->shape->setFillColor(sf::Color::Transparent);
                prefabToPaint->collider->shape->setPosition(position);
                prefabToPaint->collider->shape->setOutlineThickness(2.0f);
                prefabToPaint->collider->shape->setOutlineColor(sf::Color::Red);
            }

        }

        // RENDER ////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color::Black);
        window->setView(cam->view);
        window->draw(*terrain);
        window->draw(*floors);
        renderGameObjects();

        if (!GUIwasHover && prefabToPaint != nullptr)
            prefabToPaint->draw(window);
        
        drawPalette();
        window->display();
    }
}

void buildingEditorEventLeftClick() {

    if (buttonUp->mouseOvering(worldMousePosition)) {
        GUIwasClicked = true;
        if (paletteScroll > 0)
            paletteScroll -= 1;
    }
    else if (buttonDown->mouseOvering(worldMousePosition)) {
        GUIwasClicked = true;

        float maxValue = availableGameObjects.size() - 16;
        if (maxValue < 0)
            maxValue = 0;

        if (paletteScroll * 2 < maxValue)
            paletteScroll += 1;

    }

    // select the palette button
    for (auto& p : palette) {
        if (p.mouseOvering(worldMousePosition)) {

            GUIwasClicked = true;
            prefabToPaint = p.object;

        }
    }

    if (!GUIwasClicked && prefabToPaint != nullptr) {
        
        addPrefabToLists();
    }
}

void buildingEditorEventRightClick() {

    if (prefabToPaint == nullptr) {

        bool was_delete = false;

        for (auto& go : gameObjects) {
            if (go->mouseIsOver == true) {
                //cout << "delete: " << go->name << "\n";
                go->toDelete = true;
                was_delete = true;
                break;
            }
        }

        if (was_delete) {
            deleteGameObjectsFromMainLists();
        }
        else {
            floors->edit(worldMousePosition, 0);
        }

    }
    else
        prefabToPaint = nullptr;
}

void saveBuildingToFile() {

    string filename = "assets/buildings/testBuilding.txt";
    std::ofstream file(filename);

    if (!file.is_open()) {
        cout << "cant open file to save building: " << filename << "\n";
        return;
    }

    file << "name \"testBuilding\"\n";
    file << "texture \"assets/buildings/testBuilding.png\"\n";
    file << "size " << to_string(terrain->width) << " " << to_string(terrain->height) << "\n";
    file << "\n";

    // save floors
    file << "// FLOORS\n";
    for (int y = 0; y < floors->height; y++) {
        for (int x = 0; x < floors->width; x++) {

            file << floors->floors[y*floors->width+x];
            if (x != floors->width-1)
                file << " ";
        }

        file << "\n";
    }

    file << "\n";

    if (natures.size() > 0)
        file << "// NATURES\n";
    for (auto& nature : natures)
        file << "Nature " << char(34) << nature->name << char(34) << " " << int(nature->position.x) << " " << int(nature->position.y) << "\n";
    if (natures.size() > 0)
        file << "\n";


    if (itemsOnMap.size() > 0)
        file << "// ITEMS\n";
    for (auto& item : itemsOnMap)
        file << "Item " << char(34) << item->name << char(34) << " " << int(item->position.x) << " " << int(item->position.y) << "\n";
    if (itemsOnMap.size() > 0)
        file << "\n";


    if (paths.size() > 0)
        file << "// PATHS\n";
    for (auto& path : paths)
        file << "Path " << char(34) << path->name << char(34) << " " << int(path->position.x) << " " << int(path->position.y) << "\n";
    if (paths.size() > 0)
        file << "\n";


    if (furnitures.size() > 0)
        file << "// FURNITURES\n";
    for (auto& furniture : furnitures)
        file << "Furniture " << char(34) << furniture->name << char(34) << " " << int(furniture->position.x) << " " << int(furniture->position.y) << "\n";
    if (furnitures.size() > 0)
        file << "\n";


    if (walls.size() > 0)
        file << "// WALLS\n";
    for (auto& wall : walls)
        file << "Wall " << char(34) << wall->name << char(34) << " " << int(wall->position.x) << " " << int(wall->position.y) << "\n";
    if (walls.size() > 0)
        file << "\n";


    if (monsters.size() > 0)
        file << "// MONSTERS\n";
    for (auto& monster : monsters)
        file << "Monster " << char(34) << monster->name << char(34) << " " << int(monster->position.x) << " " << int(monster->position.y) << "\n";
    if (monsters.size() > 0)
        file << "\n";



    if (buildings.size() > 0)
        file << "// BUILDINGS\n";
    for (auto& building : buildings)
        file << "Building " << char(34) << building->name << char(34) << " " << int(building->position.x) << " " << int(building->position.y) << "\n";
    if (buildings.size() > 0)
        file << "\n";


    if (characters.size() > 0)
        file << "// CHARACTERS\n";
    for (auto& character : characters)
        file << "Character " << char(34) << character->name << char(34) << " " << int(character->position.x) << " " << int(character->position.y) << "\n";
    if (characters.size() > 0)
        file << "\n";


    if (inventoriesOnMap.size() > 0)
        file << "// INVENTORIES\n";
    for (auto& inventory : inventoriesOnMap)
        file << "Inventory " << char(34) << inventory->name << char(34) << " " << int(inventory->position.x) << " " << int(inventory->position.y) << "\n";
    if (inventoriesOnMap.size() > 0)
        file << "\n";



    file.close();

}

void addPrefabToLists() {

    int x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
    int y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
    // cout << "cursor at position: " << xx << " " << yy << "\n"

    if (prefabToPaint->type == gameObjectType::Nature) {

        Nature* nature = new Nature(prefabToPaint, x, y);
        gameObjects.push_back(nature);
        natures.push_back(nature);
    }

    if (prefabToPaint->type == gameObjectType::Monster) {

        Monster* monster = new Monster(prefabToPaint, x, y);
        gameObjects.push_back(monster);
        monsters.push_back(monster);
    }

    if (prefabToPaint->type == gameObjectType::ItemOnMap) {

        ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
        gameObjects.push_back(item);
        itemsOnMap.push_back(item);
    }

    if (prefabToPaint->type == gameObjectType::Path) {

        Path* path = new Path(prefabToPaint, x, y);
        gameObjects.push_back(path);
        paths.push_back(path);
    }

    if (prefabToPaint->type == gameObjectType::Furniture) {

        Furniture* furniture = new Furniture(prefabToPaint, x, y);
        gameObjects.push_back(furniture);
        furnitures.push_back(furniture);
    }

    if (prefabToPaint->type == gameObjectType::Wall) {
        Wall* wall = new Wall(prefabToPaint, x, y);
        gameObjects.push_back(wall);
        walls.push_back(wall);
    }
}

#endif