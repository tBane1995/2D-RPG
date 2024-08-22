#ifndef Walls_hpp
#define Walls_hpp

class Wall : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Wall(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, true) {
		type = gameObjectType::Wall;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Wall(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::Wall;
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

std::vector < Wall* > walls;

#endif