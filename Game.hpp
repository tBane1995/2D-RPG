#ifndef Game_hpp
#define Game_hpp

// Music by: LisetteAmago
// www.lisetteamago.com /
// lisetteamago@gmail.com


sf::RectangleShape borderLifeBar;   // border
sf::Texture lifeBarBackgroundTexture;       // background lifebar
sf::Sprite lifeBarBackgroundSprite;
sf::Texture lifeBarTexture;         // lifebar
sf::Sprite lifeBarSprite;

bool defeatAllBeasts = false;
bool collectAllItems = false;

void refreshLifeBar();
void drawLifeBar();
bool playerAttack();
bool talkWithCharacter();
bool collectItems();
void deleteCollectedItems();

void gameEvents();
void inventoryEvents();
void tradeEvents();
void dialogueEvents();
void journalEvents();

void game() {

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/GameLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    cam = new Camera();
    window->setView(cam->view);

    prevTime = timeClock.getElapsedTime();
    currentTime = prevTime;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    gameState = gameStates::start;

    sf::Text* welcome = new sf::Text("welcome", basicFont, 32);
    welcome->setFillColor(titleColor);
    welcome->setOrigin(welcome->getLocalBounds().width / 2.f, welcome->getLocalBounds().height / 2.f);
    welcome->setPosition(screenWidth / 2.0f, screenHeight / 2.0f - 50);

    sf::Text* press = new sf::Text("press Spacebar to start", basicFont, 16);
    press->setFillColor(titleColor);
    press->setOrigin(press->getLocalBounds().width / 2.f, press->getLocalBounds().height / 2.f);
    press->setPosition(screenWidth / 2.0f, screenHeight / 2.0f + 50);

    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            gameState = gameStates::game;
            break;
        }

        window->setView(cam->view);
        welcome->setPosition(cam->position.x, cam->position.y - 50);
        press->setPosition(cam->position.x, cam->position.y + 50);

        window->clear(sf::Color::Black);
        window->draw(*welcome);
        window->draw(*press);
        window->display();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    setDialogue(0);

    /*
    sf::Music music;
    if (!music.openFromFile("music/Elkmire Keep (LOOP).ogg")) {
        return;
    }

    music.setLoop(true);    // TO-DO
    music.play();           // TO-DO
    */

    clearAllMainListsOfGameObjects();
    world = new World();
    world->mapVisiblings();
    world->load();

    createPlayer();
    cam->setPosition(player->position);
    cam->update();

    // TEST TRADE   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Inventory* in = new Inventory();
    in->addItem("items/torn shirt");
    in->addItem("items/axe");
    in->addItem("items/bone");
    in->addItem("items/health herb");
    in->addItem("items/skin helmet");
    in->addItem("items/skin pants");
    in->addItem("items/wooden club");
    in->addItem("items/skin jacket");
    in->addItem("items/club");
    in->addItem("items/iron club");
    in->addItem("items/stone hammer");
    in->addItem("items/sword");
    in->addItem("items/long sword");
    in->addItem("items/gladius");
    in->addItem("items/wide blade");
    in->addItem("items/knife");
    in->addItem("items/dagger");
    in->addItem("items/hatchet");
    in->addItem("items/curved sword");
    in->addItem("items/chain mail");
    in->addItem("items/wool hat");
    in->addItem("items/wool pants");
    in->addItem("items/wool shirt");
    in->addItem("items/raw meat");
    in->addItem("items/roasted meat");
    in->addItem("items/chain mail pants");
    in->addItem("items/plate armor");
    in->addItem("items/shield");

    inventoryLeft = new InventoryPanel(in, -300);
    inventoryRight = new InventoryPanel(player->bag, 300);
    cursor = 0;
    activePanel = activeInventoryPanel::Left;
    gameState = gameStates::trade;

    cursor = 0;
    journal = new JournalPanel();
    gameState = gameStates::journal;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed) {

                if (gameState == gameStates::game) {
                    gameEvents();
                }
                else if (gameState == gameStates::inventory) {
                    inventoryEvents();
                }
                else if (gameState == gameStates::trade) {
                    tradeEvents();
                }
                else if (gameState == gameStates::dialogue) {
                    dialogueEvents();
                }
                else if (gameState == gameStates::journal) {
                    journalEvents();
                }

            }

            if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
                    worldMousePosition = window->mapPixelToCoords(mousePosition);	// Zamień na współrzędne świata, uwzględniając aktualny widok
                    cout << "cursor at " << worldMousePosition.x << " " << worldMousePosition.y << "\n";

                    Point start(player->position.x, player->position.y);
                    Point goal(worldMousePosition.x, worldMousePosition.y);

                    std::vector < Point > path = aStar(start, goal);

                    std::cout << "Path: ";
                    for (const Point& p : path)
                        std::cout << "(" << p.x << ", " << p.y << ") ";

                    cout << "\n\n";

                }
            }


        } // events

        // UPDATES
        //cout << "cursor at: " << sf::Mouse::getPosition(*window).x << "," << sf::Mouse::getPosition(*window).y << endl;


        if (gameState == gameStates::game) {

            // WASD
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (player->direction != 0)
                    player->setDirection(0);
                else if (!collisions(player, 0, -player->stepSize))
                    player->move();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (player->direction != 1)
                    player->setDirection(1);
                else if (!collisions(player, player->stepSize, 0))
                    player->move();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (player->direction != 2)
                    player->setDirection(2);
                else if (!collisions(player, 0, player->stepSize))
                    player->move();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (player->direction != 3)
                    player->setDirection(3);
                else if (!collisions(player, -player->stepSize, 0))
                    player->move();
            }
        }

        deleteCollectedItems();

        dt = currentTime.asSeconds() - prevTime.asSeconds();

        world->mapVisiblings();
        
        if(gameState != gameStates::dialogue)
            checkQuests();
        
        for (auto& go : gameObjects)
            if(visiblings(go))
                go->update(dt);

        std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });

        cam->setPosition(player->position);
        cam->update();
        
        if(gameState == gameStates::inventory)
            updateInventoryPanel();

        if(gameState == gameStates::trade)
            updateTradePanel();
        
        if (gameState == gameStates::journal)
            journal->update();

        refreshLifeBar();

        // DRAW
        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        world->draw();

        for (auto& path : paths)
            if(visiblings(path))
                path->draw(window);

        for (auto& go : gameObjects) {
            if (go->type != gameObjectType::Path)
                if(visiblings(go))
                    go->draw(window);
        }

        if (gameState == gameStates::inventory)
            drawInventoryPanel();

        if (gameState == gameStates::dialogue) {

            if (dialogueState == dialogueStates::dialogue) {
                setTextToDialogBox(currentDialogue->text);
                drawDialogBox(window, page);
            }

            if (dialogueState == dialogueStates::choose) {
                drawChooseBox(window);

            }
        }

        if (gameState == gameStates::trade) {
            drawTradePanel();
        }

        if (gameState == gameStates::journal) {
            journal->draw();
        }

        drawLifeBar();
        window->display();
    } //while
    return;
}



