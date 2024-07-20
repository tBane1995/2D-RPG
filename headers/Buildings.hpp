#ifndef Buildings_hpp
#define Buildings_hpp

class Building : public GameObject {
public:
	sf::Vector2i size;
	std::vector < ItemOnMap* > _items;
	std::vector < Furniture* > _furnitures;
	std::vector < Wall* > _walls;

	Building(string name, float x, float y) : GameObject(name, x, y) {

        string filename = "assets/" + name + ".txt";
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "cant open building script: " << filename << "\n";
            return;
        }

        string line;
        string objectType;
        string objectName;

        std::getline(file, line);   // name
        std::getline(file, line);   // texture name
        

        // SIZE
        std::getline(file, line);
        std::istringstream lineStream(line);
        lineStream >> objectType;
        lineStream >> size.x >> size.y;
        //cout << size.x << " " << size.y << "\n";

        std::getline(file, line);
        std::getline(file, line);

        // LOAD FLOORS - TUTAJ WYSTĘPUJE BŁĄD
        int value;
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                file >> value;
                //cout << value << " ";
                //editFloor(x, y, value);;
            }
            //cout << "\n";
        }

        // LOAD GAMEOBJECTS
        while (std::getline(file, line)) {

            if (line.empty()) {
                //cout << "empty line\n";
                continue;
            }


            std::istringstream lineStream(line);
            lineStream >> objectType;

            //cout << objectType << "\n";

            if (objectType == "Item") {

                int x, y;
                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                x = x - (size.x * 16 / 2) + position.x;
                y = y - (size.y * 16 / 2) + position.y;

                ItemOnMap* item = new ItemOnMap(getItem(objectName), x, y);
                _items.push_back(item);
                //cout << "Item: " << objectName << "\n";

            }

            if (objectType == "Furniture") {
                string name;
                int x, y;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;

                x = x - (size.x * 16/2) + position.x;
                y = y - (size.y * 16/2) + position.y;

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

                x = x - (size.x * 16 / 2) + position.x;
                y = y - (size.y * 16 / 2) + position.y;

                Wall* wall = new Wall(getPrefab(objectName), x, y);
                _walls.push_back(wall);
                //cout << "Wall: " << objectName << "\n";
            }

        }

        file.close();

	}

	void addGameObjectsToMainLists() {
        
        for (auto& item : _items) {
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
        }

        for (auto& furniture : _furnitures) {
            gameObjects.push_back(furniture);
            furnitures.push_back(furniture);
        }

        for (auto& wall : _walls) {
            gameObjects.push_back(wall);
            walls.push_back(wall);
        }
	}
    
    bool gameObjectInBuilding(GameObject* object) {

        int left = position.x - float(size.x) / 2.0f * 16.f;
        int right = position.x + float(size.x) / 2.0f * 16.f;
        int top = position.x - float(size.y) / 2.0f * 16.f;
        int bottom = position.x + float(size.y) / 2.0f * 16.f;

        if (object->position.x > left && object->position.x < right && object->position.y > top && object->position.y < bottom)
            return true;
        else
            return false;
    }
};

std::vector < Building* > buildings;

#endif