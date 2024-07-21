#ifndef Prefabs_hpp
#define Prefabs_hpp

std::vector < GameObject* > prefabs;

GameObject* getPrefab(string name) {
    for (auto& go : prefabs) {
        if (go->name == name)
            return go;
    }

    std::cout << "error - get Prefab - Prefab: \"" << name << "\" not exists\n";
    return nullptr;
}

void loadPrefabs() {

    prefabs.clear();
 
    // TREES
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/tree1", 36, 18));
    prefabs.push_back(new Nature("natures/tree2", 44, 22));
    prefabs.push_back(new Nature("natures/bush1", 110, 55));

    // ROCKS
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/rocks1", 90, 45));
    prefabs.push_back(new Nature("natures/rocks2", 90, 45));
    prefabs.push_back(new Nature("natures/rocks3", 90, 45));

    // MONSTERS
    // name, radius, width, height
    prefabs.push_back(new Monster("monsters/wilczur", 70, 35));
    prefabs.push_back(new Monster("monsters/goblin", 32, 16));
    prefabs.push_back(new Monster("monsters/dziobak", 72, 36));

    // FURNITURES
    prefabs.push_back(new Furniture("furnitures/table1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/bench1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/chest1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/wardrobe1", 64, 32));
    prefabs.push_back(new Furniture("furnitures/bookshelf1", 64, 32));
    prefabs.push_back(new Furniture("furnitures/furnace1", 60, 26));
    prefabs.push_back(new Furniture("furnitures/bed1", 64, 32));
    prefabs.push_back(new Furniture("furnitures/chair1", 16, 16));
    prefabs.push_back(new Furniture("furnitures/barrel1", 16, 16));
    prefabs.push_back(new Furniture("furnitures/lectern1", 24, 16));

    // WALLS
    prefabs.push_back(new Wall("walls/wooden_wall_bottom", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_0", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_1", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_2", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_3", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_4", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_5", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_6", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_7", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_8", 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_top_9", 32, 32));

    prefabs.push_back(new Wall("walls/stone_wall_bottom", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_0", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_1", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_2", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_3", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_4", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_5", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_6", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_7", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_8", 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_top_9", 32, 32));

    prefabs.push_back(new Wall("walls/mud_wall_bottom", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_0", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_1", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_2", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_3", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_4", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_5", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_6", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_7", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_8", 32, 32));
    prefabs.push_back(new Wall("walls/mud_wall_top_9", 32, 32));
    

    // PATHS
    // name, radius, width, height
    prefabs.push_back(new Path("paths/stonepath1", 64, 32));
    prefabs.push_back(new Path("paths/stonepath2", 64, 32));

    // CHARACTERS
    // name, radius, width, height
    prefabs.push_back(new Character("characters/jack"));
    prefabs.push_back(new Character("characters/john"));
    prefabs.push_back(new Character("characters/peter"));
    prefabs.push_back(new Character("characters/pit"));

    for (auto& i : items) {
        prefabs.push_back(new ItemOnMap(i, 0, 0));
    }

}



#endif
