#ifndef TerrainAndFloors_hpp
#define TerrainAndFloors_hpp

float tileSide = 16.0f;

enum class terrainType { grass, sands, water, gravel };
enum class floorType { floor_0, floor_1, floor_2, floor_3 };

class TerrainPrefab : public GameObject {
public:
	Texture* texture;
	terrainType ttype;

	TerrainPrefab(string name, terrainType ttype) : GameObject(name) {
		type = gameObjectType::Terrain;
		texture = getTexture(name);
		this->ttype = ttype;
	}
	
};

class FloorPrefab : public GameObject {
public:
	Texture* texture;
	floorType ftype;

	FloorPrefab(string name, floorType ftype) : GameObject(name) {
		type = gameObjectType::Floor;
		texture = getTexture(name);
		this->ftype = ftype;
	}

};

class Terrain : public sf::Drawable, public sf::Transformable {
public:
	int width, height;
	sf::Vector2i coords;

	sf::VertexArray vertexes;
	sf::Texture tileset;

	std::vector < int > tiles;

	Terrain(int x, int y, int width, int height ) {

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		tileset = sf::Texture();
		tileset = *getTexture("tiles/0_tileset")->texture;

		vertexes.setPrimitiveType(sf::Triangles);
		vertexes.resize(width * height * 6); // widthMap * heightMap * TwoTrianglesVertices

		tiles.resize(width * height);

		int tu, tv;
		int coord_x, coord_y;

		// TERRAIN - GRASS
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++) {

				sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

				coord_x = (coords.x * width + x);
				coord_y = (coords.y * height + y);

				triangles[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				triangles[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, 0);
			}

		
	}

	void edit(int x, int y, int value) {

		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		if (value > 3 || value < 0)
			return;

		tiles[y * width + x] = value;

		int global_x = coords.x * width + x;
		int global_y = coords.y * height + y;

		sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

		int tu = (int(global_x * tileSide) % 64) + (value * 64);
		int tv = (int(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, int value) {

		int global_x = worldMousePosition.x / 16;
		int global_y = worldMousePosition.y / 16;

		int onMap_x = global_x - coords.x * width;
		int onMap_y = global_y - coords.y * height;

		if (onMap_x < 0 || onMap_x >= width || onMap_y < 0 || onMap_y >= height)
			return;

		if (value > 3 || value < 0)
			return;

		tiles[onMap_y * width + onMap_x] = value;

		sf::Vertex* triangles = &vertexes[(onMap_y * width + onMap_x) * 6];

		int tu = (int(global_x * tileSide) % 64) + (value * 64);
		int tv = (int(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, TerrainPrefab* terrainPrefab) {

		if (terrainPrefab->name == "tiles/tile_0_grass")
			edit(worldMousePosition, 0);

		if (terrainPrefab->name == "tiles/tile_1_sands")
			edit(worldMousePosition, 1);

		if (terrainPrefab->name == "tiles/tile_2_water")
			edit(worldMousePosition, 2);

		if (terrainPrefab->name == "tiles/tile_3_gravel")
			edit(worldMousePosition, 3);
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		// draw tiles - terrain
		states.transform *= getTransform();
		states.texture = &tileset;	// TO-DO
		target.draw(vertexes, states);
	}
};

class Floors : public sf::Drawable, public sf::Transformable {
public:
	int width, height;
	sf::Vector2i coords;

	sf::VertexArray vertexes;
	sf::Texture floorset;

	std::vector < int > floors;

	Floors(int x, int y, int width, int height) {
		
		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		floorset = sf::Texture();
		floorset = *getTexture("floors/0_floorset")->texture;

		vertexes.setPrimitiveType(sf::Triangles);
		vertexes.resize(width * height * 6); // widthMap * heightMap * TwoTrianglesVertices

		floors.resize(width * height);

		int coord_x, coord_y;

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++) {

				sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

				coord_x = (coords.x * width + x);
				coord_y = (coords.y * height + y);

				triangles[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				triangles[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
				triangles[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				triangles[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, 0);
			}


	}

	void edit(int x, int y, int value) {

		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		if (value > 3 || value < 0)
			return;

		floors[y * width + x] = value;

		int global_x = coords.x * width + x;
		int global_y = coords.y * height + y;

		sf::Vertex* triangles = &vertexes[(y * width + x) * 6];

		int tu = (int(global_x * tileSide) % 64) + (value * 64);
		int tv = (int(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, int value) {

		int global_x = worldMousePosition.x / 16;
		int global_y = worldMousePosition.y / 16;

		int onMap_x = global_x - coords.x * width;
		int onMap_y = global_y - coords.y * height;

		if (onMap_x < 0 || onMap_x >= width || onMap_y < 0 || onMap_y >= height)
			return;

		if (value > 3 || value < 0)
			return;

		floors[onMap_y * width + onMap_x] = value;

		sf::Vertex* triangles = &vertexes[(onMap_y * width + onMap_x) * 6];

		int tu = (int(global_x * tileSide) % 64) + (value * 64);
		int tv = (int(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		triangles[0].texCoords = sf::Vector2f(tu, tv);
		triangles[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[2].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[3].texCoords = sf::Vector2f(tu, tv + tileSide);
		triangles[4].texCoords = sf::Vector2f(tu + tileSide, tv);
		triangles[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, FloorPrefab* floorPrefab) {

		if (floorPrefab->name == "floors/floor_0")
			edit(worldMousePosition, 0);

		if (floorPrefab->name == "floors/floor_1")
			edit(worldMousePosition, 1);

		if (floorPrefab->name == "floors/floor_2")
			edit(worldMousePosition, 2);

		if (floorPrefab->name == "floors/floor_3")
			edit(worldMousePosition, 3);
	}


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		states.transform *= getTransform();
		states.texture = &floorset;	// TO-DO
		target.draw(vertexes, states);


	}
};
#endif