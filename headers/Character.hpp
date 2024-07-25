#ifndef Character_hpp
#define Character_hpp

class Character : public Unit {
public:
	Dialogue* dialogue;

	Texture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	

	Character(string name) : Unit(name, 36, 18) {
		type = gameObjectType::Character;

		takeItTexture = getTexture("GUI/talk");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

	}

	Character(GameObject* object, float x, float y) : Unit(object, x, y) {
		type = gameObjectType::Character;

		takeItTexture = getTexture("GUI/talk");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;
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

		showHand = false;
		takeItSprite.setPosition(position.x, position.y - 80);

		if (dialogue != nullptr) {

			if (player != nullptr) {

				// SHOW HAND
				float x1, y1, rx1, ry1;
				float x2, y2, rx2, ry2;

				x1 = player->position.x;
				y1 = player->position.y;
				rx1 = (player->collider->width / 2.0f + player->actionRange);
				ry1 = (player->collider->height + player->actionRange) / 2.0f;

				x2 = position.x;
				y2 = position.y;
				rx2 = collider->width / 2.0f;
				ry2 = collider->height / 2.0f;

				if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {
					showHand = true;

				}
			}
		}
	}

	void draw(sf::RenderWindow* window) {
		if (mouseIsOver) {
			window->draw(viewRangeArea);
			window->draw(actionRangeArea);
			GameObject::draw(window);
		}
		window->draw(sprite);
		
		if (showHand == true)
			window->draw(takeItSprite);
		
		//window->draw(lifeBarBackground);
		//window->draw(lifeBar);
	}
};

std::vector < Character* > characters;


#endif