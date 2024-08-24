#ifndef MapEditorPalette_hpp
#define MapEditorPalette_hpp

sf::Vector2f paletteButtonSize = sf::Vector2f(80.0f, 80.0f);
sf::Vector2f palettePosition;
std::vector < GameObject* > availableGameObjects;
std::vector < GameObject* > terrainGameObjects;
std::vector < GameObject* > floorGameObjects;
std::vector < GameObject* > buildingGameObjects;

sf::Color idleColor = sf::Color(192.0f, 192.0f, 192.0f);
sf::Color hoverColor = sf::Color(224.0f, 224.0f, 224.0f);
sf::Color pressedColor = sf::Color::White;

int paletteScroll;
int paletteCols;
int paletteRows;

enum class buttonState { idle, hover, pressed};
/*
    idle = normal state
    hover - button is hover by cursor
    pressed - button is pressed by click
*/

class Button {
public:

    sf::Vector2f position;
    sf::Sprite sprite;
    buttonState state;
    std::function<void()> func;
    sf::Time clickTime;

    Button() {
        sprite = sf::Sprite();
        state = buttonState::idle;
        func = { };
        
        clickTime = currentTime;
    }

    Button(Button* btn) {

        this->position = btn->position;
        this->sprite = btn->sprite;
        state = buttonState::idle;
        this->func = btn->func;

        clickTime = currentTime;
    }

    Button(Button* btn, sf::Vector2f position) {


        this->position = position;
        this->sprite = btn->sprite;
        state = buttonState::idle;
        this->func = btn->func;

        clickTime = currentTime;
    }

    Button(Texture* texture, sf::Vector2f position) {
        this->position = position;

        sprite = sf::Sprite();

        state = buttonState::idle;

        if (texture != nullptr) {
            sprite.setTexture(*texture->texture);
            sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
        }

        func = { };

        clickTime = currentTime;
    }

    virtual void setTexture(Texture* texture) {
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
    }

    virtual void setPosition(sf::Vector2f position) {
        this->position = position;
        sprite.setPosition(position);
    }

    virtual void changeColor() {

        if (state == buttonState::pressed) {
            sprite.setColor(pressedColor);
        }
        else if (state == buttonState::hover) {
            sprite.setColor(hoverColor);
        }
        else {
            sprite.setColor(idleColor);
        }
            
    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {
            state = buttonState::idle;
            changeColor();
        }
            
    }

    virtual void hover() {
        if (state != buttonState::pressed) {

            float w = sprite.getTexture()->getSize().x;
            float h = sprite.getTexture()->getSize().y;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                state = buttonState::hover;
                changeColor();
                GUIwasHover = true;
            }
        }
        else {
            // GUI WAS PRESSED
            GUIwasHover = true;
        }
    }

    virtual void click() {
        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {
            
            state = buttonState::pressed;
            changeColor();
            GUIwasClicked = true;
            clickTime = currentTime;

            if (func)
                func();
    
        }

    }

    virtual void update(float dt) {
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
    }

    virtual void draw() {

        window->draw(sprite);
    }
};

Button* buttonUp;
Button* buttonDown;

Button* btnMenuEmpty;
Button* btnMenuTerrain;
Button* btnMenuFloors;
Button* btnMenuFurnitures;
Button* btnMenuWalls;
Button* btnMenuMonsters;
Button* btnMenuPaths;
Button* btnMenuItems;
Button* btnMenuNatures;

Button* btnToolsCursor;
Button* btnToolsBrush;
Button* btnToolsRectBrush;
Button* btnToolsIncrease;
Button* btnToolsDecrease;
Button* btnToolsRectangle;
Button* btnToolsElipse;
Button* btnToolsFill;
Button* btnToolsEraser;

Button* selectedMenuButton;
Button* selectedPaletteButton;
Button* selectedTool;

toolType tool;
int brushSize;

class PaletteButton : public Button {
public:

    sf::Sprite objectSprite;
    GameObject* object;

    PaletteButton() : Button() {

        sprite.setTexture(*getTexture("GUI/slot2")->texture);
        sprite.setOrigin(40, 40);
        
        object = nullptr;
        
        state = buttonState::idle;
    }

    virtual void changeColor() {

        if (state == buttonState::pressed) {
            sprite.setColor(pressedColor);
            objectSprite.setColor(pressedColor);
        }
        else if (state == buttonState::hover) {
            sprite.setColor(hoverColor);
            objectSprite.setColor(hoverColor);
        }
        else {
            sprite.setColor(idleColor);
            objectSprite.setColor(idleColor);
        }

    }

