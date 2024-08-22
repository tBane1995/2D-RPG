#ifndef MapEditor_hpp
#define MapEditor_hpp

enum class mapEditorStates { start, editor };
mapEditorStates mapEditorState;

void addPrefabToLists();
void createPalette();
void updatePalette();
void renderPalette();
void editTile();
void editFloor();
void mapEditorEventLeftClick();
void mapEditorEventRightClick();

void mapEditor() {

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/MapEditorLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    // create sf::View
    cam = new Camera();
    window->setView(cam->view);

    // start screen
    mapEditorState = mapEditorStates::start;

    sf::Text* welcomeText = new sf::Text("Map Editor", basicFont, 32);
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

    mapEditorState = mapEditorStates::editor;

    prefabToPaint = nullptr;
    createMapEditorPalette();

    world = new World();
    world->load();
    cam->setPosition(screenWidth/2.0f, screenHeight/2.0f);

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

            if (mapEditorState == mapEditorStates::editor) {

                if (event.type == sf::Event::MouseButtonPressed) {

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        mapEditorEventLeftClick();
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        // DELETE GAMEOBJECTS OR FLOORS
                        mapEditorEventRightClick();
                    }
                }

                    

                if (event.type == sf::Event::KeyPressed) {
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window->close();
                        exit(0);
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                        world->save();
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) {
                        world->load();
                    }

                }



            }
        }

        // calculate delta time
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        float moveSpeed = 1.0f;
        // moving the view
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cam->move(0.0f, -moveSpeed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            cam->move(0.0f, moveSpeed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cam->move(-moveSpeed, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cam->move(moveSpeed, 0.0f);

        if (!GUIwasClicked) {
            
            if (prefabToPaint != nullptr) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    if (prefabToPaint->type == gameObjectType::Terrain)
                        editTile();

                    if (prefabToPaint->type == gameObjectType::Floor) {
                        editFloor();
                    }
                }
            }
            

        }

        

        // UPDATE ////////////////////////////////////////////////////////////////////////

        world->mapVisiblings();     // render map or not render map

        updateGameObjects();
        sortGameObjects();

        cam->update();

        
        // PALETTE
        for (auto& p : palette) {
            if (p.mouseOvering(worldMousePosition))
                GUIwasHover = true;
        }
        
        
        // A PAINTER
        if (prefabToPaint != nullptr) {

            if (prefabToPaint->type != gameObjectType::Terrain && prefabToPaint->type != gameObjectType::Floor ) {

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


        updatePalette();


        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);
        world->draw();
        
        for (auto& m : world->maps)
            for (auto& building : m->_buildings)
            {
                window->draw(building->rect);
                window->draw(*building->floors);
            }

        renderGameObjects();

        

        if(!GUIwasHover && prefabToPaint != nullptr)
           prefabToPaint->draw(window);
    
        drawPalette();

        window->display();
    }


}

void addPrefabToMapAndLists() {

    int x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
    int y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
    // cout << "cursor at position: " << xx << " " << yy << "\n"

    Map* map = world->getMap(worldMousePosition);

    if(map != nullptr) {

        if (prefabToPaint->type == gameObjectType::Nature) {

            Nature* nature = new Nature(prefabToPaint, x, y);
            gameObjects.push_back(nature);
            natures.push_back(nature);
            map->_natures.push_back(nature);
        }

        if (prefabToPaint->type == gameObjectType::Monster) {

            Monster* monster = new Monster(prefabToPaint, x, y);
            gameObjects.push_back(monster);
            monsters.push_back(monster);
            map->_monsters.push_back(monster);
        }

        if (prefabToPaint->type == gameObjectType::ItemOnMap) {

            ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
            map->_itemsOnMap.push_back(item);
        }

        if (prefabToPaint->type == gameObjectType::Path) {

            Path* path = new Path(prefabToPaint, x, y);
            gameObjects.push_back(path);
            paths.push_back(path);
            map->_paths.push_back(path);
        }

        if (prefabToPaint->type == gameObjectType::Furniture) {

            Furniture* furniture = new Furniture(prefabToPaint, x, y);
            gameObjects.push_back(furniture);
            furnitures.push_back(furniture);
            map->_furnitures.push_back(furniture);
        }

        if (prefabToPaint->type == gameObjectType::Wall) {
            Wall* wall = new Wall(prefabToPaint, x, y);
            gameObjects.push_back(wall);
            walls.push_back(wall);
            map->_walls.push_back(wall);
        }
    }
}

void editTile() {

    Map* map = world->getMap(worldMousePosition);

    if (map == nullptr)
        return;

    TerrainPrefab* terrainPrefab = dynamic_cast<TerrainPrefab*>(prefabToPaint);

    if (map != nullptr) {

        if (terrainPrefab->name == "tiles/tile_0_grass")
            map->editTile(worldMousePosition, 0);

        if (terrainPrefab->name == "tiles/tile_1_sands")
            map->editTile(worldMousePosition, 1);

        if (terrainPrefab->name == "tiles/tile_2_water")
            map->editTile(worldMousePosition, 2);

        if (terrainPrefab->name == "tiles/tile_3_gravel")
            map->editTile(worldMousePosition, 3);

        
    }

    
}

void editFloor() {
    
    Map* map = world->getMap(worldMousePosition);
    
    if (map == nullptr)
        return;

    if (prefabToPaint == nullptr) {
        map->editFloor(worldMousePosition, 0);
        return;
    }

    FloorPrefab* floorPrefab = dynamic_cast<FloorPrefab*>(prefabToPaint);

    if (map != nullptr) {
        
        if (floorPrefab->name == "floors/floor_0")
            map->editFloor(worldMousePosition, 0);
            
        if (floorPrefab->name == "floors/floor_1")
            map->editFloor(worldMousePosition, 1);

        if (floorPrefab->name == "floors/floor_2")
            map->editFloor(worldMousePosition, 2);
            
        if (floorPrefab->name == "floors/floor_3")
            map->editFloor(worldMousePosition, 3);
    }
}

void mapEditorEventLeftClick() {
    cout << worldMousePosition.x << " " << worldMousePosition.y << "\n";

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

        if (prefabToPaint->type != gameObjectType::Terrain) {
            addPrefabToMapAndLists();
        }
    }
}

void mapEditorEventRightClick() {
    
    if (prefabToPaint == nullptr) {

        bool was_delete = false;

        // TO-DO //////////////////////////////////////////////////
        for (auto& m : world->maps)
            for (auto& building : m->_buildings) {
                if (building->mouseIsOver(worldMousePosition)) {
                    building->deleteBuilding();
                    deleteGameObjectsFromMainLists();
                    was_delete = true;
                    break;
                }

            }

        ////////////////////////////////////////////////////////

        for (auto& go : gameObjects) {
            if (go->mouseIsOver == true) {
                //cout << "delete: " << go->name << "\n";
                go->toDelete = true;
                was_delete = true;
                break;
            }
        }

        if (was_delete) {
            world->mapVisiblings();
            deleteGameObjectsFromMainLists();
            for (auto& map : world->maps)
                map->deleteGameObjects();
        }
        else {
            editFloor();
        }

    }
    else
        prefabToPaint = nullptr;
}
#endif