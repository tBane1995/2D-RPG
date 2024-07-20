#ifndef Paths_hpp
#define Paths_hpp


class Path : public GameObject {
public:

	Texture* texture;
	sf::Sprite sprite;
	
	Path(string name, float width, float height ) : GameObject(name, 0, 0, width, height, false, false) {
		type = gameObjectType::Path;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Path(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = gameObjectType::Path;
		this->texture = getTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*getTexture(name)->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
		
	}

	~Path() { }

	void update(float dt) {

		GameObject::update(dt);
		sprite.setPosition(position);
	}

	void draw(sf::RenderWindow* window) {
		
		if(mouseIsOver)
			GameObject::draw(window);
	
		window->draw(sprite);
	}
};

std::vector < Path* > paths;

bool isPathOnPosition( float x, float y) {
	for (auto& path : paths) {
		if (pointInEllipse(x, y, path->position.x, path->position.y, path->collider->width/2.0f, path->collider->height / 2.0f))
			return true;
	}

	return false;
}

#endif