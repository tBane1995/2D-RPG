#ifndef BuildingEditor_hpp
#define BuildingEditor_hpp

enum class buildingEditorStates { start, editor };
buildingEditorStates buildingEditorState;
Terrain* terrain;
Floors* floors;

void BuildingEditorUnclickButtons();
void BuildingEditorHoverButtons();
void BuildingEditorEventLeftClick();
void BuildingEditorEventRightClick();
void saveBuildingToFile();
void addPrefabToLists();

void BuildingEditor() {

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
    selection_state = false;

    createBuildingEditorPalette();

    updateGameObjects();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        BuildingEditorUnclickButtons();
        BuildingEditorHoverButtons();

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                }
            }
            
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    BuildingEditorEventLeftClick();

                    if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                        selection_state = false;
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    BuildingEditorEventRightClick();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (!GUIwasHover) {

                        startMousePosition = sf::Mouse::getPosition(*window);
                        startWorldMousePosition = window->mapPixelToCoords(mousePosition);

                        if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                            selection_state = true;
                        }
                    }

                }
            }

            if (event.type == sf::Event::KeyPressed) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window->close();
                    exit(0);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                    saveBuildingToFile();
                }
            }
        }

        // UPDATE ///////////////////////////////////////////////////////////////////////

        // calculate delta time
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        
        for (auto& go : selectedGameObjects)
            go->updateStatistic(dt);

        updateGameObjects();
        sortGameObjects();
        updatePalette();
        painterUpdate();

        if (!GUIwasHover) {

            if (prefabToPaint != nullptr) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (tool == toolType::Brush || tool == toolType::RectBrush) {
                        if (prefabToPaint->type == gameObjectType::Floor) {
                            for (auto& prefab : prefabsToPaint) {
                                floors->edit(prefab->position, dynamic_cast<FloorPrefab*>(prefabToPaint));
                            }
                        }
                    }
                }
            }
        }

        cam->update();

        // RENDER ////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color::Black);
        window->setView(cam->view);
        window->draw(*terrain);
        window->draw(*floors);

        for (auto& go : selectedGameObjects)
            go->drawStatistic();
        
        drawGameObjects();
        painterDraw();

        drawPalette();
        window->display();
    }
}

void BuildingEditorUnclickButtons() {
    buttonUp->unclick();
    buttonDown->unclick();

    for (auto& mb : menuButtons)
        mb->unclick();
    
    for (auto& p : palette)
        p->unclick();

    for (auto& t : tools)
        t->unclick();
    
}

void BuildingEditorHoverButtons() {
    buttonUp->hover();
    buttonDown->hover();

    for (auto& mb : menuButtons)
        mb->hover();
    
    for (auto& p : palette)
        p->hover();
    
    for (auto& t : tools)
        t->hover();
}

void BuildingEditorEventLeftClick() {

    buttonUp->click();
    buttonDown->click();

    for (auto& mb : menuButtons)
        mb->click();

    for (int i = 0; i < paletteCols * paletteRows; i++) {
        palette[i]->click();
    }

    if (selectedMenuButton == btnMenuFloors)
        for (auto& tool : tools)
            tool->click();

    if (!GUIwasHover) {

        if (tool == toolType::Cursor) {

            int x = selectArea.getPosition().x;
            int y = selectArea.getPosition().y;
            int w = selectArea.getSize().x;
            int h = selectArea.getSize().y;

            if (w < 16) w = 16;
            if (h < 16) h = 16;

            selectGameObjects(x, y, w, h);

        }

        if (!prefabsToPaint.empty()) {

            if (tool == toolType::AddGameObject) {
                addPrefabToLists();
            }

            if (tool == toolType::Rectangle || tool == toolType::Elipse) {
                for (auto& prefab : prefabsToPaint) {
                    floors->edit(prefab->position, dynamic_cast<FloorPrefab*>(prefabToPaint));
                }
            }
        }

    }

}

void BuildingEditorEventRightClick() {

    if (prefabToPaint == nullptr) {

        if (!selectedGameObjects.empty()) {
            selectGameObjects(0, 0, 0, 0);
            return;
        }

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

    }
    else {

        selectedPaletteButton = nullptr;
        selectedTool = btnToolsCursor;
        tool = toolType::Cursor;
        prefabToPaint = nullptr; 
    }
        
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

#endif