#ifndef InventoryPanel_hpp
#define InventoryPanel_hpp

int inventoryItemsInRow = 6;
int inventoryItemsInCol = 6;
int slotSide = 80;

sf::Texture slotTexture;
Inventory** currentInventory;
std::vector < sf::Sprite > itemsInventorySprites;
std::vector < sf::Sprite > slotInventorySprites;
std::vector < sf::Text > inventoryCounts;

sf::Texture selectorTexture;
sf::Sprite selector;
int bagCursor;

void createInventoryPanel() {

    // EMPTY SLOTS
    slotTexture = sf::Texture();
    slotTexture.loadFromFile("assets/GUI/slotTexture1.png");

    for (int i = 0; i < inventoryItemsInRow * inventoryItemsInCol; i++) {
        slotInventorySprites.emplace_back();
        int x = cam->position.x - (inventoryItemsInRow / 2 - i % inventoryItemsInRow) * slotSide + slotSide/2;
        int y = cam->position.y - (inventoryItemsInCol / 2 - i / inventoryItemsInRow) * slotSide + slotSide/2;
        slotInventorySprites[i].setOrigin(slotSide / 2, slotSide / 2);
        slotInventorySprites[i].setPosition(x, y);
        slotInventorySprites[i].setTexture(slotTexture);

    }

    // SELECTOR
    selectorTexture = sf::Texture();
    selectorTexture.loadFromFile("assets/GUI/slotSelectorTexture1.png");
    selector = sf::Sprite();
    selector.setTexture(selectorTexture);
    selector.setOrigin(slotSide/2, slotSide/2);

    currentInventory = &player->bag;
    bagCursor = 0;

}

void setInventoryPanel(Inventory*& inventory) {

    currentInventory = &inventory;
}

void updateInventoryPanel() {

    itemsInventorySprites.clear();
    inventoryCounts.clear();

    if ((*currentInventory) == nullptr)
        bagCursor = 0;

    
    if ((*currentInventory) != nullptr && bagCursor >= (*currentInventory)->items.size()) {
        bagCursor = (*currentInventory)->items.size() - 1;
    }
    
    if (bagCursor < 0)
        bagCursor = 0;

    int x, y, width, height;
    
    if ((*currentInventory) != nullptr) {

        for (int i = 0; i < inventoryItemsInRow * inventoryItemsInCol; i++) {
            x = cam->position.x - (inventoryItemsInRow / 2 - i % inventoryItemsInRow) * slotSide + slotSide/2;
            y = cam->position.y - (inventoryItemsInCol / 2 - i / inventoryItemsInRow) * slotSide + slotSide/2;
            slotInventorySprites[i].setPosition(x, y);

            if (i < (*currentInventory)->items.size()) {

                itemsInventorySprites.emplace_back();
                string location = (*currentInventory)->items[i]->name;
                float twidth = getTexture(location)->texture->getSize().x;
                float theight = getTexture(location)->texture->getSize().y;
                itemsInventorySprites[i].setTexture(*getTexture(location)->texture);
                itemsInventorySprites[i].setOrigin(twidth/2, theight/2);
                itemsInventorySprites[i].setPosition(x, y);
                itemsInventorySprites[i].setScale(64.0f / twidth, 64.0f / theight);


                inventoryCounts.emplace_back(to_string((*currentInventory)->counts[i]), basicFont, 16);
                inventoryCounts[i].setPosition(x, y);
                width = inventoryCounts[i].getLocalBounds().width;
                height = inventoryCounts[i].getLocalBounds().height;
                inventoryCounts[i].setOrigin(width / 2, height / 2);
                inventoryCounts[i].setPosition(x - width / 2 + 24, y - height / 2 + 24);
                inventoryCounts[i].setFillColor(textNameColor);
            }
        }
    }
    
    x = cam->position.x - (inventoryItemsInRow / 2 - bagCursor % inventoryItemsInRow) * slotSide + slotSide/2;
    y = cam->position.y - (inventoryItemsInCol / 2 - bagCursor / inventoryItemsInRow) * slotSide + slotSide/2;
    //cout << x << " " << y << "\n";
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

void useItem() {

    // TO-DO
    Item* item = (*currentInventory)->items[bagCursor];
    
    if (item->type == itemType::herb || item->type == itemType::potion || item->type == itemType::food) {
        player->heal(item->attributes[attribute::HP]);
        (*currentInventory)->removeItem((*currentInventory)->items[bagCursor]);
    }

    if (item->type == itemType::helmet) {

        if (player->helmet != nullptr)
            player->bag->addItem(player->helmet);

        player->helmet = item;
        player->bag->removeItem(item);
        player->loadHelmet();
    }

    if (item->type == itemType::armor) {

        if (player->armor != nullptr)
            player->bag->addItem(player->armor);

        player->armor = item;
        player->bag->removeItem(item);
        player->loadArmor();
    }

    if (item->type == itemType::pants) {

        if (player->pants != nullptr)
            player->bag->addItem(player->pants);

        player->pants = item;
        player->bag->removeItem(item);
        player->loadPants();
    }

    
}


#endif