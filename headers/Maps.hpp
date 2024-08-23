#ifndef Maps_hpp
#define Maps_hpp

// TO-DO - all to the rewrite

class Map {
public:
    sf::Vector2i coords;
    Terrain* terrain;
    Floors* floors;
    
    std::vector < Nature* > _natures;
    std::vector < ItemOnMap* > _itemsOnMap;
    std::vector < Path* > _paths;
    std::vector < Furniture* > _furnitures;
    std::vector < Wall* > _walls;
    std::vector < Monster* > _monsters;
    std::vector < Building* > _buildings;
    std::vector < Character* > _characters;
    std::vector < InventoryOnMap* > _inventoriesOnMap;

    bool isVisible;

    Map(int x, int y) {
       
        coords = sf::Vector2i(x, y);
        terrain = new Terrain(x*16, y*16, 16, 16);
        floors = new Floors(x*16, y*16, 16, 16);

        clearAllLists();
        //load();

        isVisible = false;
    }

    ~Map() { }

    void clearAllLists() {

        _natures.clear();
        _itemsOnMap.clear();
        _paths.clear();
        _furnitures.clear();
        _walls.clear();
        _monsters.clear();
        _buildings.clear();
        _characters.clear();
        _inventoriesOnMap.clear();
        
    }

    void save() {

        // create a folder when it no exists
        if (!std::filesystem::exists("world/maps")) {
            
            if (std::filesystem::create_directory("world/maps")) {
                cout << "create directory \"world\/maps\"\n";
            }
            else {
                cout << "error with create a directory \"world\/maps\n";
            }
        }

        string filename = "world/maps/map_" + to_string(int(terrain->coords.x)) + "_" + to_string(int(terrain->coords.y)) + ".txt";
        std::ofstream file(filename);

        if (!file.is_open()) {
            cout << "cant open file to save map: " << filename << "\n";
            return;
        }

        // save tiles
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {

                file << terrain->tiles[y*terrain->width + x];
                if (x != terrain->width-1 )
                    file << " ";
            }

            file << "\n";
        }

        file << "\n";

        // save floors
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {

                file << floors->floors[y*floors->width + x];
                if (x != floors->width-1)
                    file << " ";
            }

