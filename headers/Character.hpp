#ifndef Character_hpp
#define Character_hpp

class Character : public Unit {
public:

	string body;
	Item* helmet;
	Item* armor;
	Item* pants;

	// HELMET
	Texture* helmetIdleTextures[16];
	Texture* helmetRunTextures[16];
	Texture* helmetAttackTextures[16];

	// ARMOR
	Texture* armorIdleTextures[16];
	Texture* armorRunTextures[16];
	Texture* armorAttackTextures[16];

	// PANTS
	Texture* pantsIdleTextures[16];
	Texture* pantsRunTextures[16];
	Texture* pantsAttackTextures[16];

	// SPRITES
	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;
	
	Dialogue* dialogue;

	Texture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;


	Character(string name, string body) : Unit(name, 36, 18) {
		type = gameObjectType::Character;
		
		this->body = body;
		helmet = nullptr;
		armor = nullptr;
		pants = nullptr;

		loadTextures();


		takeItTexture = getTexture("GUI/talk");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

	}

	Character(GameObject* object, float x, float y) : Unit(object, x, y) {
		type = gameObjectType::Character;
		
		this->body = dynamic_cast<Character*>(object)->body;
		helmet = nullptr;
		armor = nullptr;
		pants = nullptr;

		loadTextures();
		
		takeItTexture = getTexture("GUI/talk");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;
	}

	void loadTextures() {

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();
	}

	void loadBody() {
		for (int i = 0; i < 16; i++) {
			idleTextures[i] = nullptr;
			runTextures[i] = nullptr;
			attackTextures[i] = nullptr;

		}

		for (int i = 0; i < 4; i++) {

			idleTextures[i] = getTexture(body + "/idleTop" + to_string(i));
			idleTextures[4 + i] = getTexture(body + "/idleRight" + to_string(i));
			idleTextures[8 + i] = getTexture(body + "/idleBottom" + to_string(i));
			idleTextures[12 + i] = getTexture(body + "/idleLeft" + to_string(i));

			runTextures[i] = getTexture(body + "/runTop" + to_string(i));
			runTextures[4 + i] = getTexture(body + "/runRight" + to_string(i));
			runTextures[8 + i] = getTexture(body + "/runBottom" + to_string(i));
			runTextures[12 + i] = getTexture(body + "/runLeft" + to_string(i));

			attackTextures[i] = getTexture(body + "/attackTop" + to_string(i));
			attackTextures[4 + i] = getTexture(body + "/attackRight" + to_string(i));
			attackTextures[8 + i] = getTexture(body + "/attackBottom" + to_string(i));
			attackTextures[12 + i] = getTexture(body + "/attackLeft" + to_string(i));

		}

		sprite = sf::Sprite();
		sprite.setOrigin(32, 58);

	}


	void loadHelmet() {

		for (int i = 0; i < 16; i++) {
			helmetIdleTextures[i] = nullptr;
			helmetRunTextures[i] = nullptr;
			helmetAttackTextures[i] = nullptr;

		}

		if (helmet != nullptr) {

			for (int i = 0; i < 4; i++) {
				helmetIdleTextures[i] = getTexture("sets/" + helmet->name + "/idleTop" + to_string(i));
				helmetIdleTextures[4 + i] = getTexture("sets/" + helmet->name + "/idleRight" + to_string(i));
				helmetIdleTextures[8 + i] = getTexture("sets/" + helmet->name + "/idleBottom" + to_string(i));
				helmetIdleTextures[12 + i] = getTexture("sets/" + helmet->name + "/idleLeft" + to_string(i));

				helmetRunTextures[i] = getTexture("sets/" + helmet->name + "/runTop" + to_string(i));
				helmetRunTextures[4 + i] = getTexture("sets/" + helmet->name + "/runRight" + to_string(i));
				helmetRunTextures[8 + i] = getTexture("sets/" + helmet->name + "/runBottom" + to_string(i));
				helmetRunTextures[12 + i] = getTexture("sets/" + helmet->name + "/runLeft" + to_string(i));

				helmetAttackTextures[i] = getTexture("sets/" + helmet->name + "/attackTop" + to_string(i));
				helmetAttackTextures[4 + i] = getTexture("sets/" + helmet->name + "/attackRight" + to_string(i));
				helmetAttackTextures[8 + i] = getTexture("sets/" + helmet->name + "/attackBottom" + to_string(i));
				helmetAttackTextures[12 + i] = getTexture("sets/" + helmet->name + "/attackLeft" + to_string(i));

			}
		}

		helmetSprite = sf::Sprite();
		helmetSprite.setOrigin(32, 58);

	}

