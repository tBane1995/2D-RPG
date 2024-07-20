#ifndef Items_hpp
#define Items_hpp

// TO-DO
enum class attribute { attack, defend, HP, MP, HP_max, MP_max, strength, dexterity };
enum class itemType { herb, potion, food, weapon, helmet, armor, other };

class Item {
public:
	string location;
	Texture* texture;
	itemType type;
	std::map < attribute, int > attributes;		// TO-DO

	Item(string location, itemType type) {
		this->location = location;
		this->type = type;
		this->texture = getTexture(location);
	}
};

std::vector < Item* > items;

Item* getItem(string location) {
	for (auto& item : items) {
		if (item->location == location)
			return item;
	}

	return nullptr;
}

class ItemOnMap : public GameObject {
public:
	Item* item;
	Texture* texture;
	sf::Sprite sprite;
	int count;
	bool collected;

	ItemOnMap(Item* item, float x, float y, int count = 1 ) : GameObject(item->location, x, y, 16, 8, false, false) {
		type = gameObjectType::ItemOnMap;
		this->item = item;
		this->count = count;
		collected = false;

		texture = getTexture(item->location);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(x, y);
		sprite.setScale(0.5f, 0.5f);
	}

	ItemOnMap(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::ItemOnMap;
		this->item = getItem(object->name);
		this->count = 1;
		collected = false;

		texture = getTexture(item->location);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(x, y);
		sprite.setScale(0.5f, 0.5f);
	}

	void update(float dt) {

		GameObject::update(dt);
		sprite.setPosition(position);
	}

	void draw(sf::RenderWindow* window) {

		window->draw(sprite);
		
		if (mouseIsOver) {

			GameObject::draw(window);
			window->draw(textname);
		}
	}

};

std::vector < ItemOnMap* > itemsOnMap;

void loadItems() {

	items.clear();
	Item* item;
	
	// WEAPONS
	item = new Item("items/wooden club", itemType::weapon);
	item->attributes[attribute::attack] = 2;
	items.push_back(item);

	item = new Item("items/knife", itemType::weapon);
	item->attributes[attribute::attack] = 2;
	items.push_back(item);
	
	item = new Item("items/hatchet", itemType::weapon);
	item->attributes[attribute::attack] = 3;
	items.push_back(item);

	item = new Item("items/dagger", itemType::weapon);
	item->attributes[attribute::attack] = 4;
	items.push_back(item);

	item = new Item("items/sword", itemType::weapon);
	item->attributes[attribute::attack] = 5;
	items.push_back(item);

	item = new Item("items/gladius", itemType::weapon);
	item->attributes[attribute::attack] = 5;
	items.push_back(item);

	item = new Item("items/stone hammer", itemType::weapon);
	item->attributes[attribute::attack] = 5;
	items.push_back(item);

	item = new Item("items/club", itemType::weapon);
	item->attributes[attribute::attack] = 6;
	items.push_back(item);

	item = new Item("items/curved sword", itemType::weapon);
	item->attributes[attribute::attack] = 7;
	items.push_back(item);

	item = new Item("items/long sword", itemType::weapon);
	item->attributes[attribute::attack] = 8;
	items.push_back(item);

	item = new Item("items/wide blade", itemType::weapon);
	item->attributes[attribute::attack] = 10;
	items.push_back(item);

	item = new Item("items/iron club", itemType::weapon);
	item->attributes[attribute::attack] = 12;
	items.push_back(item);

	item = new Item("items/axe", itemType::weapon);
	item->attributes[attribute::attack] = 14;
	items.push_back(item);


	// HERBS
	item = new Item("items/herb", itemType::herb);
	item->attributes[attribute::HP] = 5;
	items.push_back(item);

	item = new Item("items/health herb", itemType::herb);
	item->attributes[attribute::HP] = 15;
	items.push_back(item);

	item = new Item("items/health root", itemType::herb);
	item->attributes[attribute::HP] = 25;
	items.push_back(item);
	
	item = new Item("items/health plant", itemType::herb);
	item->attributes[attribute::HP] = 50;
	items.push_back(item);

	item = new Item("items/mushroom", itemType::herb);
	item->attributes[attribute::HP] = 50;
	items.push_back(item);

	// POTIONS

	item = new Item("items/potion", itemType::potion);
	item->attributes[attribute::HP] = 30;
	items.push_back(item);

	// FOOD
	item = new Item("items/raw meat", itemType::food);
	item->attributes[attribute::HP] = 10;
	items.push_back(item);

	item = new Item("items/roasted meat", itemType::food);
	item->attributes[attribute::HP] = 20;
	items.push_back(item);

	// OTHERS
	item = new Item("items/bone", itemType::other);
	items.push_back(item);

	item = new Item("items/tooth", itemType::other);
	items.push_back(item);

	item = new Item("items/wolf skin", itemType::other);
	items.push_back(item);

}


class Inventory {
public:
	std::vector < Item* > items;
	std::vector < int > counts;

	Inventory() {
		items.clear();
		counts.clear();
	}

	void addItem(string location, int count = 1) {

		for (int i = 0; i < items.size(); i++)
			if (items[i]->location == location) {
				counts[i] += count;
				return;
			}

		items.push_back(getItem(location));
		counts.push_back(count);
	}

	void addItem(Item* item, int count = 1) {

		bool addedItem = false;

		for (int i = 0; i < items.size(); i++)
			if (items[i] == item) {
				counts[i] += count;
				return;
			}

		items.push_back(item);
		counts.push_back(count);
	}

	bool hasItemsInInventory(string location, int count=1) {
		
		for (int i = 0; i < items.size(); i++)
			if (items[i]->location == location) {
				
				if (counts[i] >= count)
					return true;
				else
					return false;
			}

		return false;
	}

	void removeItem(string location, int count = 1) {
		for (int i = 0; i < items.size(); i++)
			if (items[i]->location == location) {
				counts[i] -= count;
			}

		// delete zeros (count)
		std::vector < Item* > newItems;
		std::vector < int > newCounts;

		for (int i = 0; i < items.size(); i++) {
			if (counts[i] > 0) {
				newItems.push_back(items[i]);
				newCounts.push_back(counts[i]);
			}
				
		}

		items = newItems;
		counts = newCounts;
		return;
	}


};


class InventoryOnMap : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;
	bool collected;
	Inventory* inventory;

	InventoryOnMap(Inventory* inventory, float x, float y) : GameObject("inventory", x, y, 16, 8, false, false) {
		type = gameObjectType::InventoryOnMap;
		texture = getTexture("items/bag");
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(x, y);
		sprite.setScale(0.5f, 0.5f);
		collected = false;
		this->inventory = inventory;
	}
	
	void update(float dt) {
		GameObject::update(dt);

		sprite.setPosition(position);
	}

	void draw(sf::RenderWindow* window) {

		if (mouseIsOver)
			GameObject::draw(window);

		window->draw(sprite);

	}


	~InventoryOnMap() { }
};

std::vector < InventoryOnMap* > inventoriesOnMap;

#endif 
