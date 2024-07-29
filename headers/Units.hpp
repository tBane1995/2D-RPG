#ifndef Units_hpp
#define Units_hpp

float diff_x, diff_y;
float dist;

class Unit : public GameObject {
public:
	
	Texture* attackTextures[16];
	Texture* idleTextures[16];			
	Texture* runTextures[16];
	sf::Sprite sprite;

	sf::CircleShape viewRangeArea;		// is a range of see of units // in this range player can be a select as target
	sf::CircleShape actionRangeArea;
	sf::RectangleShape lifeBarBackground;
	sf::RectangleShape lifeBar;

	int frame;		// current frame
	float countdown;
	int direction;	// direction 0 - Top, 1 - Right, 2 - Bottom, 3 - Left
	float actionRange;	// range of action 
	float viewRange;	// range of view
	float cooldown;
	float attackTime;

	int HP, HP_max;
	int MP, MP_max;
	int STRENGTH;
	int DEXTERITY;
	int INTELLIGENCE;

	states state;

	sf::Vector2f target;


	Unit(string name, float width, float height) : GameObject(name, 0, 0, width, height, true, false) {

		frame = 0;
		countdown = 0.0f;
		direction = 2;

		sprite = sf::Sprite();
		

		viewRange = 200.0f;
		actionRange = 35.0f;

		setViewRangeArea();
		setActionRangeArea();

		// STATS
		HP = 50;
		HP_max = 50;
		MP = 10;
		MP_max = 10;
		STRENGTH = 5;
		DEXTERITY = 5;
		INTELLIGENCE = 5;

		// STATE
		state = states::idle;

		cooldown = 0.0f;
		attackTime = 1.0f;
	
	}

	Unit(GameObject* object, float x, float y) : GameObject(object, x, y) {
		
		type = gameObjectType::Character;

		frame = 0;
		countdown = 0.0f;
		direction = 2;
				
		viewRange = 200.0f;
		actionRange = 25.0f;

		setViewRangeArea();
		setActionRangeArea();

		// STATS
		HP = dynamic_cast < Unit* >(object)->HP;
		HP_max = dynamic_cast < Unit* >(object)->HP_max;
		MP = dynamic_cast <Unit*>(object)->MP;
		MP_max = dynamic_cast <Unit*>(object)->MP_max;
		STRENGTH = dynamic_cast <Unit*>(object)->STRENGTH;
		DEXTERITY = dynamic_cast <Unit*>(object)->DEXTERITY;
		INTELLIGENCE = dynamic_cast <Unit*>(object)->INTELLIGENCE;
		
		// STATE
		state = states::idle;

		cooldown = 0.0f;
		attackTime = 1.0f;
	}

	~Unit() { }

	

	void setViewRangeArea() {
		viewRangeArea = sf::CircleShape(viewRange + collider->width/2.0f);
		viewRangeArea.setFillColor(sf::Color(64, 64, 128, 128));
		viewRangeArea.setOutlineColor(sf::Color(64, 64, 196, 128));
		viewRangeArea.setOutlineThickness(4.0f);
		viewRangeArea.setOrigin(viewRange + collider->width/2.0f, viewRange + collider->height/2.0f);
		viewRangeArea.setScale(1.0f, collider->height/collider->width);
	}

	void setActionRangeArea() {
		actionRangeArea = sf::CircleShape(actionRange + collider->width/2.0f);
		actionRangeArea.setFillColor(sf::Color(128, 64, 64, 128));
		actionRangeArea.setOutlineColor(sf::Color(196, 64, 64, 128));
		actionRangeArea.setOutlineThickness(4.0f);
		actionRangeArea.setOrigin(actionRange + collider->width / 2.0f, actionRange + collider->width/2.0f);
		actionRangeArea.setScale(1.0f, collider->height/collider->width);
	}