            file << "\n";
        }

        file << "\n";

        if(_natures.size() > 0)
            file << "// NATURES\n";
        for (auto& nature : _natures)
            file << "Nature " << char(34) << nature->name << char(34) << " " << int(nature->position.x) << " " << int(nature->position.y) << "\n";
        if (_natures.size() > 0)
            file << "\n";


        if (_itemsOnMap.size() > 0)
            file << "// ITEMS\n";
        for (auto& item : _itemsOnMap)
            file << "Item " << char(34) << item->name << char(34) << " " << int(item->position.x) << " " << int(item->position.y) << "\n";
        if (_itemsOnMap.size() > 0)
            file << "\n";


        if (_paths.size() > 0)
            file << "// PATHS\n";
        for (auto& path : _paths)
            file << "Path " << char(34) << path->name << char(34) << " " << int(path->position.x) << " " << int(path->position.y) << "\n";
        if (_paths.size() > 0)
            file << "\n";


        if (_furnitures.size() > 0)
            file << "// FURNITURES\n";
        for (auto& furniture : _furnitures)
            file << "Furniture " << char(34) << furniture->name << char(34) << " " << int(furniture->position.x) << " " << int(furniture->position.y) << "\n";
        if (_furnitures.size() > 0)
            file << "\n";


        if (_walls.size() > 0)
            file << "// WALLS\n";
        for (auto& wall : _walls)
            file << "Wall " << char(34) << wall->name << char(34) << " " << int(wall->position.x) << " " << int(wall->position.y) << "\n";
        if (_walls.size() > 0)
            file << "\n";


        if (_monsters.size() > 0)
            file << "// MONSTERS\n";
        for (auto& monster : _monsters)
            file << "Monster " << char(34) << monster->name << char(34) << " " << int(monster->position.x) << " " << int(monster->position.y) << "\n";
        if (_monsters.size() > 0)
            file << "\n";


        
        if(_buildings.size() > 0)
            file << "// BUILDINGS\n";
        for (auto& building : _buildings)
            file << "Building " << char(34) << building->name << char(34) << " " << int(building->position.x) << " " << int(building->position.y) << "\n";
        if (_buildings.size() > 0)
            file << "\n";


        if (_characters.size() > 0)
            file << "// CHARACTERS\n";
        for (auto& character : _characters)
            file << "Character " << char(34) << character->name << char(34) << " " << int(character->position.x) << " " << int(character->position.y) << "\n";
        if (_characters.size() > 0)
            file << "\n";


        if (_inventoriesOnMap.size() > 0)
            file << "// INVENTORIES\n";
        for (auto& inventory : _inventoriesOnMap)
            file << "Inventory " << char(34) << inventory->name << char(34) << " " << int(inventory->position.x) << " " << int(inventory->position.y) << "\n";
        if (_inventoriesOnMap.size() > 0)
            file << "\n";



        file.close();
    }

    void load() {

        string filename = "world/maps/map_" + to_string(coords.x) + "_" + to_string(coords.y) + ".txt";
        ifstream file(filename);

        if (!file.is_open()) {
            //cout << "cant open map: " << filename << "\n";
            return;
        }
            
        //cout << "open map: " << filename << "\n";

        string line;
        string objectType;
        string objectName;

        // load tiles
        int value;
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                file >> value;
                editTile(x, y, value);;
            }
        }

        // load floors
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                file >> value;
                editFloor(x, y, value);;
            }
        }

        // load GameObjects
        while (std::getline(file, line)) {

            if (line.empty()) {
                //cout << "empty line\n";
                continue;
            }
                

            std::istringstream lineStream(line);
            lineStream >> objectType;

            if (objectType == "Nature") {

                int x, y;
                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                Nature* nature = new Nature(getPrefab(objectName), x, y);
                _natures.push_back(nature);
                //cout << "Nature: " << objectName << "\n";
            }

            if (objectType == "Item") {

                int x, y;
                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                ItemOnMap* itemOnMap = new ItemOnMap(getItem(objectName), x, y);
                _itemsOnMap.push_back(itemOnMap);
                //cout << "Item: " << objectName << "\n";

            }

            if (objectType == "Path") {

                string name;
                int x, y;
                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                Path* path = new Path(getPrefab(objectName), x, y);
                _paths.push_back(path);
                //cout << "Path: " << objectName << "\n";
            }

            if (objectType == "Furniture") {
                string name;
                int x, y;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                Furniture* furniture = new Furniture(getPrefab(objectName), x, y);
                _furnitures.push_back(furniture);
                //cout << "Furniture: " << objectName << "\n";
            }

            if (objectType == "Wall") {
                string name;
                int x, y;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
               lineStream >> y;

                Wall* wall = new Wall(getPrefab(objectName), x, y);
                _walls.push_back(wall);
                //cout << "Wall: " << objectName << "\n";
            }

            if (objectType == "Monster") {

                int x, y;
                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                Monster* monster = new Monster(getPrefab(objectName), x, y);
                _monsters.push_back(monster);
                //cout << "Monster: " << objectName << "\n";
            }

            if (objectType == "Building") {
                int x, y;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                Building* building = new Building(objectName, x, y);
                _buildings.push_back(building);
                //cout << "Building: " << objectName << "\n";
            }

            if (objectType == "Character") {
                int x, y;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                Character* character = new Character(getPrefab(objectName), x, y);
                _characters.push_back(character);

                //cout << "Character: " << objectName << "\n";
            }

            if (objectType == "Inventory") {
                int x, y;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                // TO-DO
            }
        }

        file.close();
    }

    void editTile(sf::Vector2f worldMousePosition, int value) {

        terrain->edit(worldMousePosition, value);
    }

    void editTile(int x, int y, int value) {
        terrain->edit(x, y, value);
        
    }

    void editFloor(sf::Vector2f worldMousePosition, int value) {

        floors->edit(worldMousePosition, value);
    }

    void editFloor(int x, int y, int value) {

        floors->edit(x, y, value);
    }

    void addGameObjectsToMainLists() {

        for (auto& nature : _natures) {
            gameObjects.push_back(nature);
            natures.push_back(nature);
        }

        for (auto& item : _itemsOnMap) {
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
        }

        for (auto& path : _paths) {
            gameObjects.push_back(path);
            paths.push_back(path);
        }

        for (auto& furniture : _furnitures) {
            gameObjects.push_back(furniture);
            furnitures.push_back(furniture);
        }

        for (auto& wall : _walls) {
            gameObjects.push_back(wall);
            walls.push_back(wall);
        }

        for (auto& monster : _monsters) {
            gameObjects.push_back(monster);
            monsters.push_back(monster);
        }

        for (auto& building : _buildings) {
            building->addGameObjectsToMainLists();
        }

        for (auto& character : _characters) {
            gameObjects.push_back(character);
            characters.push_back(character);
        }

        for (auto& inventory : _inventoriesOnMap) {
            gameObjects.push_back(inventory);
            inventoriesOnMap.push_back(inventory);
        }
    }

    void deleteGameObjects() {

        std::vector < Nature* > new_natures;
        std::vector < ItemOnMap* > new_itemsOnMap;
        std::vector < Path* > new_paths;
        std::vector < Furniture* > new_furnitures;
        std::vector < Wall* > new_walls;
        std::vector < Monster* > new_monsters;
        std::vector < Building* > new_buildings;
        std::vector < Character* > new_characters;
        std::vector < InventoryOnMap* > new_inventoriesOnMap;
        
        new_natures.clear();
        new_itemsOnMap.clear();
        new_paths.clear();
        new_furnitures.clear();
        new_walls.clear();
        new_monsters.clear();
        new_buildings.clear();
        new_characters.clear();
        new_inventoriesOnMap.clear();
        

        for (auto& nature : _natures)
            if (nature->toDelete != true)
                new_natures.push_back(nature);

        for (auto& item : _itemsOnMap)
            if (item->toDelete != true)
                new_itemsOnMap.push_back(item);

        for (auto& path : _paths)
            if (path->toDelete != true)
                new_paths.push_back(path);

        for (auto& furniture : _furnitures)
            if (furniture->toDelete != true)
                new_furnitures.push_back(furniture);

        for (auto& wall : _walls)
            if (wall->toDelete != true)
                new_walls.push_back(wall);

        for (auto& monster : _monsters)
            if (monster->toDelete != true)
                new_monsters.push_back(monster);

        for (auto& building : _buildings)
            if (building->toDelete != true)
                new_buildings.push_back(building);

        for (auto& character : _characters)
            if (character->toDelete != true)
                new_characters.push_back(character);

        for (auto& inventory : _inventoriesOnMap)
            if (inventory->toDelete != true)
                new_inventoriesOnMap.push_back(inventory);
        
        _natures = new_natures;
        _itemsOnMap = new_itemsOnMap;
        _paths = new_paths;
        _furnitures = new_furnitures;
        _walls = new_walls;
        _monsters = new_monsters;
        _buildings = new_buildings;
        _characters = new_characters;
        _inventoriesOnMap = new_inventoriesOnMap;
        

    }

    void draw()
    {
        window->draw(*terrain);
        window->draw(*floors);
    }

};

