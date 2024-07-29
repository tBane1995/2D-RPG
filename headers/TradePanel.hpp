#ifndef TradePanel_hpp
#define TradePanel_hpp

int itemsInRow = 6;
int itemsInCol = 4;
int slotSize = 80;
int cursor = 0;
enum class activeInventoryPanel { Left, Right };
activeInventoryPanel activePanel = activeInventoryPanel::Right;

class InventoryPanel {
public:
	
	Inventory* inventory;
	int position_x;
	int position_y;

	std::vector < sf::Sprite > slots;
	std::vector <sf::Sprite > items;
	bool drawSelector;
	sf::Sprite selector;

	InventoryPanel(Inventory* inventory, int position_x=0, int position_y=0) {
		this->inventory = inventory;
		this->position_x = position_x;
		this->position_y = position_y;


		// SLOTS
		for (int i = 0; i < itemsInRow * itemsInCol; i++) {
			slots.emplace_back();
			int x = cam->position.x + position_x - (itemsInRow / 2 - i % itemsInRow) * slotSize + slotSize / 2;
			int y = cam->position.y + position_y - (itemsInCol / 2 - i / itemsInRow) * slotSize + slotSize / 2;
			slots[i].setOrigin(slotSize / 2, slotSize / 2);
			slots[i].setPosition(x, y);
			slots[i].setTexture(*getTexture("GUI/slotTexture1")->texture);
		}

		// SELECTOR
		selector = sf::Sprite();
		selector.setTexture(*getTexture("GUI/slotSelectorTexture1")->texture);
		selector.setOrigin(slotSize / 2, slotSize / 2);
		
		drawSelector = false;
	}

	void update(int cursor) {

		// SLOTS
		for (int i = 0; i < itemsInRow * itemsInCol; i++) {
			int x = cam->position.x + position_x - (itemsInRow / 2 - i % itemsInRow) * slotSize + slotSize / 2;
			int y = cam->position.y + position_y - (itemsInCol / 2 - i / itemsInRow) * slotSize + slotSize / 2;
			slots[i].setPosition(x, y);
		}

		// ITEMS
		items.clear();
		if (inventory != nullptr) {
			for (int i = 0; i < itemsInRow * itemsInCol; i++) {

				if (i < inventory->items.size()) {

					Item* item = inventory->items[i];

					items.emplace_back();

					int x = cam->position.x + position_x - (itemsInRow / 2 - i % itemsInRow) * slotSize + slotSize / 2;
					int y = cam->position.y + position_y - (itemsInCol / 2 - i / itemsInRow) * slotSize + slotSize / 2;

					float twidth = item->texture->texture->getSize().x;
					float theight = item->texture->texture->getSize().y;
					items[i].setTexture(*item->texture->texture);
					items[i].setOrigin(twidth / 2, theight / 2);
					items[i].setPosition(x, y);
					items[i].setScale(64.0f / twidth, 64.0f / theight);
				}
			}
		}

		// SELECTOR
		if (cursor != -1) {
			
			drawSelector = true;

			int x = cam->position.x + position_x - (inventoryItemsInRow / 2 - cursor % inventoryItemsInRow) * slotSide + slotSide / 2;
			int y = cam->position.y + position_y - (inventoryItemsInCol / 2 - cursor / inventoryItemsInRow) * slotSide + slotSide / 2;
			
			selector.setPosition(x, y);
		}
		else {
			drawSelector = false;
		}
	}

	void draw() {
		for(auto &slot : slots)
			window->draw(slot);

		for (auto& item : items)
			window->draw(item);

		if (drawSelector)
			window->draw(selector);
	}
};

InventoryPanel* inventoryLeft;  // TO-DO - to delete
InventoryPanel* inventoryRight;  // TO-DO - to delete

void updateTradePanel() {
	
	if (activePanel == activeInventoryPanel::Left) {
		inventoryLeft->update(cursor);
		inventoryRight->update(-1);
	}

	if (activePanel == activeInventoryPanel::Right) {
		inventoryLeft->update(-1);
		inventoryRight->update(cursor);
	}

}
#endif