	void setLifeBar() {
		lifeBarBackground = sf::RectangleShape(sf::Vector2f(50.0f, 6.0f));
		lifeBarBackground.setOrigin(25, 3);
		lifeBarBackground.setFillColor(sf::Color::Black);
		lifeBarBackground.setPosition(position.x, position.y - 100);

		lifeBar = sf::RectangleShape(sf::Vector2f(48.0f * HP / HP_max, 4.0f));
		lifeBar.setOrigin(24, 2);
		lifeBar.setFillColor(sf::Color(128, 64, 64));
		lifeBar.setPosition(position.x, position.y - 100); 
	}

	void takeDamage(float damage) {
		HP -= damage;

		if (HP < 0)
			HP = 0.0f;
	}

	void calculateCurrentFrame(float dt) {
		countdown -= dt;
		while (countdown <= 0.0f) {
			countdown += 1.0f / 8.0f;	// 8 FPS
			frame += 1;
		}

		if (frame > 3)
			frame = frame % 4;
	}

	void cooldownDecrease(float dt) {
		if (cooldown >= 0.0f)
			cooldown -= dt;
	}

	bool playerInActionRange() {

		if (player == nullptr)
			return false;

		return intersectionTwoEllipses(position.x, position.y, collider->width/2.0f + actionRange, (collider->height + actionRange) / 2.0f, player->position.x, player->position.y, player->collider->width/2.0f, player->collider->height / 2.0f);

	}

	bool playerInViewRange() {
		if (player == nullptr)
			return false;

		return intersectionTwoEllipses(position.x, position.y, collider->width/2.0f + viewRange, (collider->height + viewRange) / 2.0f, player->position.x, player->position.y, player->collider->width/2.0f, player->collider->height / 2.0f);
	}

	void goToTarget(float dt) {
		 
		dist = 15.0f * 4.0f * dt;	// distance to move
		diff_x = target.x - position.x;
		diff_y = target.y - position.y;

		if (diff_x == 0 && diff_y == 0)
		{
			state = states::idle;
			frame = 0;

		}
		else if (diff_x!=0 && abs(diff_x) < dist) {
			position.x = target.x;
		}
		else if (diff_y!=0 && abs(diff_y) < dist) {
			position.y = target.y;
		}
		else {

			if (diff_x > 0) direction = 1; // prawo
			if (diff_x < 0) direction = 3; // lewo

			// Ruch w pionie
			if (diff_y > 0) direction = 2; // dół
			if (diff_y < 0) direction = 0; // góra

			// TO TOP
			if (direction == 0) {
				if (!collisions(this, 0, -dist))
					position.y -= dist;
			}

			// TO RIGHT
			if (direction == 1) {
				if (!collisions(this, dist, 0))
					position.x += dist;
			}

			// TO DOWN
			if (direction == 2) {
				if (!collisions(this, 0, dist))
					position.y += dist;
			}

			// TO LEFT
			if (direction == 3) {
				if (!collisions(this, -dist, 0))
					position.x -= dist;
			}
		}
		
	}

	void idle(float dt) {
		if (rand() % 30 == 0) {
			state = states::walk;
			target.x = position.x + rand() % 100 - 50;
			target.y = position.y + rand() % 100 - 50;
		}

		calculateCurrentFrame(dt);
		sprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
	}

	void run(float dt) {
		
		goToTarget(dt);

		calculateCurrentFrame(dt);
		sprite.setTexture(*runTextures[direction * 4 + frame]->texture);
	}

	void attack(float dt) {

		if (cooldown <= 0.0f) {
			//player->takeDamage(10);
			player->takeDamage(STRENGTH * 3 + DEXTERITY);
			cooldown = attackTime;
			frame = 0;
		}else
			frame = (attackTime-cooldown) / attackTime * 4.0f;
			
		if (frame < 0)
			frame = 0;

		if (frame >= 4) 
			frame = 3;

		sprite.setTexture(*attackTextures[direction * 4 + frame]->texture);
	}

	virtual void update(float dt) {

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

	virtual void draw(sf::RenderWindow* window) {
		if (mouseIsOver) {
			window->draw(viewRangeArea);
			window->draw(actionRangeArea);
			GameObject::draw(window);
		}
		window->draw(sprite);
		window->draw(lifeBarBackground);
		window->draw(lifeBar);
	}

};

#endif