class World {
public:
    std::vector < Map* > maps;

    World() {

        maps.clear();
    }

    void load() {

        maps.clear();

        // 8 x 4
        int start_x = 0;
        int end_x = 16;
        int start_y = 0;
        int end_y = 16;

        // CREATING MAPS
        for (int y = start_y; y <= end_y; y++)
            for (int x = start_x; x <= end_x; x++)
                maps.push_back(new Map(x, y));

        for (auto& map : maps) {
            map->load();
        }


        // MAP IS VISIBLE OR NOT
        mapVisiblings();

        // ADDING ALL THE GAMEOBJECTS FROM MAP TO MAIN LISTS OF GAMEOBJECTS
        clearAllMainListsOfGameObjects();

        for (auto& map : maps)
            map->addGameObjectsToMainLists();

    }

    Map* getMap(sf::Vector2f worldMousePosition) {
        
        float left, right, top, bottom;

        for (auto& m : maps) {

            left = m->coords.x * 16 * tileSide;
            right = left + m->terrain->width * tileSide;
            top = m->coords.y * 16 * tileSide;
            bottom = top + m->terrain->height * tileSide;

            if (worldMousePosition.x >= left && worldMousePosition.x <= right && worldMousePosition.y >= top && worldMousePosition.y <= bottom)
            {
                cout << m->coords.x << ", " << m->coords.y << "\n";
                return m;

            }
        }
          
        return nullptr;
    }

    void mapVisiblings() {

        sf::Vector2f map_position;

        for (auto& map : maps) {

            map_position.x = (map->terrain->coords.x * tileSide) + 8 * tileSide;
            map_position.y = (map->terrain->coords.y * tileSide) + 8 * tileSide;

            float width = screenWidth * 2.0f;
            float height = screenHeight * 2.0f;

            map->isVisible = intersectionTwoRectangles(cam->position.x, cam->position.y, width, height, map_position.x, map_position.y, map->terrain->width*tileSide, map->terrain->height*tileSide );

        }


    }

    void save() {

        for (auto& map : maps)
            map->save();
    }

    void draw() {
        //sf::Clock c;
        //sf::Time start = c.getElapsedTime();

        int i = 0;

        for (auto& map : maps) {
            if (map->isVisible)
                map->draw();
        }

        //sf::Time end = c.getElapsedTime();
        // 
        //cout << (end - start).asMilliseconds() << " ms,\t";
        //cout << (end - start).asSeconds() << " s \n";
    }


};

World* world = nullptr;

#endif
