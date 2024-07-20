#ifndef Player_hpp
#define Player_hpp

class Player : public GameObject {
public:
	sf::Texture bodyIdleTextures[16];	// idle for top, right, bottom, left
	sf::Texture bodyRunTextures[16];	// run for top, right, bottom, left
	sf::Texture bodyAttackTextures[16];	// fight for top, right, bottom, left

	// HELMET
	sf::Texture helmetIdleTextures[16];
	sf::Texture helmetRunTextures[16];
	sf::Texture helmetAttackTextures[16];

	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;

	int direction;
	int frame;	// current frame number
	float stepSize;
	states state;
	float actionRange;
	float viewRange;
	sf::CircleShape actionRangeArea;
	float HP, HP_max;
	float countdown;	 // timer to determine current frame
	float attackTime;
	float cooldown;

	Inventory* bag;

	Player() : GameObject("hero", 0, 0, 36, 18, true, false) {
		type = gameObjectType::Player;
		direction = 2;
		frame = 0;
		stepSize = 6.0f;
		countdown = 0.0f;
		state = states::idle;
		actionRange = 25.0f;
		cooldown = 0.0f;
		attackTime = 1.0f;
		HP_max = 100;
		HP = 90;
		
		loadTextures();
	
		bodySprite = sf::Sprite();
		bodySprite.setOrigin(32, 58);

		helmetSprite = sf::Sprite();
		helmetSprite.setOrigin(32, 58);

		setActionRangeArea();

		bag = new Inventory();
		
		toDelete = false;
		isVisible = false;
	}

	~Player() { }
	
	void setDirection(int direction) {
		this->direction = direction;
		frame = 0.0f;
	}

	void move() {
		state = states::walk;
	}

	void attack() {
		state = states::attack;
		frame = 0.0f;
		cooldown = attackTime;
	}

	void setPosition(float x, float y) {
		this->position.x = x;
		this->position.y = y;
	}

	void loadBodyTextures() {
		for (int i = 0; i < 16; i++) {
			bodyIdleTextures[i] = sf::Texture();
			bodyRunTextures[i] = sf::Texture();
			bodyAttackTextures[i] = sf::Texture();

		}

		for (int i = 0; i < 4; i++) {
			bodyIdleTextures[i].loadFromFile("assets/hero/idleTop" + to_string(i) + ".png");
			bodyIdleTextures[4 + i].loadFromFile("assets/hero/idleRight" + to_string(i) + ".png");
			bodyIdleTextures[8 + i].loadFromFile("assets/hero/idleBottom" + to_string(i) + ".png");
			bodyIdleTextures[12 + i].loadFromFile("assets/hero/idleLeft" + to_string(i) + ".png");

			bodyRunTextures[i].loadFromFile("assets/hero/runTop" + to_string(i) + ".png");
			bodyRunTextures[4 + i].loadFromFile("assets/hero/runRight" + to_string(i) + ".png");
			bodyRunTextures[8 + i].loadFromFile("assets/hero/runBottom" + to_string(i) + ".png");
			bodyRunTextures[12 + i].loadFromFile("assets/hero/runLeft" + to_string(i) + ".png");

			bodyAttackTextures[i].loadFromFile("assets/hero/attackTop" + to_string(i) + ".png");
			bodyAttackTextures[4 + i].loadFromFile("assets/hero/attackRight" + to_string(i) + ".png");
			bodyAttackTextures[8 + i].loadFromFile("assets/hero/attackBottom" + to_string(i) + ".png");
			bodyAttackTextures[12 + i].loadFromFile("assets/hero/attackLeft" + to_string(i) + ".png");

		}
	}

