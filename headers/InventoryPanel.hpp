#ifndef InventoryPanel_hpp
#define InventoryPanel_hpp

int itemsInRow = 6;
int itemsInCol = 4;
int slotSide = 80;
int cursor = 0;

class InventoryPanel {
public:

	Inventory* inventory;
	int position_x;
	int position_y;

	std::vector < sf::Sprite > slots;
	std::vector <sf::Sprite > items;
	std::vector < sf::Text > counts;
	bool drawSelector;
	sf::Sprite selector;

	InventoryPanel(Inventory* inventory, int position_x = 0, int position_y = 0) {
		this->inventory = inventory;
		this->position_x = position_x;
		this->position_y = position_y;


		// SLOTS
		for (int i = 0; i < itemsInRow * itemsInCol; i++) {
			slots.emplace_back();
			int x = cam->position.x + position_x - (itemsInRow / 2 - i % itemsInRow) * slotSide + slotSide / 2;
			int y = cam->position.y + position_y - (itemsInCol / 2 - i / itemsInRow) * slotSide + slotSide / 2;
			slots[i].setOrigin(slotSide / 2, slotSide / 2);
			slots[i].setPosition(x, y);
			slots[i].setTexture(*getTexture("GUI/slotTexture1")->texture);
		}

		// SELECTOR
		selector = sf::Sprite();
		selector.setTexture(*getTexture("GUI/slotSelectorTexture1")->texture);
		selector.setOrigin(slotSide / 2, slotSide / 2);

		drawSelector = false;
	}

	void update(int cursor) {

		// SLOTS
		for (int i = 0; i < itemsInRow * itemsInCol; i++) {
			int x = cam->position.x + position_x - (itemsInRow / 2 - i % itemsInRow) * slotSide + slotSide / 2;
			int y = cam->position.y + position_y - (itemsInCol / 2 - i / itemsInRow) * slotSide + slotSide / 2;
			slots[i].setPosition(x, y);
			slots[i].setColor(sf::Color::White);
		}

		// ITEMS
		items.clear();
		counts.clear();
		if (inventory != nullptr) {
			for (int i = 0; i < itemsInRow * itemsInCol; i++) {

				if (i < inventory->items.size()) {

					Item* item = inventory->items[i];

					if (item == player->helmet || item == player->armor || item == player->pants)
						slots[i].setColor(sf::Color::Red);

					items.emplace_back();

					int x = cam->position.x + position_x - (itemsInRow / 2 - i % itemsInRow) * slotSide + slotSide / 2;
					int y = cam->position.y + position_y - (itemsInCol / 2 - i / itemsInRow) * slotSide + slotSide / 2;

					float twidth = item->texture->texture->getSize().x;
					float theight = item->texture->texture->getSize().y;
					items[i].setTexture(*item->texture->texture);
					items[i].setOrigin(twidth / 2, theight / 2);
					items[i].setPosition(x, y);
					items[i].setScale(64.0f / twidth, 64.0f / theight);

					counts.emplace_back(to_string(inventory->counts[i]), basicFont, 16);
					counts[i].setPosition(x, y);
					int width = counts[i].getLocalBounds().width;
					int height = counts[i].getLocalBounds().height;
					counts[i].setOrigin(width / 2, height / 2);
					counts[i].setPosition(x - width / 2 + 24, y - height / 2 + 24);
					counts[i].setFillColor(textNameColor);

				}
			}
		}

		// SELECTOR
		if (cursor != -1) {

			drawSelector = true;

			int x = cam->position.x + position_x - (itemsInRow / 2 - cursor % itemsInRow) * slotSide + slotSide / 2;
			int y = cam->position.y + position_y - (itemsInCol / 2 - cursor / itemsInRow) * slotSide + slotSide / 2;

			selector.setPosition(x, y);
		}
		else {
			drawSelector = false;
		}
	}

	void draw() {
		for (auto& slot : slots)
			window->draw(slot);

		for (auto& item : items)
			window->draw(item);

		for (auto& count : counts)
			window->draw(count);

		if (drawSelector)
			window->draw(selector);
	}
};

InventoryPanel* inventory;

sf::Sprite background;
sf::Sprite itemSprite;
sf::Text itemName;
sf::Text itemDescription;
bool drawItemStats;

void updateInventoryPanel() {

	inventory->update(cursor);
	
	drawItemStats = false;
	
	background = sf::Sprite();
	background.setTexture(*getTexture("GUI/dialogBoxTexture")->texture);
	background.setPosition(cam->position.x, cam->position.y + 275);
	background.setOrigin(300,75);

	Item* item = nullptr;
	
	if (inventory->inventory != nullptr && cursor < inventory->inventory->items.size())
		item = inventory->inventory->items[cursor];

	if (item!=nullptr)
	{
		drawItemStats = true;
		itemSprite = sf::Sprite();
		itemSprite.setTexture(*item->texture->texture);
		itemSprite.setOrigin(32, 32);
		itemSprite.setScale(2, 2);
		itemSprite.setPosition(cam->position.x-300+80, cam->position.y+275);

		itemName = sf::Text();
		itemName.setCharacterSize(28);
		itemName.setFillColor(textDialogueColor);
		itemName.setFont(basicFont);
		itemName.setPosition(cam->position.x-300 + 192, cam->position.y+275-64);
		itemName.setString(getItemName(inventory->inventory->items[cursor]));

		itemDescription = sf::Text();
		itemDescription.setCharacterSize(16);
		itemDescription.setFillColor(textDialogueColor);
		itemDescription.setFont(basicFont);
		itemDescription.setPosition(cam->position.x - 300 + 192, cam->position.y + 275 - 32);
		itemDescription.setString(getItemDescription(inventory->inventory->items[cursor]));
	}
	
}

void drawInventoryPanel() {
	
	inventory->draw();
	window->draw(background);
	if (drawItemStats == true){
		window->draw(itemSprite);
		window->draw(itemName);
		window->draw(itemDescription);
	}
}

void useItem() {
    
	if (inventory == nullptr)
		return;

	if (inventory->inventory == nullptr)
		return;

	if (cursor >= inventory->inventory->items.size())
		return;

	Item* item = inventory->inventory->items[cursor];

    if (item->type == itemType::herb || item->type == itemType::potion || item->type == itemType::food) {
        player->heal(item->attributes[attribute::HP]);
		inventory->inventory->removeItem(item);
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