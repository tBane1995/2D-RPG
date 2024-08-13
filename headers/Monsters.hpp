#ifndef Monsters_hpp
#define Monsters_hpp

class Monster : public Unit {
public:

	bool isAlive;
	sf::Vector2f base;
	sf::Time deathTime;

	Monster(string name, float width, float height) : Unit(name, width, height) {
		type = gameObjectType::Monster;
		direction = 2;
		isAlive = true;
		base = position;
		
		loadTextures();

	}

	Monster(GameObject* object, float x, float y) : Unit(object, x, y) {
		type = gameObjectType::Monster;
		direction = 2;
		isAlive = true;
		base = position;

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
			loot->addItem("items/tooth", 2);
			loot->addItem("items/wolf skin");
		}
		else if (name == "monsters/dziobak") {
			loot->addItem("items/raw meat", 2);
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
			state = states::walk;
			target.x = base.x + rand() % 100 - 50;
			target.y = base.y + rand() % 100 - 50;
		}

		calculateCurrentFrame(dt);
		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
	}

	virtual void update(float dt) {

		if (HP <= 0.f && isAlive == true) {
			
			// death
			dropLoot();
			isAlive = false;
			collisioning = false;
			deathTime = currentTime;
		}
		else if (isAlive == false) {
			
			// resurrection
			if ( (currentTime-deathTime).asSeconds() > 10) {
				isAlive = true;
				collisioning = true;
				HP = HP_max;
				state = states::idle;

				while (collisions(this, 0, 0)) {

					position.x = rand() % 100 - 50 + base.x;
					position.y = rand() % 100 - 50 + base.y;
				}
			}

		}
		
		if( isAlive == true) {

			GameObject::update(dt);

			if (playerInActionRange()) {
				state = states::attack;
			}
			else if (playerInViewRange()) {
				target = player->position;
				state = states::walk;
			}

			if (state == states::idle) {
				idle(dt);
			}
			else if (state == states::walk) {
				run(dt);
			}
			else if (state == states::attack) {
				attack(dt);
			}

			if (cooldown > 0.0f)
				cooldown -= dt;

			sprite.setPosition(position);
			viewRangeArea.setPosition(position);
			actionRangeArea.setPosition(position);

			setLifeBar();
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