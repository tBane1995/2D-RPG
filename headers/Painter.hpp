#ifndef Painter_hpp
#define Painter_hpp

void painterUpdate() {

    for (auto& prefab : prefabsToPaint) {
        delete prefab;
    }

    prefabsToPaint.clear();

    if (prefabsToPaint.empty())
        cout << "empty brush\n";

    if (GUIwasHover || GUIwasClicked) {
        return;
    }
    else if (tool == toolType::Cursor && selection_state == true) {
        mouseSelection();
    }
    else if (prefabToPaint != nullptr) {

        if (prefabToPaint->type == gameObjectType::Terrain || prefabToPaint->type == gameObjectType::Floor) {

            // RECTANGLE    ///////////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::Rectangle) {
                if (selection_state == true) {
                    generateRectangle();
                }
            }

            // ELIPSE   ///////////////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::Elipse) {
                if (selection_state == true) {
                    generateElipse();
                }
            }

            //  BRUSH   ////////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::Brush) {
                generateBrush();
            }

            //  RECT BRUSH  ////////////////////////////////////////////////////////////////////////////////////////
            if (tool == toolType::RectBrush) {
                generateRectBrush();
            }

        }
        else {
            // prefab is a GameObject

            int x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
            int y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

            if (prefabToPaint->type == gameObjectType::Nature) {
                Nature* nature = new Nature(prefabToPaint, x, y);
                prefabsToPaint.push_back(nature);
            }

            if (prefabToPaint->type == gameObjectType::Monster) {
                Monster* monster = new Monster(prefabToPaint, x, y);
                prefabsToPaint.push_back(monster);
            }

            if (prefabToPaint->type == gameObjectType::ItemOnMap) {
                ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
                prefabsToPaint.push_back(item);
            }

            if (prefabToPaint->type == gameObjectType::Path) {
                Path* path = new Path(prefabToPaint, x, y);
                prefabsToPaint.push_back(path);
            }

            if (prefabToPaint->type == gameObjectType::Furniture) {
                Furniture* furniture = new Furniture(prefabToPaint, x, y);
                prefabsToPaint.push_back(furniture);
            }

            if (prefabToPaint->type == gameObjectType::Wall) {
                Wall* wall = new Wall(prefabToPaint, x, y);
                prefabsToPaint.push_back(wall);
            }

            // Aktualizujemy prefabrykaty
            for (auto& prefab : prefabsToPaint) {

                if (prefab->type == gameObjectType::Unit || prefab->type == gameObjectType::Monster || prefab->type == gameObjectType::Character) {
                    dynamic_cast<Unit*>(prefab)->idling(dt);
                }
                else {
                    prefab->update(dt);
                    prefab->mouseIsOver = false;
                }
            }
        }


    }
}

void painterDraw() {

    if (tool == toolType::Cursor && selection_state == true) {
        window->draw(selectArea);

    } else {
        for (auto& p : prefabsToPaint) {
            p->draw();
        }
    }
    

}

void addPrefabToLists() {

    int x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
    int y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
    // cout << "cursor at position: " << xx << " " << yy << "\n"

    if (prefabToPaint->type == gameObjectType::Nature) {

        Nature* nature = new Nature(prefabToPaint, x, y);
        gameObjects.push_back(nature);
        natures.push_back(nature);
    }

    if (prefabToPaint->type == gameObjectType::Monster) {

        Monster* monster = new Monster(prefabToPaint, x, y);
        gameObjects.push_back(monster);
        monsters.push_back(monster);
    }

    if (prefabToPaint->type == gameObjectType::ItemOnMap) {

        ItemOnMap* item = new ItemOnMap(prefabToPaint, x, y);
        gameObjects.push_back(item);
        itemsOnMap.push_back(item);
    }

    if (prefabToPaint->type == gameObjectType::Path) {

        Path* path = new Path(prefabToPaint, x, y);
        gameObjects.push_back(path);
        paths.push_back(path);
    }

    if (prefabToPaint->type == gameObjectType::Furniture) {

        Furniture* furniture = new Furniture(prefabToPaint, x, y);
        gameObjects.push_back(furniture);
        furnitures.push_back(furniture);
    }

    if (prefabToPaint->type == gameObjectType::Wall) {
        Wall* wall = new Wall(prefabToPaint, x, y);
        gameObjects.push_back(wall);
        walls.push_back(wall);
    }
}


void addPrefabsToMapAndLists() {

    Map* map = world->getMap(worldMousePosition);

    if (map == nullptr)
        return;

    for (auto& prefab : prefabsToPaint) {

        int x = prefab->position.x;
        int y = prefab->position.y;

        if (prefab->type == gameObjectType::Nature) {

            Nature* nature = new Nature(prefab, x, y);
            gameObjects.push_back(nature);
            natures.push_back(nature);
            map->_natures.push_back(nature);
        }

        if (prefab->type == gameObjectType::Monster) {

            Monster* monster = new Monster(prefab, x, y);
            gameObjects.push_back(monster);
            monsters.push_back(monster);
            map->_monsters.push_back(monster);
        }

        if (prefab->type == gameObjectType::ItemOnMap) {

            ItemOnMap* item = new ItemOnMap(prefab, x, y);
            gameObjects.push_back(item);
            itemsOnMap.push_back(item);
            map->_itemsOnMap.push_back(item);
        }

        if (prefab->type == gameObjectType::Path) {

            Path* path = new Path(prefab, x, y);
            gameObjects.push_back(path);
            paths.push_back(path);
            map->_paths.push_back(path);
        }

        if (prefab->type == gameObjectType::Furniture) {

            Furniture* furniture = new Furniture(prefab, x, y);
            gameObjects.push_back(furniture);
            furnitures.push_back(furniture);
            map->_furnitures.push_back(furniture);
        }

        if (prefab->type == gameObjectType::Wall) {
            Wall* wall = new Wall(prefab, x, y);
            gameObjects.push_back(wall);
            walls.push_back(wall);
            map->_walls.push_back(wall);
        }

    }
}

#endif // ! Painter_hpp
