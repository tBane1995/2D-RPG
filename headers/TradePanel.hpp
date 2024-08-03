#ifndef TradePanel_hpp
#define TradePanel_hpp


enum class activeInventoryPanel { Left, Right };
activeInventoryPanel activePanel = activeInventoryPanel::Right;

InventoryPanel* inventoryLeft;
InventoryPanel* inventoryRight;

void updateTradePanel() {
	
	Item* item = nullptr;

	if (activePanel == activeInventoryPanel::Left) {
		inventoryLeft->update(cursor);
		inventoryRight->update(-1);

		if (inventoryLeft->inventory != nullptr )
			if(inventoryLeft->inventory->items.size() > 0 )
				if(cursor < inventoryLeft->inventory->items.size())
					item = inventoryLeft->inventory->items[cursor];
	}

	if (activePanel == activeInventoryPanel::Right) {
		inventoryLeft->update(-1);
		inventoryRight->update(cursor);

		if (inventoryRight->inventory != nullptr)
			if (inventoryRight->inventory->items.size() > 0)
				if (cursor < inventoryRight->inventory->items.size())
					item = inventoryRight->inventory->items[cursor];
	}
	
	drawItemStats = false;

	background = sf::Sprite();
	background.setTexture(*getTexture("GUI/dialogBoxTexture")->texture);
	background.setPosition(cam->position.x, cam->position.y + 275);
	background.setOrigin(300, 75);

	if (item != nullptr)
	{
		drawItemStats = true;

		itemSprite = sf::Sprite();
		itemSprite.setTexture(*item->texture->texture);
		itemSprite.setOrigin(32, 32);
		itemSprite.setScale(2, 2);
		itemSprite.setPosition(cam->position.x - 300 + 80, cam->position.y + 275);

		itemName = sf::Text();
		itemName.setCharacterSize(28);
		itemName.setFillColor(textDialogueColor);
		itemName.setFont(basicFont);
		itemName.setPosition(cam->position.x - 300 + 192, cam->position.y + 275 - 64);
		itemName.setString(getItemName(item));

		itemDescription = sf::Text();
		itemDescription.setCharacterSize(16);
		itemDescription.setFillColor(textDialogueColor);
		itemDescription.setFont(basicFont);
		itemDescription.setPosition(cam->position.x - 300 + 192, cam->position.y + 275 - 32);
		itemDescription.setString(getItemDescription(item));
	}

}

void drawTradePanel() {
	inventoryLeft->draw();
	inventoryRight->draw();
	
	window->draw(background);
	if (drawItemStats == true) {
		window->draw(itemSprite);
		window->draw(itemName);
		window->draw(itemDescription);
	}
}
#endif