void refreshLifeBar() {
    int x = cam->position.x - screenWidth / 2.0f;
    int y = cam->position.y - screenHeight / 2.0f;

    borderLifeBar = sf::RectangleShape(sf::Vector2f(200.0f, 30.0f));
    borderLifeBar.setPosition(x, y);
    borderLifeBar.setFillColor(sf::Color(0, 0, 0, 255));

    lifeBarBackgroundTexture = sf::Texture();
    lifeBarBackgroundTexture.loadFromFile("assets/GUI/lifeBarBackground.png");
    lifeBarBackgroundSprite = sf::Sprite();
    lifeBarBackgroundSprite.setTexture(lifeBarBackgroundTexture);
    lifeBarBackgroundSprite.setPosition(x + 4, y + 4);

    lifeBarTexture = sf::Texture();
    lifeBarTexture.loadFromFile("assets/GUI/lifeBar.png");
    lifeBarSprite = sf::Sprite();
    lifeBarSprite.setTexture(lifeBarTexture);
    lifeBarSprite.setTextureRect(sf::IntRect(0, 0, 192.0f * player->HP / player->HP_max, 22.0f));
    lifeBarSprite.setPosition(x + 4, y + 4);


}

void drawLifeBar() {
    window->draw(borderLifeBar);
    window->draw(lifeBarBackgroundSprite);
    window->draw(lifeBarSprite);
    
}

bool playerAttack() {

    bool result = false;
    float x, y, rx, ry;
    x = player->position.x;
    y = player->position.y;
    rx = player->collider->width/2.0f + player->actionRange;
    ry = (player->collider->height + player->actionRange) / 2.0f;

    for (auto& m : monsters)
    {
        if(m->isAlive == true)
            if (intersectionTwoEllipses(x, y, rx, ry, m->position.x, m->position.y, m->collider->width/2.0f, m->collider->height / 2.0f)) {
                m->takeDamage(player->getDamage());
                result = true;
            }
    }
    player->attack();   // animation
    return result;
}

