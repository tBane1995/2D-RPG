#ifndef Character_hpp
#define Character_hpp

class Character : public Unit {
public:
	Dialogue* dialogue;

	Character(string name) : Unit(name, 36, 18) {
		type = gameObjectType::Character;
	}

	Character(GameObject* object, float x, float y) : Unit(object, x, y) {
		type = gameObjectType::Character;
	}


	void update(float dt) {
		GameObject::update(dt);
		
		// only state = states::idle !!

		calculateCurrentFrame(dt);
		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);

		sprite.setPosition(position);
		viewRangeArea.setPosition(position);
		actionRangeArea.setPosition(position);

		setLifeBar();
	}

	void draw(sf::RenderWindow* window) {
		if (mouseIsOver) {
			window->draw(viewRangeArea);
			window->draw(actionRangeArea);
			GameObject::draw(window);
		}
		window->draw(sprite);
		//window->draw(lifeBarBackground);
		//window->draw(lifeBar);
	}
};

std::vector < Character* > characters;


#endif