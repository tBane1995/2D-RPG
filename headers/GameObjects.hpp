#ifndef GameObjects_hpp
#define GameObjects_hpp

enum class gameObjectType { GameObject, Nature, Monster, Character, Player, ItemOnMap, InventoryOnMap, Path, Furniture, Terrain, Floor, Wall, Building };

class Collider {
public:
	float width;
	float height;
	bool isRectangular;
	sf::Shape* shape;

	Collider(float width, float height, bool isRectangular) {
		this->width = width;
		this->height = height;
		this->isRectangular = isRectangular;

		if (isRectangular == true) {
			shape = new sf::RectangleShape(sf::Vector2f(width, height));
			shape->setFillColor(sf::Color(128, 64, 128, 128));
			shape->setOutlineColor(sf::Color(196, 64, 196, 128));
			shape->setOutlineThickness(4.0f);
			shape->setOrigin(width/2.0f, height/2.0f);
			shape->setScale(1, 1);
		}
		else {
			shape = new sf::CircleShape(width/2.0f);
			shape->setFillColor(sf::Color(128, 64, 128, 128));
			shape->setOutlineColor(sf::Color(196, 64, 196, 128));
			shape->setOutlineThickness(4.0f);
			shape->setOrigin(width/2.0f, width/2.0f);
			shape->setScale(1, height/width);
		}
	}

	Collider(Collider* col) {
		this->width = col->width;
		this->height = col->height;
		this->isRectangular = col->isRectangular;

		if (isRectangular == true) {
			shape = new sf::RectangleShape(sf::Vector2f(width, height));
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());

		}
		else {
			shape = new sf::CircleShape(width/2.0f);
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());
		}
	}
};

class GameObject {
public:
	string name;
	gameObjectType type;
	sf::Vector2f position;
	bool collisioning;	// check the collision
	
	bool mouseIsOver;	// mouse is over on GameObject
	
	Collider* collider;
	sf::Text textname;
	
	bool isVisible;	// TO-DO
	bool toDelete;

	GameObject(string name, float x, float y, float width, float height, bool collisioning, bool isRectangular) {
		// CREATE PREFAB
		this->name = name;
		type = gameObjectType::GameObject;
		position.x = x;
		position.y = y;

		this->collisioning = collisioning;
		
		mouseIsOver = false;

		collider = new Collider(width, height, isRectangular);
		createTextname();
		
		toDelete = false;
		isVisible = false;
	}

	GameObject(GameObject* go, float x, float y) {
		// CREATE GAMEOBJECT FROM PREFAB
		this->name = go->name;
		type = gameObjectType::GameObject;
		position.x = x;
		position.y = y;

		this->collisioning = go->collisioning;
		
		mouseIsOver = false;
		collider = new Collider(go->collider);

		createTextname();

		toDelete = false;
		isVisible = false;
	}

	GameObject(string name) {
		// FOR TILES PALETTE (TERRAIN) 
		this->name = name;
		position.x = 0;
		position.y = 0;

		collisioning = true;

		mouseIsOver = false;
		collider = new Collider(16,16, true);
		collider->shape = new sf::RectangleShape(sf::Vector2f(16,16));
		createTextname();

		toDelete = false;
		isVisible = false;
	}

	~GameObject() { }

	
	GameObject(string name, float x, float y) {
		// FOR BUILDINGS

		this->name = name;
		position.x = x;
		position.y = y;

		collisioning = true;

		mouseIsOver = false;
		collider = nullptr;
		createTextname();

		toDelete = false;
		isVisible = false;
	}

	void createTextname() {
		textname = sf::Text(name, basicFont, 16);
		textname.setOrigin(textname.getGlobalBounds().width / 2.f, textname.getGlobalBounds().height / 2.f);
		textname.setFillColor(textNameColor);
		textname.setOutlineColor(sf::Color::Black);
		textname.setOutlineThickness(1.0f);
		
	}

	void mouseOvering() {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
		sf::Vector2f worldPosition = window->mapPixelToCoords(mousePosition);	// Zamień na współrzędne świata, uwzględniając aktualny widok
		
		if (collider->isRectangular == false) {

			if (pointInEllipse(worldPosition.x, worldPosition.y, position.x, position.y, collider->width/2.0f, collider->height / 2.0f))
				mouseIsOver = true;
			else
				mouseIsOver = false;
		}

		if (collider->isRectangular == true) {

			if (pointInRectangle(worldPosition.x, worldPosition.y, position.x, position.y, collider->width, collider->height))
				mouseIsOver = true;
			else
				mouseIsOver = false;
		}

		
	}

	virtual void update(float dt) { 
		mouseOvering();

		collider->shape->setPosition(position);
		textname.setPosition(position.x, position.y - 100);
	}

	virtual void draw(sf::RenderWindow* window) {
		window->draw(*collider->shape);
		
		if(mouseIsOver)
			window->draw(textname);
	}

};


std::vector < GameObject* > gameObjects;

bool collisions(GameObject* object, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	if (object->collider->isRectangular == false) {
		
		// object is elipse
		for (auto& go : gameObjects) {

			if (go != object && go->collisioning != false) {

				if (go->collider->isRectangular == false) {
					// elipse with elipse
					if ( intersectionTwoEllipses(object->position.x + dx, object->position.y + dy, object->collider->width/2.0f, object->collider->height / 2.f, go->position.x, go->position.y, go->collider->width/2.0f, go->collider->height / 2.f))
						return true;
				}

				if (go->collider->isRectangular == true) {
					// elipse with rectangle
					if ( intersectionRectangleWithElipse(go->position.x, go->position.y, go->collider->width, go->collider->height, object->position.x+dx, object->position.y+dy, object->collider->width/2.0f, object->collider->height / 2.0f))
						return true;

				}
			}
		}
	}

	if (object->collider->isRectangular == true) {
		
		// object is rectangle
		for (auto& go : gameObjects) {

			if (go != object && go->collisioning != false) {

				if (go->collider->isRectangular == false) {
					// rectangle with elipse
					if (intersectionRectangleWithElipse(object->position.x+dx, object->position.y+dy, object->collider->width, object->collider->height, go->position.x, go->position.y, go->collider->width/2.0f, go->collider->height/2.0f))
						return true;
				}

				if (go->collider->isRectangular == true) {
					// rectangle with rectangle
					if (intersectionTwoRectangles(object->position.x+dx, object->position.y+dy, object->collider->width, object->collider->height, go->position.x, go->position.y, go->collider->width, go->collider->height))
						return true;

				}
			}
		}
	}
	

	return false;
}



#endif