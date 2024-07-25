#ifndef Textures_hpp
#define Textures_hpp

using namespace std;

class Texture {
public:
	string name;
	sf::Texture* texture;
	float cx, cy;	// coordinates of center on the texture

	Texture(string pathfile, float cx, float cy) {
		
		name = "";

		int i = int(pathfile.size()) - 5;
		while ( i>=0)
			name = pathfile[i--] + name;

		this->cx = cx;
		this->cy = cy;

		texture = new sf::Texture;
		texture->loadFromFile("assets/" + pathfile);

		//cout << "load texture: " << pathfile << " as: " << name << endl;
	}

};

std::vector < Texture* > textures;

void loadTexture(string pathfile, float cx, float cy) {
	textures.push_back( new Texture(pathfile, cx, cy) );
}

void loadTextures() {

	textures.clear();

	// GUI ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("GUI/slotTexture1.png", 40, 40);
	loadTexture("GUI/slotTexture2.png", 40, 40);
	loadTexture("GUI/wideArrowUp1.png", 80, 20);
	loadTexture("GUI/wideArrowUp2.png", 80, 20);
	loadTexture("GUI/wideArrowDown1.png", 80, 20);
	loadTexture("GUI/wideArrowDown2.png", 80, 20);
	loadTexture("GUI/hand.png", 8, 8);
	loadTexture("GUI/talk.png", 8, 8);

	// TILES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("tiles/tile_0_grass.png", 32, 32);
	loadTexture("tiles/tile_1_sands.png", 32, 32);
	loadTexture("tiles/tile_2_water.png", 32, 32);
	loadTexture("tiles/tile_3_gravel.png", 32, 32);


	// FLOORS
	loadTexture("floors/floor_0.png", 32, 32);
	loadTexture("floors/floor_1.png", 32, 32);
	loadTexture("floors/floor_2.png", 32, 32);
	loadTexture("floors/floor_3.png", 32, 32);

	// NATURES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("natures/tree1.png", 126, 185);
	loadTexture("natures/tree2.png", 113, 220);
	loadTexture("natures/bush1.png", 140, 150);
	loadTexture("natures/rocks1.png", 130, 170);
	loadTexture("natures/rocks2.png", 130, 190);
	loadTexture("natures/rocks3.png", 130, 160);

	// BUILDINGS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("buildings/temple.png", 125, 185);
	loadTexture("buildings/column.png", 130, 200);
	loadTexture("buildings/home.png", 128, 185);

	loadTexture("buildings/stone house.png", 80, 152);	//80, 160 - 16/2
	loadTexture("buildings/mud house.png", 80, 152);
	loadTexture("buildings/demo house.png", 128, 256); // 128, 384 - 8*16


	// ITEMS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	loadTexture("items/bag.png", 28, 48);

	// WEAPONS
	loadTexture("items/club.png", 32, 32);
	loadTexture("items/knife.png", 32, 32);
	loadTexture("items/hatchet.png", 32, 32);
	loadTexture("items/sword.png", 32, 32);
	loadTexture("items/dagger.png", 32, 32);
	loadTexture("items/wooden club.png", 32, 32);
	loadTexture("items/long sword.png", 32, 32);
	loadTexture("items/curved sword.png", 32, 32);
	loadTexture("items/wide blade.png", 32, 32);
	loadTexture("items/gladius.png", 32, 32);
	loadTexture("items/iron club.png", 32, 32);
	loadTexture("items/axe.png", 32, 32);
	loadTexture("items/stone hammer.png", 32, 32);

	// HELMET
	loadTexture("items/basic helmet.png", 32, 32);	// TO-DO to delete
	loadTexture("items/skin helmet.png", 32, 32);	// TO-DO to delete

	// ARMORS
	loadTexture("items/basic armor.png", 32, 32);	// TO-DO to delete
	loadTexture("items/skin jacket.png", 32, 32);	// TO-DO to delete

	// PANTS
	loadTexture("items/basic pants.png", 32, 32);	// TO-DO to delete
	loadTexture("items/skin pants.png", 32, 32);	// TO-DO to delete

	// HERBS
	loadTexture("items/herb.png", 30, 50);
	loadTexture("items/health herb.png", 32, 34);
	loadTexture("items/health root.png", 31, 46);	
	loadTexture("items/health plant.png", 30, 44);
	loadTexture("items/mushroom.png", 30, 44);

	// POTIONS
	loadTexture("items/potion.png", 32, 32);

	// FOOD
	loadTexture("items/raw meat.png", 32, 32);
	loadTexture("items/roasted meat.png", 32, 32);

	// OTHERS
	loadTexture("items/bone.png", 32, 32);
	loadTexture("items/bone1.png", 40, 40);
	loadTexture("items/tooth.png", 32, 32);
	loadTexture("items/wolf skin.png", 32, 32);

	// PATHS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadTexture("paths/stonepath1.png", 32, 32);
	loadTexture("paths/stonepath2.png", 32, 32);


	// CHARACTERS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector < string > characters;
	characters.push_back("characters/jack");
	characters.push_back("characters/john");
	characters.push_back("characters/peter");
	characters.push_back("characters/pit");

	for (auto& c : characters) {
		for (int i = 0; i < 4; i++) {

			loadTexture(c + "/idleTop" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/idleRight" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/idleBottom" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/idleLeft" + to_string(i) + ".png", 32, 58);

			loadTexture(c + "/attackTop" + to_string(i) + ".png", 32, 87);
			loadTexture(c + "/attackRight" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/attackBottom" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/attackLeft" + to_string(i) + ".png", 32, 58);

			loadTexture(c + "/walkTop" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/walkRight" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/walkBottom" + to_string(i) + ".png", 32, 58);
			loadTexture(c + "/walkLeft" + to_string(i) + ".png", 32, 58);

		}
	}

	// MONSTERS
	std::vector < string > monsters;
	monsters.push_back("wilczur");
	monsters.push_back("goblin");
	monsters.push_back("dziobak");

	for (auto& m : monsters) {
		for (int i = 0; i < 4; i++) {

			loadTexture("monsters/" + m + ".png", 63, 87);

			loadTexture("monsters/" + m + "/idleTop" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/idleRight" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/idleBottom" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/idleLeft" + to_string(i) + ".png", 63, 87);

			loadTexture("monsters/" + m + "/attackTop" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/attackRight" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/attackBottom" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/attackLeft" + to_string(i) + ".png", 63, 87);

			loadTexture("monsters/" + m + "/walkTop" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/walkRight" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/walkBottom" + to_string(i) + ".png", 63, 87);
			loadTexture("monsters/" + m + "/walkLeft" + to_string(i) + ".png", 63, 87);

		}
	}
	
	// FURNITURES
	loadTexture("furnitures/table1.png", 32, 32);
	loadTexture("furnitures/bench1.png", 32, 32);
	loadTexture("furnitures/chest1.png", 32, 32);
	loadTexture("furnitures/wardrobe1.png", 32, 50);
	loadTexture("furnitures/bookshelf1.png", 32, 50);
	loadTexture("furnitures/furnace1.png", 32, 50);
	loadTexture("furnitures/bed1.png", 32, 50);
	loadTexture("furnitures/chair1.png", 34, 38);
	loadTexture("furnitures/barrel1.png", 34, 38);
	loadTexture("furnitures/lectern1.png", 34, 38);

	loadTexture("walls/wooden_wall_bottom.png", 16, 16);
	loadTexture("walls/wooden_wall_top_0.png", 16, 16);
	loadTexture("walls/wooden_wall_top_1.png", 16, 16);
	loadTexture("walls/wooden_wall_top_2.png", 16, 16);
	loadTexture("walls/wooden_wall_top_3.png", 16, 16);
	loadTexture("walls/wooden_wall_top_4.png", 16, 16);
	loadTexture("walls/wooden_wall_top_5.png", 16, 16);
	loadTexture("walls/wooden_wall_top_6.png", 16, 16);
	loadTexture("walls/wooden_wall_top_7.png", 16, 16);
	loadTexture("walls/wooden_wall_top_8.png", 16, 16);
	loadTexture("walls/wooden_wall_top_9.png", 16, 16);

	loadTexture("walls/stone_wall_bottom.png", 16, 16);
	loadTexture("walls/stone_wall_top_0.png", 16, 16);
	loadTexture("walls/stone_wall_top_1.png", 16, 16);
	loadTexture("walls/stone_wall_top_2.png", 16, 16);
	loadTexture("walls/stone_wall_top_3.png", 16, 16);
	loadTexture("walls/stone_wall_top_4.png", 16, 16);
	loadTexture("walls/stone_wall_top_5.png", 16, 16);
	loadTexture("walls/stone_wall_top_6.png", 16, 16);
	loadTexture("walls/stone_wall_top_7.png", 16, 16);
	loadTexture("walls/stone_wall_top_8.png", 16, 16);
	loadTexture("walls/stone_wall_top_9.png", 16, 16);

	loadTexture("walls/mud_wall_bottom.png", 16, 16);
	loadTexture("walls/mud_wall_top_0.png", 16, 16);
	loadTexture("walls/mud_wall_top_1.png", 16, 16);
	loadTexture("walls/mud_wall_top_2.png", 16, 16);
	loadTexture("walls/mud_wall_top_3.png", 16, 16);
	loadTexture("walls/mud_wall_top_4.png", 16, 16);
	loadTexture("walls/mud_wall_top_5.png", 16, 16);
	loadTexture("walls/mud_wall_top_6.png", 16, 16);
	loadTexture("walls/mud_wall_top_7.png", 16, 16);
	loadTexture("walls/mud_wall_top_8.png", 16, 16);
	loadTexture("walls/mud_wall_top_9.png", 16, 16);
	

	// BODY SET
	for (int i = 0; i < 4; i++) {

		loadTexture("sets/hero/idleTop" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/idleRight" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/idleBottom" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/idleLeft" + to_string(i) + ".png", 32, 58);

		loadTexture("sets/hero/runTop" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/runRight" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/runBottom" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/runLeft" + to_string(i) + ".png", 32, 58);

		loadTexture("sets/hero/attackTop" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/attackRight" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/attackBottom" + to_string(i) + ".png", 32, 58);
		loadTexture("sets/hero/attackLeft" + to_string(i) + ".png", 32, 58);

	}

	// SETS

	std::vector < string > sets;
	sets.push_back("basic armor");
	sets.push_back("basic pants");
	sets.push_back("basic helmet");
	sets.push_back("skin jacket");
	sets.push_back("skin pants");
	sets.push_back("skin helmet");


	for (auto& set : sets) {

		for (int i = 0; i < 4; i++) {
			
			loadTexture("sets/items/" + set + "/idleTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/idleRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/idleBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/idleLeft" + to_string(i) + ".png", 32, 58);

			loadTexture("sets/items/" + set + "/runTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/runRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/runBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/runLeft" + to_string(i) + ".png", 32, 58);

			loadTexture("sets/items/" + set + "/attackTop" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/attackRight" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/attackBottom" + to_string(i) + ".png", 32, 58);
			loadTexture("sets/items/" + set + "/attackLeft" + to_string(i) + ".png", 32, 58);

		}
	}
}

Texture* getTexture(string name) {

	for (auto& t : textures) {
		if (t->name == name) {
			return t;
		}
	}

	cout << "error - getTexture - texture: \"" << name << "\" not exists\n";
	return nullptr;
}

#endif