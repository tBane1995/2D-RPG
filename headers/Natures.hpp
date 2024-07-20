#ifndef NatureObjects_hpp
#define NatureObjects_hpp

class Nature : public GameObject {
public:
	Texture* texture;
	sf::Sprite sprite;

	Nature(string name, float width, float height) : GameObject(name, 0, 0, width, height, true, false) {
		type = gameObjectType::Nature;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Nature(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::Nature;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

	}

	~Nature() { }

	void update(float dt) { 
		
		GameObject::update(dt);
		
		//mouseOvering();
		sprite.setPosition(position);
	}

	void draw(sf::RenderWindow* window) {

		if (mouseIsOver)
			GameObject::draw(window);

		window->draw(sprite);

		
	}
};

std::vector < Nature* > natures;

#endif