	void loadArmor() {

		for (int i = 0; i < 16; i++) {
			armorIdleTextures[i] = nullptr;
			armorRunTextures[i] = nullptr;
			armorAttackTextures[i] = nullptr;

		}

		if (armor != nullptr) {

			for (int i = 0; i < 4; i++) {
				armorIdleTextures[i] = getTexture("sets/" + armor->name + "/idleTop" + to_string(i));
				armorIdleTextures[4 + i] = getTexture("sets/" + armor->name + "/idleRight" + to_string(i));
				armorIdleTextures[8 + i] = getTexture("sets/" + armor->name + "/idleBottom" + to_string(i));
				armorIdleTextures[12 + i] = getTexture("sets/" + armor->name + "/idleLeft" + to_string(i));

				armorRunTextures[i] = getTexture("sets/" + armor->name + "/runTop" + to_string(i));
				armorRunTextures[4 + i] = getTexture("sets/" + armor->name + "/runRight" + to_string(i));
				armorRunTextures[8 + i] = getTexture("sets/" + armor->name + "/runBottom" + to_string(i));
				armorRunTextures[12 + i] = getTexture("sets/" + armor->name + "/runLeft" + to_string(i));

				armorAttackTextures[i] = getTexture("sets/" + armor->name + "/attackTop" + to_string(i));
				armorAttackTextures[4 + i] = getTexture("sets/" + armor->name + "/attackRight" + to_string(i));
				armorAttackTextures[8 + i] = getTexture("sets/" + armor->name + "/attackBottom" + to_string(i));
				armorAttackTextures[12 + i] = getTexture("sets/" + armor->name + "/attackLeft" + to_string(i));

			}
		}

		armorSprite = sf::Sprite();
		armorSprite.setOrigin(32, 58);
	}

	void loadPants() {

		for (int i = 0; i < 16; i++) {
			pantsIdleTextures[i] = nullptr;
			pantsRunTextures[i] = nullptr;
			pantsAttackTextures[i] = nullptr;

		}

		if (pants != nullptr) {

			for (int i = 0; i < 4; i++) {
				pantsIdleTextures[i] = getTexture("sets/" + pants->name + "/idleTop" + to_string(i));
				pantsIdleTextures[4 + i] = getTexture("sets/" + pants->name + "/idleRight" + to_string(i));
				pantsIdleTextures[8 + i] = getTexture("sets/" + pants->name + "/idleBottom" + to_string(i));
				pantsIdleTextures[12 + i] = getTexture("sets/" + pants->name + "/idleLeft" + to_string(i));

				pantsRunTextures[i] = getTexture("sets/" + pants->name + "/runTop" + to_string(i));
				pantsRunTextures[4 + i] = getTexture("sets/" + pants->name + "/runRight" + to_string(i));
				pantsRunTextures[8 + i] = getTexture("sets/" + pants->name + "/runBottom" + to_string(i));
				pantsRunTextures[12 + i] = getTexture("sets/" + pants->name + "/runLeft" + to_string(i));

				pantsAttackTextures[i] = getTexture("sets/" + pants->name + "/attackTop" + to_string(i));
				pantsAttackTextures[4 + i] = getTexture("sets/" + pants->name + "/attackRight" + to_string(i));
				pantsAttackTextures[8 + i] = getTexture("sets/" + pants->name + "/attackBottom" + to_string(i));
				pantsAttackTextures[12 + i] = getTexture("sets/" + pants->name + "/attackLeft" + to_string(i));

			}
		}

		pantsSprite = sf::Sprite();
		pantsSprite.setOrigin(32, 58);

	}


	void update(float dt) {
		GameObject::update(dt);
		
		// only state = states::idle !!

		calculateCurrentFrame(dt);

		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);

		if (helmet != nullptr)
			helmetSprite.setTexture(*helmetIdleTextures[direction * 4 + frame]->texture);

		if (armor != nullptr)
			armorSprite.setTexture(*armorIdleTextures[direction * 4 + frame]->texture);

		if (pants != nullptr)
			pantsSprite.setTexture(*pantsIdleTextures[direction * 4 + frame]->texture);

		sprite.setPosition(position);
		helmetSprite.setPosition(position);
		armorSprite.setPosition(position);
		pantsSprite.setPosition(position);

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
		window->draw(helmetSprite);
		window->draw(pantsSprite);
		window->draw(armorSprite);
		
		if (showHand == true)
			window->draw(takeItSprite);
		
		//window->draw(lifeBarBackground);
		//window->draw(lifeBar);
	}
};

std::vector < Character* > characters;


#endif