	void loadHelmetTextures() {

		for (int i = 0; i < 16; i++) {
			helmetIdleTextures[i] = sf::Texture();
			helmetRunTextures[i] = sf::Texture();
			helmetAttackTextures[i] = sf::Texture();

		}

		for (int i = 0; i < 4; i++) {
			helmetIdleTextures[i].loadFromFile("assets/hero/basicHelmet/idleTop" + to_string(i) + ".png");
			helmetIdleTextures[4 + i].loadFromFile("assets/hero/basicHelmet/idleRight" + to_string(i) + ".png");
			helmetIdleTextures[8 + i].loadFromFile("assets/hero/basicHelmet/idleBottom" + to_string(i) + ".png");
			helmetIdleTextures[12 + i].loadFromFile("assets/hero/basicHelmet/idleLeft" + to_string(i) + ".png");

			helmetRunTextures[i].loadFromFile("assets/hero/basicHelmet/runTop" + to_string(i) + ".png");
			helmetRunTextures[4 + i].loadFromFile("assets/hero/basicHelmet/runRight" + to_string(i) + ".png");
			helmetRunTextures[8 + i].loadFromFile("assets/hero/basicHelmet/runBottom" + to_string(i) + ".png");
			helmetRunTextures[12 + i].loadFromFile("assets/hero/basicHelmet/runLeft" + to_string(i) + ".png");

			helmetAttackTextures[i].loadFromFile("assets/hero/basicHelmet/attackTop" + to_string(i) + ".png");
			helmetAttackTextures[4 + i].loadFromFile("assets/hero/basicHelmet/attackRight" + to_string(i) + ".png");
			helmetAttackTextures[8 + i].loadFromFile("assets/hero/basicHelmet/attackBottom" + to_string(i) + ".png");
			helmetAttackTextures[12 + i].loadFromFile("assets/hero/basicHelmet/attackLeft" + to_string(i) + ".png");

		}

	}

	void loadTextures() {

		loadBodyTextures();
		loadHelmetTextures();
		
	}

	void setActionRangeArea() {
		actionRangeArea = sf::CircleShape(actionRange + collider->width/2.0f);
		actionRangeArea.setFillColor(sf::Color(128, 64, 64, 128));
		actionRangeArea.setOutlineColor(sf::Color(196, 64, 64, 128));
		actionRangeArea.setOutlineThickness(4.0f);
		actionRangeArea.setOrigin(actionRange + collider->width / 2.0f, actionRange + collider->width/2.0f);
		actionRangeArea.setScale(1.0f, collider->height/collider->width);
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

	void takeDamage(float damage) {
		HP -= damage;
		if (HP < 0)
			HP = 0;
	}
	
	float getDamage() {
		return 10;
	}

	void heal(float HP) {
		this->HP += HP;

		if (this->HP > HP_max)
			this->HP = HP_max;
	}

	void collectItem(Item* item, int count = 1) {

		bag->addItem(item,count);
	}

	void update(float dt) {

		GameObject::update(dt);

		float distance = 20.0f * stepSize * dt;

		if (state == states::attack) {
		
			if (cooldown <= 0.0f)
			{
				state = states::idle;
				frame = 0;
			}
			frame = cooldown / attackTime * 4.0f - 1.0f;
			if (frame < 0)
				frame = 0;
			bodySprite.setTexture(bodyAttackTextures[direction * 4 + frame]);
			helmetSprite.setTexture(helmetAttackTextures[direction * 4 + frame]);
		}		
		else if (state == states::walk) {

			calculateCurrentFrame(dt);
			state = states::idle;

			if (direction == 0) position.y -= distance;
			if (direction == 1) position.x += distance;
			if (direction == 2) position.y += distance;
			if (direction == 3) position.x -= distance;

			bodySprite.setTexture(bodyRunTextures[direction * 4 + frame]);
			helmetSprite.setTexture(helmetRunTextures[direction * 4 + frame]);
		}
		else if(state == states::idle) {

			calculateCurrentFrame(dt);
			bodySprite.setTexture(bodyIdleTextures[direction * 4 +frame]);
			helmetSprite.setTexture(helmetIdleTextures[direction * 4 +frame]);
			
		}

		if (cooldown > 0.0f)
			cooldown -= dt;

		bodySprite.setPosition(position);
		helmetSprite.setPosition(position);
		actionRangeArea.setPosition(position);
		
	}

	void draw(sf::RenderWindow* window) {
		if (mouseIsOver) {
			window->draw(actionRangeArea);
			GameObject::draw(window);
		}
		
		window->draw(bodySprite);		
		
	}
};

Player* player = nullptr;

void createPlayer() {
	player = new Player();

	player->position.x = 0;
	player->position.y = 0;
	
	player->isVisible = true;

	gameObjects.push_back(player);
}
#endif