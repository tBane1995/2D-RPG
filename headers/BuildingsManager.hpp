#ifndef BuildingsManager_hpp
#define BuildingsManager_hpp

class Building : public GameObject {
public:
	sf::Vector2i size;
	std::vector < ItemOnMap* > _items;
	std::vector < Furniture* > _furnitures;
	std::vector < Wall* > _walls;
    Door* _door;

    Floors* floors;
    sf::RectangleShape rect;
    sf::Texture tex;
    sf::Sprite sprite;

    int x1, x2, y1, y2; // corners of building

	Building(string name, float x, float y) : GameObject(name, x, y) {

        type = gameObjectType::Building;

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
        std::getline(file, line);   // door
        _door = new Door(getPrefab("doors/door_0"), position.x, position.y);
        
        // SIZE
        std::getline(file, line);
        std::istringstream lineStream(line);
        lineStream >> objectType;
        lineStream >> size.x >> size.y;
        //cout << size.x << " " << size.y << "\n";

        collider = new Collider(size.x * 16, size.y * 16, size.y * 16, true);
         
        rect = sf::RectangleShape(sf::Vector2f(size.x*16, size.y*16));
        rect.setFillColor(sf::Color(128, 48, 48, 128));
        rect.setOrigin(size.x/2*16, size.y*16);
        rect.setPosition(position);

        // TO-DO
        sprite = sf::Sprite();
        tex.loadFromFile("assets/buildings/demo house.png");
        sprite.setTexture(tex);
        sprite.setOrigin(tex.getSize().x/2, tex.getSize().y);
        sprite.setPosition(position);

        std::getline(file, line);
        std::getline(file, line);

        // LOAD FLOORS - TO-DO
        //cout << position.x/16 << ", " << position.y << "\n";
        //cout << size.x << ", " << size.y << "\n";

        floors = new Floors(position.x/16-size.x/2, position.y/16-size.y, size.x, size.y);
        int value;
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                file >> value;
                //cout << value << " ";
                floors->edit(x, y, value);;
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
                y = y - (size.y * 16) + position.y;

                ItemOnMap* item = new ItemOnMap(getItem(objectName), x, y);
                _items.push_back(item);
                //cout << "Item: " << objectName << "\n";

            }

            if (objectType == "Furniture") {
                string name;
                int x, y, id;

                getline(lineStream, objectName, '"'); // Pomijamy pierwszy znak cudzysłowu
                getline(lineStream, objectName, '"'); // Wczytaj nazwę do kolejnego cudzysłowu
                lineStream >> x;
                lineStream >> y;
                lineStream >> id;

                x = x - (size.x * 16/2) + position.x;
                y = y - (size.y * 16) + position.y;

                Furniture* furniture = new Furniture(getPrefab(objectName), x, y);
                furniture->inventory = getInventory(id);
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
                y = y - (size.y * 16) + position.y;

                Wall* wall = new Wall(getPrefab(objectName), x, y);
                _walls.push_back(wall);
                //cout << "Wall: " << objectName << "\n";
            }

        }

        file.close();

        collider->shape->setPosition(position.x, position.y - size.y / 2 * 16);

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

        gameObjects.push_back(_door);
        doors.push_back(_door);
	}

    void calculateCorners() {
        x1 = position.x - size.x / 2 * 16;
        x2 = position.x + size.x / 2 * 16;
        y1 = position.y - size.y * 16;
        y2 = position.y;
    }

    void deleteBuilding() {
        toDelete = true;

        for (auto& item : _items)
            item->toDelete = true;

        for (auto& furniture : _furnitures)
            furniture->toDelete = true;

        for (auto& wall : _walls)
            wall->toDelete = true;

        _door->toDelete = true;
    }

    virtual void mouseOvering() {

        if (worldMousePosition.x > x1 && worldMousePosition.x < x2 && worldMousePosition.y > y1 && worldMousePosition.y < y2)
            mouseIsOver = true;
        else
            mouseIsOver = false;
    }

    bool playerInside() {

        int x3, y3, rx3, ry3;
        x3 = player->position.x;
        y3 = player->position.y;
        rx3 = (player->collider->width / 2.0f);
        ry3 = (player->collider->length) / 2.0f;

        if (intersectionRectangleWithElipse((x1 + x2) / 2, (y1 + y2) / 2, x2 - x1, y2 - y1, x3, y3, rx3, ry3))
            return true;
        else
            return false;
    }

    virtual void update(float dt) {
        calculateCorners();
        mouseOvering();
        sprite.setPosition(position);
    }

    virtual void updateStatistic(float dt) {
        
    }

    virtual void draw() {

        if(player!=nullptr && !playerInside()) {
            window->draw(sprite);
        }

        if (player == nullptr) {
            if (GameObject::mouseIsOver == false) {
                window->draw(sprite);
            }
        }
  
    }

    virtual void drawStatistic() {

    }
};

std::vector < Building* > buildings;

#endif