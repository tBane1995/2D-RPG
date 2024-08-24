#ifndef MapEditorPalette_hpp
#define MapEditorPalette_hpp

sf::Vector2f paletteButtonSize = sf::Vector2f(80.0f, 80.0f);
sf::Vector2f palettePosition;
std::vector < GameObject* > availableGameObjects;
std::vector < GameObject* > terrainGameObjects;
std::vector < GameObject* > floorGameObjects;
std::vector < GameObject* > buildingGameObjects;

int paletteScroll;
int paletteCols;
int paletteRows;

class Button {
public:

    Texture* texture;
    sf::Vector2f position;
    sf::Sprite sprite;
    bool mouseOver;

    Button(Texture* texture, sf::Vector2f position) {
        this->texture = texture;
        this->position = position;
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
    }

    bool mouseOvering(sf::Vector2f mousePosition) {
        float w = sprite.getTexture()->getSize().x;
        float h = sprite.getTexture()->getSize().y;
        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        if (mousePosition.x > x - w / 2.0f && mousePosition.x < x + w / 2.0f &&
            mousePosition.y > y - h / 2.0f && mousePosition.y < y + h / 2.0f) {
            mouseOver = true;
        }
        else
            mouseOver = false;

        return mouseOver;

    }

    void update() {
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
    }

    void draw() {
        window->draw(sprite);
    }
};

class PaletteButton {
public:
    Texture* slotTexture;
    sf::Sprite slotSprite;
    sf::Sprite objectSprite;
    GameObject* object;
    bool mouseOver;   // mouse over

    PaletteButton() {
        slotTexture = getTexture("GUI/slot2");
        slotSprite = sf::Sprite();
        slotSprite.setTexture(*slotTexture->texture);
        slotSprite.setOrigin(paletteButtonSize.x / 2.0f, paletteButtonSize.y / 2.0f);

        object = nullptr;

        objectSprite = sf::Sprite();
    }

    bool mouseOvering(sf::Vector2f mousePosition) {
        float w = slotSprite.getTexture()->getSize().x;
        float h = slotSprite.getTexture()->getSize().y;
        float x = slotSprite.getPosition().x;
        float y = slotSprite.getPosition().y;

        if (mousePosition.x > x - w / 2.0f && mousePosition.x < x + w / 2.0f &&
            mousePosition.y > y - h / 2.0f && mousePosition.y < y + h / 2.0f) {
            mouseOver = true;
        }
        else
            mouseOver = false;

        return mouseOver;

    }

    void setObject(GameObject* object) {
        this->object = object;
    }

    void draw() {
        window->draw(slotSprite);
        window->draw(objectSprite);
    }

};

Button* buttonUp;
Button* buttonDown;
std::vector < PaletteButton > palette;

void createPalette() {

    paletteButtonSize = sf::Vector2f(80, 80);

    paletteCols = 4;
    paletteRows = 8;

    sf::Vector2f buttonSize = sf::Vector2f(320, 40);

    Texture* texUp = getTexture("GUI/wideArrowUp2");
    sf::Vector2f positionUp;
    positionUp.x = screenWidth / 2.f - buttonSize.x / 2.0f;
    positionUp.y = -screenHeight / 2.0f + buttonSize.y / 2.0f;
    buttonUp = new Button(texUp, positionUp);

    Texture* texDown = getTexture("GUI/wideArrowDown2");
    sf::Vector2f positionDown;
    positionDown.x = screenWidth / 2.f - buttonSize.x / 2.0f;
    positionDown.y = screenHeight / 2.0f - buttonSize.y / 2.0f;
    buttonDown = new Button(texDown, positionDown);

    // slots & prefabs
    for (int i = 0; i < paletteCols * paletteRows; i++)
        palette.push_back(PaletteButton());

    paletteScroll = 0;

    // Terrain GameObjects
    terrainGameObjects.clear();
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_0_grass", terrainType::grass));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_1_sands", terrainType::sands));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_2_water", terrainType::water));
    terrainGameObjects.push_back(new TerrainPrefab("tiles/tile_3_gravel", terrainType::gravel));

    floorGameObjects.clear();
    floorGameObjects.push_back(new FloorPrefab("floors/floor_0", floorType::floor_0));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_1", floorType::floor_1));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_2", floorType::floor_2));
    floorGameObjects.push_back(new FloorPrefab("floors/floor_3", floorType::floor_3));

}

