#ifndef InventoryPanel_hpp
#define InventoryPanel_hpp

int inventoryItemsInRow = 6;
int inventoryItemsInCol = 6;

sf::Texture slotTexture;
Inventory* inventory;
std::vector < sf::Sprite > itemsInventorySprites;
std::vector < sf::Sprite > slotInventorySprites;
std::vector < sf::Text > inventoryCounts;

sf::Texture selectorTexture;
sf::Sprite selector;
int bagCursor;

void createInventoryPanel() {

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

    inventory = player->bag;
    bagCursor = 0;

}

void setInventoryPanel(Inventory* i) {

    inventory = i;
}

void updateInventoryPanel() {
    // TO-DO

    itemsInventorySprites.clear();
    inventoryCounts.clear();

    if (inventory!=nullptr && bagCursor >= inventory->items.size())
        bagCursor = inventory->items.size() - 1;

    if (bagCursor < 0)
        bagCursor = 0;

    int x, y, width, height;

    // TO-DO
    for (int i = 0; i < inventoryItemsInRow * inventoryItemsInCol; i++) {
        x = cam->position.x - (inventoryItemsInRow / 2 - i % inventoryItemsInRow) * 80 + 40;
        y = cam->position.y - (inventoryItemsInCol / 2 - i / inventoryItemsInRow) * 80 + 40;
        slotInventorySprites[i].setPosition(x, y);

        if (inventory != nullptr) {

            if (i < inventory->items.size()) {
                itemsInventorySprites.emplace_back();
                string location = inventory->items[i]->location;
                itemsInventorySprites[i].setPosition(x, y);
                itemsInventorySprites[i].setOrigin(32, 32);
                itemsInventorySprites[i].setTexture(*getTexture(location)->texture);

                inventoryCounts.emplace_back(to_string(inventory->counts[i]), basicFont, 16);
                inventoryCounts[i].setPosition(x, y);
                width = inventoryCounts[i].getLocalBounds().width;
                height = inventoryCounts[i].getLocalBounds().height;
                inventoryCounts[i].setOrigin(width / 2, height / 2);
                inventoryCounts[i].setPosition(x - width / 2 + 24, y - height / 2 + 24);
                inventoryCounts[i].setFillColor(textNameColor);
            }
        }
    }

    // TO-DO
    x = cam->position.x - (inventoryItemsInRow / 2 - bagCursor % inventoryItemsInRow) * 80 + 40;
    y = cam->position.y - (inventoryItemsInCol / 2 - bagCursor / inventoryItemsInRow) * 80 + 40;
    cout << x << " " << y << "\n";
    selector.setPosition(x, y);

}

void drawInventoryPanel() {

    for (auto& spr : slotInventorySprites) {
        window->draw(spr);
    }

    for (auto& spr : itemsInventorySprites) {
        window->draw(spr);
    }

    for (auto& t : inventoryCounts) {
        window->draw(t);
    }


    window->draw(selector);
}

#endif