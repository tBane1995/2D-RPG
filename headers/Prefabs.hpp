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
    // name, width, height
    prefabs.push_back(new Path("paths/stonepath1", 64, 32));
    prefabs.push_back(new Path("paths/stonepath2", 64, 32));

    // ITEMS
    for (auto& i : items) {
        prefabs.push_back(new ItemOnMap(i, 0, 0));
    }

    // CHARACTERS
    // name, bodySet

    Character* character = nullptr;

    character = new Character("characters/jack", "sets/body/hero");
    character->dialogue = getDialogue(1);
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->rightHand = getItem("items/sword");
    character->leftHand = getItem("items/shield");
    character->loadTextures();
    prefabs.push_back(character);

    character = new Character("characters/john", "sets/body/hero");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->loadTextures();
    prefabs.push_back(character);

    character = new Character("characters/peter", "sets/body/hero");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->loadTextures();
    prefabs.push_back(character);

    character = new Character("characters/pit", "sets/body/hero");
    character->dialogue = getDialogue(5);
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->loadTextures();
    prefabs.push_back(character);


    // MONSTERS
    // name, width, height

    Monster* wilczur = new Monster("monsters/wilczur", 70, 35);
    wilczur->HP = 70;
    wilczur->HP_max = 70;
    wilczur->MP = 10;
    wilczur->MP_max = 10;
    wilczur->STRENGTH = 7;
    wilczur->DEXTERITY = 5;
    wilczur->INTELLIGENCE = 2;
    prefabs.push_back(wilczur);

    Monster* goblin = new Monster("monsters/goblin", 32, 16);
    goblin->HP = 50;
    goblin->HP_max = 50;
    goblin->MP = 10;
    goblin->MP_max = 10;
    goblin->STRENGTH = 4;
    goblin->DEXTERITY = 5;
    goblin->INTELLIGENCE = 3;
    prefabs.push_back(goblin);

    Monster* dziobak = new Monster("monsters/dziobak", 72, 36);
    dziobak->HP = 50;
    dziobak->HP_max = 50;
    dziobak->MP = 10;
    dziobak->MP_max = 10;
    dziobak->STRENGTH = 3;
    dziobak->DEXTERITY = 3;
    dziobak->INTELLIGENCE = 1;
    prefabs.push_back(dziobak);

    Monster* niedzwiedz = new Monster("monsters/niedzwiedz", 70, 35);
    niedzwiedz->HP = 200;
    niedzwiedz->HP_max = 150;
    niedzwiedz->MP = 10;
    niedzwiedz->MP_max = 10;
    niedzwiedz->STRENGTH = 30;
    niedzwiedz->DEXTERITY = 15;
    niedzwiedz->INTELLIGENCE = 2;
    prefabs.push_back(niedzwiedz);

    Monster* kolcorozec = new Monster("monsters/kolcorozec", 70, 35);
    kolcorozec->HP = 150;
    kolcorozec->HP_max = 150;
    kolcorozec->MP = 10;
    kolcorozec->MP_max = 10;
    kolcorozec->STRENGTH = 30;
    kolcorozec->DEXTERITY = 15;
    kolcorozec->INTELLIGENCE = 2;
    prefabs.push_back(kolcorozec);

    Monster* szpon = new Monster("monsters/szpon", 66, 32);
    szpon->HP = 100;
    szpon->HP_max = 100;
    szpon->MP = 10;
    szpon->MP_max = 10;
    szpon->STRENGTH = 20;
    szpon->DEXTERITY = 15;
    szpon->INTELLIGENCE = 2;
    prefabs.push_back(szpon);

    Monster* troll = new Monster("monsters/troll", 90, 60);
    troll->HP = 400;
    troll->HP_max = 400;
    troll->MP = 10;
    troll->MP_max = 10;
    troll->STRENGTH = 20;
    troll->DEXTERITY = 5;
    troll->INTELLIGENCE = 2;
    prefabs.push_back(troll);

    Monster* bies = new Monster("monsters/bies", 90, 60);
    bies->HP = 400;
    bies->HP_max = 400;
    bies->MP = 10;
    bies->MP_max = 10;
    bies->STRENGTH = 20;
    bies->DEXTERITY = 5;
    bies->INTELLIGENCE = 2;
    prefabs.push_back(bies);
}



#endif
