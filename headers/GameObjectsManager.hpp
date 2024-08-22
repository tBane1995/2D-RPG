#ifndef GameObjectsManager_hpp
#define GameObjectsManager_hpp

void clearAllMainListsOfGameObjects() {

    gameObjects.clear();

    natures.clear();
    itemsOnMap.clear();
    paths.clear();
    furnitures.clear();
    walls.clear();
    monsters.clear();
    characters.clear();
    inventoriesOnMap.clear();

    buildings.clear();


}

void deleteGameObjectsFromMainLists() {

    std::vector < GameObject* > new_gameObjects;
    std::vector < Nature* > new_natures;
    std::vector < ItemOnMap* > new_itemsOnMap;
    std::vector < Path* > new_paths;
    std::vector < Furniture* > new_furnitures;
    std::vector < Wall* > new_walls;
    std::vector < Monster* > new_monsters;
    std::vector < Building* > new_buildings;
    std::vector < Character* > new_characters;
    std::vector < InventoryOnMap* > new_inventoriesOnMap;


    new_gameObjects.clear();
    new_natures.clear();
    new_itemsOnMap.clear();
    new_paths.clear();
    new_furnitures.clear();
    new_walls.clear();
    new_monsters.clear();
    new_buildings.clear();
    new_characters.clear();
    new_inventoriesOnMap.clear();


    for (auto& go : gameObjects) {

        if (go->toDelete == false) {

            new_gameObjects.push_back(go);

            if (go->type == gameObjectType::Nature)
                new_natures.push_back(dynamic_cast<Nature*>(go));

            if (go->type == gameObjectType::ItemOnMap)
                new_itemsOnMap.push_back(dynamic_cast<ItemOnMap*>(go));

            if (go->type == gameObjectType::Path)
                new_paths.push_back(dynamic_cast<Path*>(go));

            if (go->type == gameObjectType::Furniture)
                new_furnitures.push_back(dynamic_cast<Furniture*>(go));

            if (go->type == gameObjectType::Wall)
                new_walls.push_back(dynamic_cast<Wall*>(go));

            if (go->type == gameObjectType::Monster)
                new_monsters.push_back(dynamic_cast<Monster*>(go));

            if (go->type == gameObjectType::Building)
                new_buildings.push_back(dynamic_cast<Building*>(go));

            if (go->type == gameObjectType::Character)
                new_characters.push_back(dynamic_cast<Character*>(go));

            if (go->type == gameObjectType::InventoryOnMap)
                new_inventoriesOnMap.push_back(dynamic_cast<InventoryOnMap*>(go));


        }
    }

    gameObjects = new_gameObjects;
    natures = new_natures;
    itemsOnMap = new_itemsOnMap;
    paths = new_paths;
    furnitures = new_furnitures;
    walls = new_walls;
    monsters = new_monsters;

    buildings = new_buildings;

    characters = new_characters;
    inventoriesOnMap = new_inventoriesOnMap;

}

bool visiblings(GameObject* object) {
    if (object != nullptr) {

        if (object->collider->isRectangular == false) {
            if (intersectionRectangleWithElipse(cam->position.x, cam->position.y, screenWidth * 2.0f, screenHeight * 2.0f, object->position.x, object->position.y, object->collider->width / 2.0f, object->collider->length / 2.0f)) {
                return true;
            }
        }

        if (object->collider->isRectangular == true) {
            if (intersectionTwoRectangles(cam->position.x, cam->position.y, screenWidth * 2.0f, screenHeight * 2.0f, object->position.x, object->position.y, object->collider->width, object->collider->length))
                return true;
        }
    }

    //cout << "visiblings with nullptr\n";
    return false;
}

void sortGameObjects() {

	std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });
}

void updateGameObjects() {

	for (auto& go : gameObjects) {
		if (visiblings(go))     // only visible GameObjects are updating
			go->update(dt);
	}
}

void renderGameObjects() {

	for (auto& p : paths) {
		if (visiblings(p))
			p->draw(window);
	}

	for (auto& go : gameObjects)
		if (go->type != gameObjectType::Path)
			if (visiblings(go))
				go->draw(window);

}

#endif