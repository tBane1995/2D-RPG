#ifndef MapEditor_hpp
#define MapEditor_hpp

enum class mapEditorStates { start, editor };
mapEditorStates mapEditorState;

bool showStatistics = false;

void painterUpdate();
void painterDraw();
void addPrefabToLists();
void editTiles();
void editFloors();
void MapEditorUnclickButtons();
void MapEditorHoverButtons();
void MapEditorEventLeftClick();
void MapEditorEventRightClick();


void MapEditor() {

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
    selectedGameObjects.clear();

    selection_state = false;

    createMapEditorPalette();

    world = new World();
    world->load();
    cam->setPosition(screenWidth/2.0f, screenHeight/2.0f);

    updateGameObjects();

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();

        mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
        worldMousePosition = window->mapPixelToCoords(mousePosition);

        GUIwasHover = false;
        GUIwasClicked = false;

        MapEditorUnclickButtons();
        MapEditorHoverButtons();

        // events
        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    MapEditorEventLeftClick();

                    if (tool == toolType::Cursor || tool == toolType::Rectangle || tool == toolType::Elipse) {
                        selection_state = false;
                    }

                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    MapEditorEventRightClick();
                }
            }
                
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (GUIwasHover != true) {

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
                    world->save();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) {
                    world->load();
                }

            }



        }

        // calculate delta time
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        float moveSpeed = 300.0f * dt;
        // moving the view
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cam->move(0.0f, -moveSpeed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            cam->move(0.0f, moveSpeed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cam->move(-moveSpeed, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cam->move(moveSpeed, 0.0f);

        

        if (!GUIwasHover) {

            if (prefabToPaint != nullptr) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (tool == toolType::Brush || tool == toolType::RectBrush) {
                        if (prefabToPaint->type == gameObjectType::Terrain)
                            editTiles();
                    }
                    
                }
            }

        }

        

        // UPDATE ////////////////////////////////////////////////////////////////////////

        world->mapVisiblings();     // render map or not render map
        
        world->update(dt);
        for (auto& go : selectedGameObjects)
            go->updateStatistic(dt);

        updateGameObjects();
        sortGameObjects();
        updatePalette();
        cam->update();
        painterUpdate();
      

        // RENDER ////////////////////////////////////////////////////////////////////////////

        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        world->draw();
        world->drawStatistic();

        for (auto& m : world->maps)
            for (auto& b : m->_buildings) {
                window->draw(*b->floors);
                b->draw();
            }
        
        for (auto& go : selectedGameObjects)
            go->drawStatistic();

        drawGameObjects();
        painterDraw();
    
        drawPalette();
        window->display();
    }

    delete window;
}



void editTiles() {

    
    for(auto& prefab : prefabsToPaint) {

        if (prefab->type == gameObjectType::Terrain) {
            
            TerrainPrefab* tp = dynamic_cast<TerrainPrefab*>(prefab);
            //cout << prefab->position.x << ", " << prefab->position.y << "\n";

            Map* map = world->getMap(tp->position);

            if (map != nullptr) {

                if (tp->name == "tiles/tile_0_grass")
                    map->editTile(tp->position, 0);

                if (tp->name == "tiles/tile_1_sands")
                    map->editTile(tp->position, 1);

                if (tp->name == "tiles/tile_2_water")
                    map->editTile(tp->position, 2);

                if (tp->name == "tiles/tile_3_gravel")
                    map->editTile(tp->position, 3);

            }
        }
    }

    
}

void MapEditorUnclickButtons() {
    buttonUp->unclick();
    buttonDown->unclick();

    for (auto& mb : menuButtons)
        mb->unclick();

    for (int i = 0; i < paletteCols * paletteRows; i++)
        palette[i]->unclick();

    if (selectedMenuButton == btnMenuTerrain)
        for (auto& tool : tools)
            tool->unclick();

}

void MapEditorHoverButtons() {
    buttonUp->hover();
    buttonDown->hover();

    for (auto& mb : menuButtons)
        mb->hover();
    
    for (int i = 0; i < paletteCols * paletteRows; i++)
        palette[i]->hover();

    if (selectedMenuButton == btnMenuTerrain)
        for (auto& tool : tools)
            tool->hover();

}

void MapEditorEventLeftClick() {
    
    cout << "\nclick";

    buttonUp->click();
    buttonDown->click();

    for (auto& mb : menuButtons)
        mb->click();

    for (int i = 0; i < paletteCols * paletteRows; i++) {
        palette[i]->click();
    }

    if (selectedMenuButton == btnMenuTerrain)
        for (auto& tool : tools)
            tool->click();

    if (!GUIwasHover) {

        (GUIwasHover) ? cout << "hover" : cout << "not hover";

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
                addPrefabsToMapAndLists();
            }

            if (tool == toolType::Rectangle || tool == toolType::Elipse) {
                editTiles();
            }
        }

    }

}

void MapEditorEventRightClick() {
    
    
    if (prefabToPaint == nullptr) {

        if (!selectedGameObjects.empty()) {
            selectGameObjects(0, 0, 0, 0);
            return;
        }
            

        bool was_delete = false;

        // TO-DO //////////////////////////////////////////////////
        for (auto& m : world->maps)
            for (auto& building : m->_buildings) {
                if (building->mouseIsOver) {
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

    } else {
  
        selectedPaletteButton = nullptr;
        selectedTool = btnToolsCursor;
        tool = toolType::Cursor;
        prefabToPaint = nullptr;
    }
}
#endif