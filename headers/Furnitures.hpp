#ifndef Furnitures_hpp
#define Furnitures_hpp

class Furniture : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Inventory* inventory;
	Texture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Furniture(string name, float width, float height) : GameObject(name, 0, 0, width, height, true, true) {
		type = gameObjectType::Furniture;
		
		texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

		inventory = nullptr;
		takeItTexture = getTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;
	}
	
	Furniture(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::Furniture;
		
		texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

		
		inventory = nullptr;
		// TO-DO (test)
		if (name == "furnitures/chest1") {
			inventory = new Inventory();
			inventory->addItem("items/wooden club");
			inventory->addItem("items/wool shirt");   // TO-DO to delete
			inventory->addItem("items/wool pants");   // TO-DO to delete
			inventory->addItem("items/wool hat");   // TO-DO to delete

			// TO-DO - to delete
			inventory->addItem("items/torn shirt");
			inventory->addItem("items/axe");
			inventory->addItem("items/bone");
			inventory->addItem("items/health herb");
			inventory->addItem("items/skin helmet");
			inventory->addItem("items/skin pants");
			inventory->addItem("items/wooden club");
			inventory->addItem("items/skin jacket");
			inventory->addItem("items/club");
			inventory->addItem("items/iron club");
			inventory->addItem("items/stone hammer");
			inventory->addItem("items/sword");
			inventory->addItem("items/long sword");
			inventory->addItem("items/gladius");
			inventory->addItem("items/wide blade");
			inventory->addItem("items/knife");
			inventory->addItem("items/dagger");
			inventory->addItem("items/hatchet");
			inventory->addItem("items/curved sword");
			inventory->addItem("items/chain mail");
			inventory->addItem("items/wool hat");
			inventory->addItem("items/wool pants");
			inventory->addItem("items/wool shirt");
			inventory->addItem("items/raw meat");
			inventory->addItem("items/roasted meat");
			inventory->addItem("items/chain mail pants");
			inventory->addItem("items/plate armor");
			
		}

		if (name == "furnitures/table1") {
			inventory = new Inventory();
			inventory->addItem("items/roasted meat", 3);
		}
		//

		
		takeItTexture = getTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;
	}

	void update(float dt) {

		GameObject::update(dt);

		/*
		if (inventory != nullptr && inventory->items.size() < 1)
			inventory = nullptr;
		*/

		sprite.setPosition(position);
		takeItSprite.setPosition(position.x, position.y - 50);
		showHand = false;

		if (player != nullptr) {

			if (inventory != nullptr) {

				// SHOW HAND
				float x1, y1, rx1, ry1;
				float x2, y2, rx2, ry2;
				
				x1 = player->position.x;
				y1 = player->position.y;
				rx1 = (player->collider->width / 2.0f + player->actionRange);
				ry1 = (player->collider->height + player->actionRange) / 2.0f;

				x2 = position.x;
				y2 = position.y;
				rx2 = collider->width;
				ry2 = collider->height;

				if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1)) {
					showHand = true;

					if (inventory->items.size() > 0)
						takeItSprite.setTexture(*getTexture("GUI/hand")->texture);
					else
						takeItSprite.setTexture(*getTexture("GUI/grey_hand")->texture);
				}

			}

		}

		// TO-DO
		if (player == nullptr) {
			if (inventory != nullptr) {
				if (pointInRectangle(worldMousePosition.x, worldMousePosition.y, position.x, position.y, collider->width, collider->height)) {
					showHand = true;
				}
			}
		}
		//

	}

	void draw(sf::RenderWindow* window) {
		if (mouseIsOver)
			GameObject::draw(window);

		window->draw(sprite);

		if(showHand)
			window->draw(takeItSprite);
	}
};

std::vector < Furniture* > furnitures;

#endif