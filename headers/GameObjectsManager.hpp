#ifndef GameObjectsManager_hpp
#define GameObjectsManager_hpp

std::vector < GameObject* > selectedGameObjects;

void selectGameObjects(int rect_x, int rect_y, int rect_w, int rect_h) {

    selectedGameObjects.clear();

    for (auto& go : gameObjects) {

        if (intersectionRectangleWithElipse(rect_x, rect_y, rect_w, rect_h, go->position.x, go->position.y, go->collider->width / 2, go->collider->length / 2)) {
            go->mouseIsOver = true;
            selectedGameObjects.push_back(go);
        }
            
    }
}

void clearAllMainListsOfGameObjects() {

    gameObjects.clear();

    natures.clear();
    itemsOnMap.clear();
    paths.clear();
    furnitures.clear();
    walls.clear();
    doors.clear();
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
    std::vector < Door* > new_doors;
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
    new_doors.clear();
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

            if (go->type == gameObjectType::Door)
                new_doors.push_back(dynamic_cast<Door*>(go));

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
    doors = new_doors;

    monsters = new_monsters;

    buildings = new_buildings;

    characters = new_characters;
    inventoriesOnMap = new_inventoriesOnMap;

}

bool visiblings(GameObject* object) {
    if (object != nullptr) {

        if (object->collider->isRectangular == false) {
            if (intersectionRectangleWithElipse(cam->position.x, cam->position.y, screenWidth * 1.5f, screenHeight * 1.5f, object->position.x, object->position.y, object->collider->width / 2.0f, object->collider->length / 2.0f)) {
                return true;
            }
        }

        if (object->collider->isRectangular == true) {
            if (intersectionTwoRectangles(cam->position.x, cam->position.y, screenWidth * 1.5f, screenHeight * 1.5f, object->position.x, object->position.y, object->collider->width, object->collider->length))
                return true;
        }
    }

    //cout << "visiblings with nullptr\n";
    return false;
}

void updateGameObjects() {

	for (auto& go : gameObjects) {
        if (visiblings(go)) {
            go->update(dt);
            go->mouseOvering();
        }
	}
}

void sortGameObjects() {

    std::sort(gameObjects.begin(), gameObjects.end(), [](const auto& a, const auto& b) { return a->position.y < b->position.y; });
}

void drawGameObjects() {

	for (auto& p : paths) {
		if (visiblings(p))
			p->draw();
	}

	for (auto& go : gameObjects)
		if (go->type != gameObjectType::Path)
			if (go->type == gameObjectType::Building || visiblings(go))
				if(visiblings(go))
                    go->draw();

}

#endif