bool talkWithCharacter() {

    float x1, y1, rx1, ry1;
    float x2, y2, rx2, ry2;

    x1 = player->position.x;
    y1 = player->position.y;
    rx1 = (player->collider->width/2.0f + player->actionRange);
    ry1 = (player->collider->height + player->actionRange) / 2.0f;

    for (auto& character : characters) {

        if (character->dialogue != nullptr) {

            x2 = character->position.x;
            y2 = character->position.y;
            rx2 = (character->collider->width/2.0f + character->actionRange);
            ry2 = (character->collider->height + character->actionRange) / 2.0f;

            if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {

                // talking 
                // TO-DO
                setDialogue(character->dialogue);
                return true;
            }
        }

    }


    return false;
}

bool collectItems() {

    float x1, y1, rx1, ry1;
    float x2, y2, rx2, ry2;

    x1 = player->position.x;
    y1 = player->position.y;
    rx1 = (player->collider->width/2.0f + player->actionRange);
    ry1 = (player->collider->height + player->actionRange) / 2.0f;


    for (auto& item : itemsOnMap) {
        x2 = item->position.x;
        y2 = item->position.y;
        rx2 = item->collider->width / 2.0f;
        ry2 = item->collider->height / 2.0f;

        if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {

            // collect the Item
            player->collectItem(item->item);
            item->collected = true;
            return true;
        }
    }

    for (auto& bag : inventoriesOnMap) {
        x2 = bag->position.x;
        y2 = bag->position.y;
        rx2 = bag->collider->width / 2.0f;
        ry2 = bag->collider->height / 2.0f;

        if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {

            // collect the bag

            for (int i = 0; i < bag->inventory->items.size(); i++) {
                player->collectItem(bag->inventory->items[i], bag->inventory->counts[i]);
            }

            bag->collected = true;
            return true;
        }
    }

    for (auto& furniture : furnitures) {

        if( furniture->inventory != nullptr ) {
            x2 = furniture->position.x;
            y2 = furniture->position.y;
            rx2 = furniture->collider->width;
            ry2 = furniture->collider->height;

            if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1)) {
                inventoryLeft = new InventoryPanel(furniture->inventory, -300);
                inventoryRight = new InventoryPanel(player->bag, 300);
                cursor = 0;
                activePanel = activeInventoryPanel::Left;
                gameState = gameStates::trade;
                return true;
            }
        }
    }
     
    return false;
}



void deleteCollectedItems() {
    std::vector < GameObject* > newGameObjectsList;
    std::vector < ItemOnMap* > newItemsOnMapList;
    std::vector < InventoryOnMap* > newInventoriesOnMapList;

    // DELETE ITEMS
    newGameObjectsList.clear();
    newItemsOnMapList.clear();

    for (auto& go : gameObjects) {
        if (go->type != gameObjectType::ItemOnMap) {
            newGameObjectsList.push_back(go);
        }
    }

    for (auto& item : itemsOnMap) {
        if (item->collected != true) {
            newGameObjectsList.push_back(item);
            newItemsOnMapList.push_back(item);
        }
    }

    gameObjects = newGameObjectsList;
    itemsOnMap = newItemsOnMapList;

    // DELETE INVENTORIES
    newGameObjectsList.clear();
    newInventoriesOnMapList.clear();

    for (auto& go : gameObjects) {
        if (go->type != gameObjectType::InventoryOnMap) {
            newGameObjectsList.push_back(go);
        }
    }

    for (auto& bag : inventoriesOnMap) {
        if (bag->collected != true) {
            newGameObjectsList.push_back(bag);
            newInventoriesOnMapList.push_back(bag);
        }
    }

    gameObjects = newGameObjectsList;
    inventoriesOnMap = newInventoriesOnMapList;

}

void gameEvents() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->close();
        exit(0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

        if (player->cooldown <= 0.0f)
            if (!playerAttack())
                if (!collectItems())
                    if (!talkWithCharacter())
                        player->attack();   // animation of attack
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        cursor = 0;
        inventory = new InventoryPanel(player->bag);
        gameState = gameStates::inventory;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        cursor = 0;
        journal = new JournalPanel();
        gameState = gameStates::journal;
    }

}

