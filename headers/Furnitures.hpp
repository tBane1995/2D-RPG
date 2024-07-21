#ifndef Furnitures_hpp
#define Furnitures_hpp

class Furniture : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Inventory* inventory;
	Texture* takeItTexture;
	sf::Sprite takeItSprite;

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
	}
	
	Furniture(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::Furniture;
		
		texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

		// TO-DO (test)
		//inventory = nullptr;
		inventory = new Inventory();
		inventory->addItem("items/roasted meat");
		inventory->addItem("items/wooden club");
		//

		takeItTexture = getTexture("GUI/hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
	}

	void update(float dt) {

		GameObject::update(dt);
		sprite.setPosition(position);
		takeItSprite.setPosition(position.x, position.y - 50);
		if (mouseIsOver) {
			setInventoryPanel(inventory);
		}
			
	}

	void draw(sf::RenderWindow* window) {
		if (mouseIsOver)
			GameObject::draw(window);

		window->draw(sprite);
		
		if(mouseIsOver || (player != nullptr && intersectionRectangleWithElipse(position.x, position.y, collider->width, collider->height, player->position.x, player->position.y, player->collider->width+player->actionRange, player->collider->height + player->actionRange/2.0f)))
			window->draw(takeItSprite);
	}
};

std::vector < Furniture* > furnitures;

#endif