void createMapEditorPalette() {
    
    createPalette();

    availableGameObjects.clear();

    // adding terrains
    for (auto& terrain : terrainGameObjects)
        availableGameObjects.push_back(terrain);

    // adding floors
    for (auto& floor : floorGameObjects)
        availableGameObjects.push_back(floor);

    // adding prefabs (GameObjects)
    int i = 0;
    while (i < prefabs.size()) {
        if (
            prefabs[i]->type == gameObjectType::GameObject ||
            prefabs[i]->type == gameObjectType::Furniture ||
            prefabs[i]->type == gameObjectType::Nature ||
            prefabs[i]->type == gameObjectType::Path ||
            prefabs[i]->type == gameObjectType::Monster ||
            prefabs[i]->type == gameObjectType::Wall
            )
            availableGameObjects.push_back(prefabs[i]);
        i++;
    }

    // adding items (herbs, ... )
    i = 0;
    while (i < items.size()) {
        availableGameObjects.push_back(getPrefab(items[i]->name));
        i++;
    }
}

void createBuildingEditorPalette() {
    
    createPalette();

    availableGameObjects.clear();

    // adding floors
    for (auto& floor : floorGameObjects)
        availableGameObjects.push_back(floor);

    // adding prefabs (GameObjects)
    int i = 0;
    while (i < prefabs.size()) {
        if (
            prefabs[i]->type == gameObjectType::GameObject ||
            prefabs[i]->type == gameObjectType::Furniture ||
            prefabs[i]->type == gameObjectType::Wall
            )
            availableGameObjects.push_back(prefabs[i]);
        i++;
    }

    // adding items (herbs, ... )
    i = 0;
    while (i < items.size()) {
        availableGameObjects.push_back(getPrefab(items[i]->name));
        i++;
    }
}

void updatePalette() {

    float scaleX, scaleY;
    float tw, th; // texture width, texture height

    int dist_x = paletteCols * paletteButtonSize.x - paletteButtonSize.x / 2;
    palettePosition.x = cam->position.x + screenWidth / 2.0f - dist_x;
    palettePosition.y = cam->position.y - screenHeight / 2.0f + paletteButtonSize.y;

    for (int i = 0; i < paletteCols * paletteRows; i++) {

        sf::Vector2f position;
        position.x = palettePosition.x + (i % paletteCols) * paletteButtonSize.x;
        position.y = palettePosition.y + (i / paletteCols) * paletteButtonSize.y;
        
        palette[i].slotSprite.setPosition(position);
        palette[i].objectSprite = sf::Sprite();

        
        if (i + paletteScroll * paletteCols < availableGameObjects.size()) {

            palette[i].object = availableGameObjects[i + paletteScroll * paletteCols];
            palette[i].objectSprite.setTexture(*getTexture(palette[i].object->name)->texture);

            palette[i].objectSprite.setPosition(position);

            tw = palette[i].objectSprite.getTexture()->getSize().x;
            th = palette[i].objectSprite.getTexture()->getSize().y;
            palette[i].objectSprite.setOrigin(tw / 2.0f, th / 2.0f);

            scaleX = (paletteButtonSize.x - 16.0f) / tw; // 80px-16px ( 64px x 64px )
            scaleY = (paletteButtonSize.y - 16.0f) / th; // 80px-16px ( 64px x 64px )
            palette[i].objectSprite.setScale(scaleX, scaleY);

            if (!palette[i].mouseOver)
                palette[i].objectSprite.setColor(sf::Color(192.0f, 192.0f, 192.0f));

        }
        
    }

    buttonUp->update();
    buttonDown->update();
}

void drawPalette() {

    for (int i = 0; i < palette.size(); i++) {
        palette[i].draw();
    }

    buttonUp->draw();
    buttonDown->draw();
}


#endif