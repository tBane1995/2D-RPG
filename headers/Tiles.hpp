#ifndef Terrain_hpp
#define Terrain_hpp

float tileSide = 16.0f;

enum class terrainType { grass, sands, water, gravel };
enum class floorType { floor_0, floor_1, floor_2, floor_3 };

class Terrain : public GameObject {
public:
	Texture* texture;
	terrainType ttype;

	Terrain(string name, terrainType ttype) : GameObject(name) {
		type = gameObjectType::Terrain;
		texture = getTexture(name);
		this->ttype = ttype;
	}
	
};

class Floor : public GameObject {
public:
	Texture* texture;
	floorType ftype;

	Floor(string name, floorType ftype) : GameObject(name) {
		type = gameObjectType::Floor;
		texture = getTexture(name);
		this->ftype = ftype;
	}

};

#endif