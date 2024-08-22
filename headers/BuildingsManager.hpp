#ifndef BuildingsManager_hpp
#define BuildingsManager_hpp

class Building : public GameObject {
public:
	sf::Vector2i size;
	std::vector < ItemOnMap* > _items;
	std::vector < Furniture* > _furnitures;
	std::vector < Wall* > _walls;
    sf::RectangleShape rect;
    Floors* floors;

	Building(string name, float x, float y) : GameObject(name, x, y) {

        rect = sf::RectangleShape(sf::Vector2f(size.x * 16, size.y * 16));
        rect.setFillColor(sf::Color(128, 48, 48, 128));
        rect.setOrigin(size.x / 2 * 16, size.y / 2 * 16);
        rect.setPosition(position);
        rect.setOutlineThickness(2);
        rect.setOutlineColor(sf::Color(192, 48, 48, 128));
        cout << "mouse is over\n";

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

        // LOAD FLOORS - TO-DO
        cout << position.x/16 << ", " << position.y << "\n";
        cout << size.x << ", " << size.y << "\n";
        floors = new Floors(position.x/16, position.y/16, size.x, size.y);
        int value;
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                file >> value;
                cout << value << " ";
                floors->edit(x, y, value);;
            }
            cout << "\n";
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
    


    bool mouseIsOver(sf::Vector2f worldMousePosition) {

        int left = position.x - size.x/2 * 16;
        int right = position.x + size.x/2 * 16;
        int top = position.y - size.y/2 * 16;
        int bottom = position.y + size.y/2 * 16;

        if (worldMousePosition.x >= left && worldMousePosition.x <= right && worldMousePosition.y >= top && worldMousePosition.y <= bottom) {
            return true;
        }

        return false;

    }

    void deleteBuilding() {
        toDelete = true;

        for (auto& item : _items)
            item->toDelete = true;

        for (auto& furniture : _furnitures)
            furniture->toDelete = true;

        for (auto& wall : _walls)
            wall->toDelete = true;
    }
};

std::vector < Building* > buildings;

#endif