void inventoryEvents() {
    // INVENTORY
    // TO-DO WASD with inventory->scroll

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {

        cursor = 0;
        journal = new JournalPanel();
        gameState = gameStates::journal;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        // USE THE ITEM
        useItem();

        if (cursor + inventory->scroll * itemsInRow >= inventory->inventory->items.size()) {
            
            int maxScroll = (inventory->inventory->items.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
            if (maxScroll < 0)
                maxScroll = 0;

            if (inventory->scroll > maxScroll) {

                cursor = cursor + (inventory->scroll-maxScroll)*itemsInRow - 1;
                inventory->scroll = maxScroll;
                
            }
            else
                cursor -= 1;
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(cursor%itemsInRow != 0)
          cursor -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if((cursor + 1)%itemsInRow != 0 )
            if(cursor + 1 + inventory->scroll * itemsInRow < inventory->inventory->items.size())
                cursor += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cursor -= itemsInRow;

        if (cursor < 0) {
            inventory->scroll -= 1;
            if (inventory->scroll < 0)
                inventory->scroll = 0;

            cursor += itemsInRow;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (inventory->inventory->items.size() > 0) {
            if ((cursor / itemsInRow * itemsInRow) + itemsInRow < inventory->inventory->items.size())
                cursor += itemsInRow;

            int maxScroll = (inventory->inventory->items.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
            if (maxScroll < 0)
                maxScroll = 0;

            if (cursor >= itemsInRow * itemsInCol) {
                inventory->scroll += 1;

                if (inventory->scroll > maxScroll)
                    inventory->scroll = maxScroll;

                cursor -= itemsInRow;
            }

            if (cursor + inventory->scroll * itemsInRow >= inventory->inventory->items.size()) {
                cursor = inventory->inventory->items.size() - inventory->scroll * itemsInRow - 1;
            }
        }
        else
            cursor = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        gameState = gameStates::journal;
        journal = new JournalPanel();
    }

}

void tradeEvents() {

    // TO-DO - whole function to repair

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (activePanel == activeInventoryPanel::Right) {
            // ACTIVE PANEL RIGHT

            if (cursor % itemsInRow == 0) {

                activePanel = activeInventoryPanel::Left;
                
                if (inventoryLeft->inventory->items.size() == 0)
                    cursor = 0;
                else {
                    cursor = cursor + itemsInRow - 1;

                    int diff = cursor + inventoryLeft->scroll * itemsInRow - (inventoryLeft->inventory->items.size() - 1);
                    if (diff > 0)
                        cursor -= diff;
                }
            }
            else
                cursor -= 1;
        }
        else {
            // ACTIVE PANEL LEFT
            if ((cursor % itemsInRow != 0))
                cursor -= 1;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        if (activePanel == activeInventoryPanel::Left) {
            // ACTIVE PANEL LEFT
            if (inventoryLeft->inventory->items.size() == 0) {
                activePanel = activeInventoryPanel::Right;
                cursor = 0;
            }
            else if ((cursor + inventoryLeft->scroll * itemsInRow >= inventoryLeft->inventory->items.size()-1) || cursor % itemsInRow == itemsInRow - 1) {
                activePanel = activeInventoryPanel::Right;

                int diff = cursor + inventoryRight->scroll * itemsInRow - (inventoryRight->inventory->items.size() - 1);
                if (diff > 0)
                    cursor -= diff;
                cursor -= cursor % itemsInRow;


            }
            else {
                cursor += 1;
            }
               
        }
        else {
            // ACTIVE PANEL RIGHT
            if (cursor % itemsInRow != itemsInRow - 1) {
                if(cursor + 1 + inventoryRight->scroll*itemsInRow < inventoryRight->inventory->items.size())
                    cursor += 1;
            }
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cursor -= itemsInRow;

        if (cursor < 0)
        {
            if (activePanel == activeInventoryPanel::Right) {
                if(inventoryRight->scroll > 0)
                    inventoryRight->scroll -= 1;
            }

            if (activePanel == activeInventoryPanel::Left) {
                if (inventoryLeft->scroll > 0)
                    inventoryLeft->scroll -= 1;
            }

            cursor += itemsInRow;
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
       
        if (activePanel == activeInventoryPanel::Right) {

            if (inventoryRight->inventory->items.size() > 0) {

                if ((cursor / itemsInRow * itemsInRow) + itemsInRow < inventoryRight->inventory->items.size())
                    cursor += itemsInRow;

                int maxScroll = (inventoryRight->inventory->items.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                if (maxScroll < 0)
                    maxScroll = 0;

                if (cursor >= itemsInRow * itemsInCol) {
                    inventoryRight->scroll += 1;

                    if (inventoryRight->scroll > maxScroll) {
                        inventoryRight->scroll = maxScroll;
                    }

                    cursor -= itemsInRow;
                }

                if (cursor + inventoryRight->scroll * itemsInRow >= inventoryRight->inventory->items.size()) {
                    cursor = inventoryRight->inventory->items.size() - inventoryRight->scroll * itemsInRow - 1;
                }
            }
            else
                cursor = 0;
            
        }

        if (activePanel == activeInventoryPanel::Left) {

            if (inventoryLeft->inventory->items.size() > 0) {
                if ((cursor / itemsInRow * itemsInRow) + itemsInRow < inventoryLeft->inventory->items.size())
                    cursor += itemsInRow;

                int maxScroll = (inventoryLeft->inventory->items.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                if (maxScroll < 0)
                    maxScroll = 0;

                if (cursor >= itemsInRow * itemsInCol) {
                    inventoryLeft->scroll += 1;

                    if (inventoryLeft->scroll > maxScroll)
                        inventoryLeft->scroll = maxScroll;

                    cursor -= itemsInRow;
                }

                if (cursor + inventoryLeft->scroll * itemsInRow >= inventoryLeft->inventory->items.size()) {
                    cursor = inventoryLeft->inventory->items.size() - inventoryLeft->scroll * itemsInRow - 1;
                }
            }
            else
                cursor = 0;
            
            
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

        if (activePanel == activeInventoryPanel::Left) {

            if (inventoryLeft->inventory->items.size() > 0) {
                if (cursor < inventoryLeft->inventory->items.size()) {

                    transferItem(inventoryLeft->inventory->items[cursor + inventoryLeft->scroll * itemsInRow], inventoryLeft->inventory, inventoryRight->inventory);

                    if (cursor + inventoryLeft->scroll * itemsInRow >= inventoryLeft->inventory->items.size()) {

                        int maxScroll = (inventoryLeft->inventory->items.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                        if (maxScroll < 0)
                            maxScroll = 0;

                        if (inventoryLeft->scroll > maxScroll) {
                            cursor = cursor + (inventoryLeft->scroll - maxScroll) * itemsInRow - 1;
                            inventoryLeft->scroll = maxScroll;
                        }
                        else {
                            if(cursor != 0)
                                cursor -= 1;
                        }
                            
                    }
                }
            }
        } 

        if (activePanel == activeInventoryPanel::Right) {
            if (inventoryRight->inventory->items.size() > 0) {
                if (cursor < inventoryRight->inventory->items.size()) {

                    transferItem(inventoryRight->inventory->items[cursor + inventoryRight->scroll * itemsInRow], inventoryRight->inventory, inventoryLeft->inventory);

                    if (cursor + inventoryRight->scroll * itemsInRow >= inventoryRight->inventory->items.size()) {

                        int maxScroll = (inventoryRight->inventory->items.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                        if (maxScroll < 0)
                            maxScroll = 0;

                        if (inventoryRight->scroll > maxScroll) {
                            cursor = cursor + (inventoryRight->scroll - maxScroll) * itemsInRow - 1;
                            inventoryRight->scroll = maxScroll;
                        }
                        else {
                            if(cursor != 0)
                                cursor -= 1;
                        }
                            
                    }

                }

            }
            else
                cursor = 0;
        }
    }


}

void dialogueEvents() {

    if (dialogueState == dialogueStates::dialogue) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

            if ((page + 1) * 5 < countOfLines)
                page += 1;
            else {
                if (currentDialogue->options.size() == 0) {
                    currentDialogue = nullptr;
                    gameState = gameStates::game;

                }
                else {
                    dialogueState = dialogueStates::choose;
                    chooseOption = 0;
                    dialogScroll = 0;
                }

            }
        }

    }

    else if (dialogueState == dialogueStates::choose) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

            if (availableOptions[chooseOption + dialogScroll].nextDialogueID != -1) {
                dialogueState = dialogueStates::dialogue;
                currentDialogue = getDialogue(availableOptions[chooseOption + dialogScroll].nextDialogueID);


                page = 0;
                dialogScroll = 0;
            }
            else
                gameState = gameStates::game;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

            if (chooseOption == 0 && dialogScroll > 0)
                dialogScroll -= 1;
            else if (chooseOption > 0)
                chooseOption -= 1;

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

            if (chooseOption + dialogScroll < availableOptions.size() - 1) {

                int maxScroll = availableOptions.size() - 5;

                if (maxScroll < 0)
                    maxScroll = 0;

                if (chooseOption >= 4 && dialogScroll < maxScroll)
                    dialogScroll += 1;
                else
                    chooseOption += 1;

            }
        }

    }

}

void journalEvents() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {

        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {

        gameState = gameStates::inventory;
        inventory = new InventoryPanel(player->bag);
        cursor = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        cursor -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        cursor += 1;
    }
}

#endif