    virtual void unclick() {
        if ((currentTime - clickTime).asSeconds() > 0.1f) {

            state = buttonState::idle;
            changeColor();

        }

    }

    virtual void hover() {
        if (state != buttonState::pressed) {

            float w = sprite.getTexture()->getSize().x;
            float h = sprite.getTexture()->getSize().y;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                changeColor();
                state = buttonState::hover;
                GUIwasHover = true;
            }
        }
        else {
            // GUI IS PRESSED
            GUIwasHover = true;
        }
    }

    void click(){
        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {
            
            changeColor();
            state = buttonState::pressed;
            GUIwasClicked = true;
            clickTime = currentTime;

            if (selectedPaletteButton == this) {
                
                selectedPaletteButton = nullptr;
                prefabToPaint = nullptr;
                tool = toolType::Cursor;
                selectedTool = btnToolsCursor;
            }
            else {
                
                if (object!=nullptr) {
                    selectedPaletteButton = this;
                    prefabToPaint = object;
                    if (prefabToPaint != nullptr && (prefabToPaint->type == gameObjectType::Terrain || prefabToPaint->type == gameObjectType::Floor))
                    {
                        if (!(tool == toolType::Brush || tool == toolType::RectBrush || tool == toolType::Rectangle || tool == toolType::Elipse || tool == toolType::Fill)) {
                            selectedTool = btnToolsBrush;
                            brushSize = 2;
                            tool = toolType::Brush;
                        }
                    }
                    else {
                        tool = toolType::AddGameObject;
                    }
                }

            }
                
        }

    }

    void setObject(GameObject* object) {

        this->object = object;

        if (object != nullptr) {
            objectSprite.setTexture(*getTexture(object->name)->texture);

            float tw = getTexture(object->name)->texture->getSize().x;
            float th = getTexture(object->name)->texture->getSize().y;
            objectSprite.setOrigin(tw / 2.0f, th / 2.0f);

            float scaleX = (paletteButtonSize.x - 16.0f) / tw; // 80px-16px ( 64px x 64px )
            float scaleY = (paletteButtonSize.y - 16.0f) / th; // 80px-16px ( 64px x 64px )
            objectSprite.setScale(scaleX, scaleY);
        }
    }

    void setPosition(sf::Vector2f position) {
        
        this->position = position;

        sprite.setPosition(position);
        objectSprite.setPosition(position);
    }

    void update(float dt) {

       
    }

    void draw() {
        window->draw(sprite);
        window->draw(objectSprite);
    }

};

std::vector < Button* > menuButtons;
std::vector < Button* > tools;
std::vector < PaletteButton* > palette;

void setTerrainObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& terrain : terrainGameObjects)
        availableGameObjects.push_back(terrain);

}

void setFloorsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& floor : floorGameObjects)
        availableGameObjects.push_back(floor);
}

void setFurnituresObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Furniture)
            availableGameObjects.push_back(p);
    }
}

void setMonstersObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Monster)
            availableGameObjects.push_back(p);
    }
}

void setPathsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Path)
            availableGameObjects.push_back(p);
    }
}

void setWallsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Wall)
            availableGameObjects.push_back(p);
    }
}

void setItemsObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& i : items)
        availableGameObjects.push_back(getPrefab(i->name));
}

void setNaturesObjectsToPalette() {
    paletteScroll = 0;

    availableGameObjects.clear();
    for (auto& p : prefabs) {
        if (p->type == gameObjectType::Nature)
            availableGameObjects.push_back(p);
    }
}

void scrollUp() {

    GUIwasClicked = true;

    if (paletteScroll > 0)
        paletteScroll -= 1;
}

void scrollDown() {
    GUIwasClicked = true;

    int maxValue = availableGameObjects.size() - paletteCols * paletteRows;
    if (maxValue < 0)
        maxValue = 0;

    if (paletteScroll * paletteRows < maxValue)
        paletteScroll += 1;
}

