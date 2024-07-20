#ifndef PlayerInventory_hpp
#define PlayerInventory_hpp

int inventoryItemsInRow = 6;
int inventoryItemsInCol = 6;
sf::RectangleShape bgInventory;
sf::Texture slotTexture;
sf::Texture selectorTexture;
std::vector < sf::Sprite > itemsInventorySprites;
std::vector < sf::Sprite > slotInventorySprites;
std::vector < sf::Text > inventoryCounts;
sf::Text itemName; // TO-DO
sf::Sprite selector;
int bagCursor = 0;

void createInventory() {

    // TO-DO
    // 
    // BACKGROUND
    bgInventory = sf::RectangleShape(sf::Vector2f(80 * inventoryItemsInRow, 80 * inventoryItemsInCol));
    bgInventory.setFillColor(sf::Color(140, 85, 11));
    bgInventory.setOrigin(80 * inventoryItemsInRow / 2, 80 * inventoryItemsInCol / 2);

    // SLOTS
    slotTexture = sf::Texture();
    slotTexture.loadFromFile("assets/GUI/slotTexture1.png");

    for (int i = 0; i < inventoryItemsInRow * inventoryItemsInCol; i++) {
        slotInventorySprites.emplace_back();
        int x = cam->position.x - (inventoryItemsInRow / 2 - i % inventoryItemsInRow) * 80 + 40;
        int y = cam->position.y - (inventoryItemsInCol / 2 - i / inventoryItemsInRow) * 80 + 40;
        slotInventorySprites[i].setPosition(x, y);
        slotInventorySprites[i].setOrigin(40, 40);
        slotInventorySprites[i].setTexture(slotTexture);

    }

    // SELECTOR
    selectorTexture = sf::Texture();
    selectorTexture.loadFromFile("assets/GUI/slotSelectorTexture1.png");
    selector = sf::Sprite();
    selector.setTexture(selectorTexture);
    selector.setOrigin(40.0f, 40.0f);

    itemName = sf::Text();
    itemName.setFont(basicFont);
    itemName.setCharacterSize(32.0f);
}

void updateInventory() {
    // TO-DO

    itemsInventorySprites.clear();
    inventoryCounts.clear();

    if (bagCursor >= player->bag->items.size())
        bagCursor = player->bag->items.size() - 1;

    if (bagCursor < 0)
        bagCursor = 0;

    bgInventory.setPosition(cam->position.x, cam->position.y);

    int x, y, width, height;

    // TO-DO
    // TO-DO for items count > itemsInRow*itemsInCol
    for (int i = 0; i < inventoryItemsInRow * inventoryItemsInCol; i++) {
        x = cam->position.x - (inventoryItemsInRow / 2 - i % inventoryItemsInRow) * 80 + 40;
        y = cam->position.y - (inventoryItemsInCol / 2 - i / inventoryItemsInRow) * 80 + 40;
        slotInventorySprites[i].setPosition(x, y);

        if (i < player->bag->items.size()) {
            itemsInventorySprites.emplace_back();
            string location = player->bag->items[i]->location;
            itemsInventorySprites[i].setPosition(x, y);
            itemsInventorySprites[i].setOrigin(32, 32);
            itemsInventorySprites[i].setTexture(*getTexture(location)->texture);

            inventoryCounts.emplace_back(to_string(player->bag->counts[i]), basicFont, 16);
            inventoryCounts[i].setPosition(x, y);
            width = inventoryCounts[i].getLocalBounds().width;
            height = inventoryCounts[i].getLocalBounds().height;
            inventoryCounts[i].setOrigin(width / 2, height / 2);
            inventoryCounts[i].setPosition(x - width / 2 + 24, y - height / 2 + 24);
            inventoryCounts[i].setFillColor(textNameColor);
        }
    }

    // TO-DO
    x = cam->position.x - (inventoryItemsInRow / 2 - bagCursor % inventoryItemsInRow) * 80 + 40;
    y = cam->position.y - (inventoryItemsInCol / 2 - bagCursor / inventoryItemsInRow) * 80 + 40;

    selector.setPosition(x, y);
    string location;
    if (bagCursor >= player->bag->items.size())
        location = "";
    else
        location = player->bag->items[bagCursor]->location;
    itemName.setString(location);
    itemName.setPosition(cam->position.x, cam->position.y - 270);
    itemName.setOrigin(itemName.getLocalBounds().width / 2.0f, itemName.getLocalBounds().height / 2.0f);
    itemName.setFillColor(textNameColor);
}

#endif