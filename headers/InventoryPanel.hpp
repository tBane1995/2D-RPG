#ifndef InventoryPanel_hpp
#define InventoryPanel_hpp

int inventoryItemsInRow = 6;
int inventoryItemsInCol = 4;
int slotSide = 80;

sf::Texture slotTexture;
Inventory** currentInventory;
std::vector < sf::Sprite > itemsInventorySprites;
std::vector < sf::Sprite > slotInventorySprites;
std::vector < sf::Text > inventoryCounts;

sf::Texture selectorTexture;
sf::Sprite selector;
int bagCursor;

sf::Texture infoPanelTexture;
sf::Sprite infoPanelSprite;

sf::Sprite itemSprite;
sf::Text itemName;
sf::Text itemDescription;

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

    // INFO PANEL
    infoPanelTexture = sf::Texture();
    infoPanelTexture.loadFromFile("assets/GUI/dialogBoxTexture.png");

    infoPanelSprite = sf::Sprite();
    infoPanelSprite.setTexture(infoPanelTexture);
    infoPanelSprite.setOrigin(300, 75);

    itemSprite = sf::Sprite();
    itemSprite.setOrigin(32, 32);
    itemSprite.setScale(2, 2);

    itemName = sf::Text();
    itemName.setFont(basicFont);
    itemName.setCharacterSize(30);
    itemName.setFillColor(textDialogueColor);

    itemDescription = sf::Text();
    itemDescription.setFont(basicFont);
    itemDescription.setCharacterSize(16);
    itemDescription.setFillColor(textDialogueColor);

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
            slotInventorySprites[i].setColor(sf::Color::White);

            if (i < (*currentInventory)->items.size()) {

                Item* item = (*currentInventory)->items[i];
                
                if (item == player->helmet || item == player->armor || item == player->pants)
                    slotInventorySprites[i].setColor(sf::Color::Red);

                itemsInventorySprites.emplace_back();
                float twidth = item->texture->texture->getSize().x;
                float theight = item->texture->texture->getSize().y;
                itemsInventorySprites[i].setTexture(*item->texture->texture);
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

    selector.setPosition(x, y);

    // PANEL INFO
    int position_y = cam->position.y + float(inventoryItemsInCol) / 2.0f * float(slotSide) + 75 + 24;
    int position_x = cam->position.x;

    infoPanelSprite.setPosition(position_x, position_y);

    itemSprite.setPosition(position_x - 300 + 64 + 11, position_y);

    if ((*currentInventory) != nullptr) {
        
        // ITEM NAME
        Item* item = (*currentInventory)->items[bagCursor];
        
        itemSprite.setTexture(*item->texture->texture);

        itemName.setPosition(position_x -75, position_y-75+11);
        itemName.setString(getItemName(item));
    
        // DESCRIPTION
        itemDescription.setPosition(position_x - 75, position_y - 75 + 11 + 48);
        itemDescription.setString(getItemDescription(item));
    }


    
    
}

void drawInventoryPanel() {

    for (auto& spr : slotInventorySprites)
        window->draw(spr);

    for (auto& spr : itemsInventorySprites)
        window->draw(spr);

    for (auto& t : inventoryCounts)
        window->draw(t);

    window->draw(selector);

    window->draw(infoPanelSprite);
    window->draw(itemSprite);
    window->draw(itemName);
    window->draw(itemDescription);
}

void useItem() {

    // TO-DO
    Item* item = (*currentInventory)->items[bagCursor];
    
    if (item->type == itemType::herb || item->type == itemType::potion || item->type == itemType::food) {
        player->heal(item->attributes[attribute::HP]);
        (*currentInventory)->removeItem((*currentInventory)->items[bagCursor]);
    }

    if (item->type == itemType::helmet) {

        if (player->helmet == item)
            player->helmet = nullptr;
        else
            player->helmet = item;
        
        player->loadHelmet();
    }

    if (item->type == itemType::armor) {
        
        if (player->armor == item)
            player->armor = nullptr;
        else
        player->armor = item;
        
        player->loadArmor();
    }

    if (item->type == itemType::pants) {

        if (player->pants == item)
            player->pants = nullptr;
        else
            player->pants = item;
        
        player->loadPants();
    }

    
}


#endif