void createPalette() {

    // NAV BUTTONS

    paletteButtonSize = sf::Vector2f(80, 80);

    sf::Vector2f buttonSize = sf::Vector2f(320, 40);

    Texture* texUp = getTexture("GUI/wideArrowUp2");
    sf::Vector2f positionUp;
    positionUp.x = screenWidth / 2.f - buttonSize.x / 2.0f;
    positionUp.y = -screenHeight / 2.0f + buttonSize.y / 2.0f + paletteButtonSize.y;
    buttonUp = new Button(texUp, positionUp);
    buttonUp->func = scrollUp;

    Texture* texDown = getTexture("GUI/wideArrowDown2");
    sf::Vector2f positionDown;
    positionDown.x = screenWidth / 2.f - buttonSize.x / 2.0f;
    positionDown.y = screenHeight / 2.0f - buttonSize.y / 2.0f;
    buttonDown = new Button(texDown, positionDown);
    buttonDown->func = scrollDown;


    // MENU BUTTONS 
    btnMenuEmpty = new Button();
    btnMenuEmpty->setTexture(getTexture("GUI/menuButton"));

    btnMenuTerrain = new Button();
    btnMenuTerrain->setTexture(getTexture("GUI/menuButton-terrain"));
    btnMenuTerrain->func = []() {
        selectedMenuButton = btnMenuTerrain;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setTerrainObjectsToPalette();
        };

    btnMenuFloors = new Button();
    btnMenuFloors->setTexture(getTexture("GUI/menuButton-floors"));
    btnMenuFloors->func = []() {
        selectedMenuButton = btnMenuFloors;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setFloorsObjectsToPalette();
        };

    btnMenuFurnitures = new Button();
    btnMenuFurnitures->setTexture(getTexture("GUI/menuButton-furnitures"));
    btnMenuFurnitures->func = []() {
        selectedMenuButton = btnMenuFurnitures;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setFurnituresObjectsToPalette();
        };

    btnMenuWalls = new Button();
    btnMenuWalls->setTexture(getTexture("GUI/menuButton-walls"));
    btnMenuWalls->func = []() {
        selectedMenuButton = btnMenuWalls;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setWallsObjectsToPalette();
        };

    btnMenuMonsters = new Button();
    btnMenuMonsters->setTexture(getTexture("GUI/menuButton-monsters"));
    btnMenuMonsters->func = []() {
        selectedMenuButton = btnMenuMonsters;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setMonstersObjectsToPalette();
        };

    btnMenuPaths = new Button();
    btnMenuPaths->setTexture(getTexture("GUI/menuButton-paths"));
    btnMenuPaths->func = []() {
        selectedMenuButton = btnMenuPaths;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setPathsObjectsToPalette();
        };

    btnMenuItems = new Button();
    btnMenuItems->setTexture(getTexture("GUI/menuButton-items"));
    btnMenuItems->func = []() {
        selectedMenuButton = btnMenuItems;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setItemsObjectsToPalette();
        };

    btnMenuNatures = new Button();
    btnMenuNatures->setTexture(getTexture("GUI/menuButton-natures"));
    btnMenuNatures->func = []() {
        tool = toolType::Cursor;
        selectedMenuButton = btnMenuNatures;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        setNaturesObjectsToPalette();
        };

    // CREATE EMPTY MENU 
    menuButtons.clear();

    for (int i = 0; i <8; i++) {
        Texture* tex = getTexture("GUI/menuButton");
        sf::Vector2f position;
        position.x = screenWidth/2 -(i%4 * 80) - 40;
        position.y = -screenHeight/2 + (i/4)*40 +20;
        menuButtons.push_back(new Button(btnMenuEmpty, position));
    }

    paletteScroll = 0;
    paletteRows = 4;
    paletteCols = 7;

    // TERRAIN GAMEOBJECTS
    terrainGameObjects.clear();
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_0_grass", terrainType::grass));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_1_sands", terrainType::sands));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_2_water", terrainType::water));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_3_gravel", terrainType::gravel));

    // FLOOR GAMEOBJECTS
    floorGameObjects.clear();
    floorGameObjects.push_back(new FloorPrefab("floors/floor_0", floorType::floor_0));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_1", floorType::floor_1));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_2", floorType::floor_2));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_3", floorType::floor_3));

    // CREATE TOOLS
    
    btnToolsCursor = new Button();
    btnToolsCursor->setTexture(getTexture("GUI/smallbutton-cursor"));
    btnToolsCursor->func = []() {
        selectedTool = btnToolsCursor;
        tool = toolType::Cursor;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        };
    

    btnToolsBrush = new Button();
    btnToolsBrush->setTexture(getTexture("GUI/smallbutton-brush"));
    btnToolsBrush->func = []() {
        selectedTool = btnToolsBrush;
        tool = toolType::Brush;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };


    btnToolsRectBrush = new Button();
    btnToolsRectBrush->setTexture(getTexture("GUI/smallbutton-rect_brush"));
    btnToolsRectBrush->func = []() {
        selectedTool = btnToolsRectBrush;
        tool = toolType::RectBrush;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    btnToolsIncrease = new Button();
    btnToolsIncrease->setTexture(getTexture("GUI/smallbutton-increase"));
    btnToolsIncrease->func = []() {
        if (selectedTool == btnToolsBrush || selectedTool == btnToolsRectBrush || selectedTool == btnToolsEraser) {
            if (brushSize < 5) {
                brushSize++;
                setBrushSize(brushSize);

                coutBrush();
                cout << "\n\n";
            }
                
        }
        };
    

    btnToolsDecrease = new Button();
    btnToolsDecrease->setTexture(getTexture("GUI/smallbutton-decrease"));
    btnToolsDecrease->func = []() {
        if (selectedTool == btnToolsBrush || selectedTool == btnToolsRectBrush || selectedTool == btnToolsEraser) {
            if (brushSize > 0) {
                brushSize--;
                setBrushSize(brushSize);

                coutBrush();
                cout << "\n\n";
            }
                
            
        }
        };
    

    btnToolsRectangle = new Button();
    btnToolsRectangle->setTexture(getTexture("GUI/smallbutton-rectangle"));
    btnToolsRectangle->func = []() {
        selectedTool = btnToolsRectangle;
        tool = toolType::Rectangle;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    btnToolsElipse = new Button();
    btnToolsElipse->setTexture(getTexture("GUI/smallbutton-elipse"));
    btnToolsElipse->func = []() {
        selectedTool = btnToolsElipse;
        tool = toolType::Elipse;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    btnToolsFill = new Button();
    btnToolsFill->setTexture(getTexture("GUI/smallbutton-fill"));
    btnToolsFill->func = []() {
        selectedTool = btnToolsFill;
        tool = toolType::Fill;
        };
    

    btnToolsEraser = new Button();
    btnToolsEraser->setTexture(getTexture("GUI/smallbutton-eraser"));
    btnToolsEraser->func = []() {
        selectedTool = btnToolsEraser;
        selectedPaletteButton = nullptr;
        prefabToPaint = nullptr;
        tool = toolType::Eraser;
        if (prefabToPaint == nullptr) {
            prefabToPaint = availableGameObjects[1];
            selectedPaletteButton = palette[1];
        }
        };
    

    // EMPTY TOOLS
    Button* emptyButton = new Button();
    emptyButton->setTexture(getTexture("GUI/smallbutton"));
    
    //tools.push_back(btnToolsCursor);
    //tools.push_back(btnToolsBrush);
    //tools.push_back(btnToolsIncrease);
    //tools.push_back(btnToolsDecrease);
    //tools.push_back(btnToolsRectangleArea);
    //tools.push_back(btnToolsElipseArea);
    //tools.push_back(btnToolsFill);
    //tools.push_back(btnToolsEraser);

    sf::Vector2f sp;    // start position
    sp.x = screenWidth / 2.0f - paletteRows * paletteButtonSize.x + 20;
    sp.y = - screenHeight / 2.0f + paletteButtonSize.y * 2.0f - 20;

    tools.clear();

    tools.push_back(new Button(btnToolsCursor, sf::Vector2f(sp.x, sp.y)));
    tools.push_back(new Button(btnToolsBrush, sf::Vector2f(sp.x + 40, sp.y)));
    tools.push_back(new Button(btnToolsRectBrush, sf::Vector2f(sp.x + 80, sp.y)));
    tools.push_back(new Button(btnToolsIncrease, sf::Vector2f(sp.x + 120, sp.y)));
    tools.push_back(new Button(btnToolsDecrease, sf::Vector2f(sp.x + 160, sp.y)));
    tools.push_back(new Button(btnToolsRectangle, sf::Vector2f(sp.x + 200, sp.y)));
    tools.push_back(new Button(btnToolsElipse, sf::Vector2f(sp.x + 240, sp.y)));
    //tools.push_back(new Button(btnToolsFill, sf::Vector2f(sp.x + 280, sp.y)));    / /TO-DO
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x + 280, sp.y)));

    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x, sp.y + 40)));
    //tools.push_back(new Button(btnToolsEraser, sf::Vector2f(sp.x, sp.y+40))); // TO-DO
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+40, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+80, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+120, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+160, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+200, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+240, sp.y+40)));
    tools.push_back(new Button(emptyButton, sf::Vector2f(sp.x+280, sp.y+40)));

    brushSize = 0;
    setBrushSize(brushSize);

    // SLOTS AND PREFABS
    palette.clear();
    for (int i = 0; i < paletteCols * paletteRows; i++)
        palette.push_back(new PaletteButton());
}

