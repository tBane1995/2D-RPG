#ifndef Monsters_hpp
#define Monsters_hpp

class Monster : public Unit {
public:

	bool isAlive;
	sf::Vector2f base;
	sf::Time deathTime;
	int EXPERIENCE;

	Monster(string name, float width, float length, float height,  int EXP) : Unit(name, name, width, length, height) {
		type = gameObjectType::Monster;
		direction = 2;
		isAlive = true;
		base = position;	
		this->EXPERIENCE = EXP;
		loadTextures();
		

	}

	Monster(GameObject* object, float x, float y) : Unit(object, x, y) {
		type = gameObjectType::Monster;
		direction = 2;
		isAlive = true;
		base = position;
		this->EXPERIENCE = dynamic_cast<Monster*>(object)->EXPERIENCE;

		loadTextures();
	}

	void loadTextures() {

		for (int i = 0; i < 4; i++) {

			attackTextures[i] = getTexture(name + "/attackTop" + to_string(i));
			attackTextures[4 + i] = getTexture(name + "/attackRight" + to_string(i));
			attackTextures[8 + i] = getTexture(name + "/attackBottom" + to_string(i));
			attackTextures[12 + i] = getTexture(name + "/attackLeft" + to_string(i));

			idleTextures[i] = getTexture(name + "/idleTop" + to_string(i));
			idleTextures[4 + i] = getTexture(name + "/idleRight" + to_string(i));
			idleTextures[8 + i] = getTexture(name + "/idleBottom" + to_string(i));
			idleTextures[12 + i] = getTexture(name + "/idleLeft" + to_string(i));

			runTextures[i] = getTexture(name + "/runTop" + to_string(i));
			runTextures[4 + i] = getTexture(name + "/runRight" + to_string(i));
			runTextures[8 + i] = getTexture(name + "/runBottom" + to_string(i));
			runTextures[12 + i] = getTexture(name + "/runLeft" + to_string(i));

		}

		sprite = sf::Sprite();
		sprite.setOrigin(idleTextures[0]->cx, idleTextures[0]->cy);
	}

	void dropLoot() {

		Inventory* loot = new Inventory();
		// TO-DO
		if (name == "monsters/wilczur") {
			loot->addItem("items/raw meat");
			loot->addItem("items/tooth", 1);
			loot->addItem("items/wolf skin");
		}
		
		if (name == "monsters/dziobak") {
			loot->addItem("items/raw meat", 2);
		}

		if (name == "monsters/goblin") {
			loot->addItem("items/wooden club", 1);
		}

		if (name == "monsters/troll") {
			
		}

		if (name == "monsters/bies") {

		}

		if (name == "monsters/kolcorozec") {
			loot->addItem("items/tooth", 1);
			loot->addItem("items/spike", 1);
		}

		if (loot->items.size() > 0) {
			InventoryOnMap* bag = new InventoryOnMap(loot, position.x, position.y);
			bag->isVisible = true;
			gameObjects.push_back(bag);
			inventoriesOnMap.push_back(bag);
		}

	}

	void idle(float dt) {
		if (rand() % 300 == 0) {
			state = unitStates::run;
			target.x = base.x + rand() % 100 - 50;
			target.y = base.y + rand() % 100 - 50;
		}

		calculateCurrentFrame(dt);
		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
	}

	virtual void update(float dt) {

		if (HP == 0 && isAlive == true) {
			
			// death
			dropLoot();
			player->gainEXP(EXPERIENCE);
			isAlive = false;
			collisioning = false;
			deathTime = currentTime;
		}
		else if (isAlive == false) {
			
			// resurrection
			if ( (currentTime-deathTime).asSeconds() > 20) {
				isAlive = true;
				collisioning = true;
				HP = HP_FULL;
				state = unitStates::idle;

				while (collisions(this, 0, 0)) {

					position.x = rand() % 100 - 50 + base.x;
					position.y = rand() % 100 - 50 + base.y;
				}
			}

		}
		
		if( isAlive == true) {

			GameObject::update(dt);

			if (playerInActionRange()) {
				state = unitStates::attack;
			}
			else if (playerInViewRange()) {
				target = player->position;
				state = unitStates::run;
			}

			if (state == unitStates::idle) {
				idle(dt);
			}
			else if (state == unitStates::run) {
				run(dt);
			}
			else if (state == unitStates::attack) {
				attack(dt);
			}

			if (cooldown > 0.0f)
				cooldown -= dt;

			sprite.setPosition(position);
			viewRangeArea.setPosition(position);
			actionRangeArea.setPosition(position);

			setLifeBar();
			textname.setPosition(position.x, position.y - collider->height - 35);
		}

	}

	void draw(sf::RenderWindow* window) {

		if (isAlive) {

			if (mouseIsOver) {
				window->draw(viewRangeArea);
				window->draw(actionRangeArea);
				GameObject::draw(window);
			}

			window->draw(sprite);
			window->draw(lifeBarBackground);
			window->draw(lifeBar);
		}
	}
};

std::vector < Monster* > monsters;
#endif