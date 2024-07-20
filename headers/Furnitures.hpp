#ifndef Furnitures_hpp
#define Furnitures_hpp

class Furniture : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Furniture(string name, float width, float height) : GameObject(name, 0, 0, width, height, true, true) {
		type = gameObjectType::Furniture;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}
	
	Furniture(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::Furniture;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
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
};

std::vector < Furniture* > furnitures;

#endif