void createMapEditorPalette() {
    
    createPalette();
    setTerrainObjectsToPalette();

    menuButtons[3] = btnMenuTerrain;
    menuButtons[2] = btnMenuNatures;
    menuButtons[1] = btnMenuPaths;
    menuButtons[0] = btnMenuMonsters;

    menuButtons[7] = btnMenuItems;
    menuButtons[6] = new Button(btnMenuEmpty);
    menuButtons[5] = new Button(btnMenuEmpty);
    menuButtons[4] = new Button(btnMenuEmpty);

    selectedMenuButton = btnMenuTerrain;
    selectedPaletteButton = nullptr;
    selectedTool = btnToolsCursor;
    tool = toolType::Cursor;

}

void createBuildingEditorPalette() {
    
    createPalette();
    setFloorsObjectsToPalette();

    menuButtons[3] = btnMenuFloors;
    menuButtons[2] = btnMenuFurnitures;
    menuButtons[1] = btnMenuWalls;
    menuButtons[0] = btnMenuItems;

    menuButtons[7] = new Button(btnMenuEmpty);
    menuButtons[6] = new Button(btnMenuEmpty);
    menuButtons[5] = new Button(btnMenuEmpty);
    menuButtons[4] = new Button(btnMenuEmpty);

    selectedMenuButton = btnMenuFloors;
    selectedPaletteButton = nullptr;
    selectedTool = btnToolsCursor;
    tool = toolType::Cursor;
}

void updatePalette() {

    // MENU
    for (int i = 0; i < 8; i++) {
        sf::Vector2f position;
        position.x = screenWidth / 2 - (i % 4 * 80) - 40;
        position.y = -screenHeight / 2 + (i / 4) * 40 + 20;
        menuButtons[i]->setPosition(position);

        if (menuButtons[i] == selectedMenuButton) {
            menuButtons[i]->state = buttonState::pressed;
            menuButtons[i]->changeColor();
        }

        menuButtons[i]->update(dt);
    }

    // NAV BUTTONS
    buttonUp->update(dt);
    buttonDown->update(dt);

    // TOOLS
    for (auto& tool : tools) {
        tool->update(dt);
    }

    if (selectedTool != nullptr) {
        selectedTool->state = buttonState::pressed;
        selectedTool->changeColor();
        selectedTool->update(dt);
    }

    // PALETTE SIZE
    (selectedMenuButton == btnMenuTerrain || selectedMenuButton == btnMenuFloors) ? paletteRows = 6 : paletteRows = 7;
    paletteCols = 4;

    // SLOTS AND PREFABS

    float scaleX, scaleY;
    float tw, th; // texture width, texture height

    int dist_x = paletteCols * paletteButtonSize.x - paletteButtonSize.x / 2;
    palettePosition.x = cam->position.x + screenWidth / 2.0f - dist_x;
    palettePosition.y = cam->position.y - screenHeight / 2.0f + paletteButtonSize.y;

    for (int i = 0; i < paletteCols * paletteRows; i++) {

        sf::Vector2f position;
        position.x = palettePosition.x + (i % paletteCols) * paletteButtonSize.x;
        position.y = palettePosition.y + (i / paletteCols) * paletteButtonSize.y + paletteButtonSize.y;
        
        if (selectedMenuButton == btnMenuTerrain || selectedMenuButton == btnMenuFloors)
            position.y += paletteButtonSize.y;

        palette[i]->objectSprite = sf::Sprite();
        palette[i]->sprite.setPosition(position);
        palette[i]->setObject(nullptr);
        palette[i]->changeColor();

        if (i + paletteScroll * paletteCols < availableGameObjects.size()) {

            palette[i]->setObject(availableGameObjects[i + paletteScroll * paletteCols]);
            palette[i]->setPosition(position);

        }

        palette[i]->update(dt);
    }

    if (selectedPaletteButton != nullptr) {
        selectedPaletteButton->state = buttonState::pressed;
        selectedPaletteButton->changeColor();
        selectedPaletteButton->update(dt);
    }

}

void drawPalette() {

    for (int i = 0; i < paletteCols*paletteRows; i++) {
        palette[i]->draw();
    }

    buttonUp->draw();
    buttonDown->draw();

    for (auto& button : menuButtons)
        button->draw();

    if (selectedMenuButton == btnMenuTerrain || selectedMenuButton == btnMenuFloors) {
        for (auto& tool : tools)
            tool->draw();
    }

    
}



#endif