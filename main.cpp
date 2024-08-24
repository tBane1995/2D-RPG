#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>

#include <algorithm>
#include <numeric>
#include <functional>

#include <string>
#include <windows.h>

#include "headers/Window.hpp"
#include "headers/Time.hpp"
#include "headers/Camera.hpp"
#include "headers/Mouse.hpp"

#include "headers/Fonts.hpp"
#include "headers/Textures.hpp"

#include "headers/Collisions.hpp"
#include "headers/Pathfinding.hpp"

#include "headers/GameObjects.hpp"
#include "headers/TerrainAndFloors.hpp"     // Terrain and Floors

#include "headers/GameStates.hpp"           

#include "headers/HitTexts.hpp"             // Hit texts
#include "headers/Items.hpp"                // manage of items, itemsOnMap, Inventory and InventoryOnMap
#include "headers/UnitStates.hpp"           // states for Units
#include "headers/Player.hpp"               // manage of Player
#include "headers/Units.hpp"                // manage of Units
#include "headers/Monsters.hpp"             // manage of Monster
#include "headers/Natures.hpp"              // manage of Natures
#include "headers/Furnitures.hpp"           // manage of Furnitures
#include "headers/Paths.hpp"                // manage of Paths
#include "headers/Walls.hpp"                // manage of Walls
#include "headers/Dialogues.hpp"            
#include "headers/Character.hpp"            // manage of Characters
#include "headers/Prefabs.hpp"              // all prefabs: itemsOnMap, InventoryOnMap, Characters, Monsters, Natures, Furnitures, Walls etc .. 
#include "headers/BuildingsManager.hpp"            // manage of Buildings
#include "headers/GameObjectsManager.hpp"   // manage of GameObjects - update/sort/render/
#include "headers/Maps.hpp"
#include "headers/Quests.hpp"

#include "headers/GUI.hpp"
#include "headers/PrefabToPaint.hpp"
#include "headers/Palette.hpp"

#include "headers/ControlsPanel.hpp"
#include "headers/InventoryPanel.hpp"
#include "headers/TradePanel.hpp"
#include "headers/JournalPanel.hpp"
#include "headers/StatsPanel.hpp"

#include "Game.hpp"
#include "MapEditor.hpp"
#include "BuildingEditor.hpp"



void createSetsFromIdle(string idlePath) {

    cout << "creating set from idles for monster: " << idlePath;

    sf::Image idle_0;
    sf::Image idle_1;

    idle_0.loadFromFile(idlePath + "0.png");
    idle_1.loadFromFile(idlePath + "1.png");

    // IDLE
    idle_0.saveToFile(idlePath + "idleBottom0.png");
    idle_1.saveToFile(idlePath + "idleBottom1.png");
    idle_0.saveToFile(idlePath + "idleBottom2.png");
    idle_1.saveToFile(idlePath + "idleBottom3.png");

    idle_0.saveToFile(idlePath + "idleTop0.png");
    idle_1.saveToFile(idlePath + "idleTop1.png");
    idle_0.saveToFile(idlePath + "idleTop2.png");
    idle_1.saveToFile(idlePath + "idleTop3.png");

    idle_0.saveToFile(idlePath + "idleLeft0.png");
    idle_1.saveToFile(idlePath + "idleLeft1.png");
    idle_0.saveToFile(idlePath + "idleLeft2.png");
    idle_1.saveToFile(idlePath + "idleLeft3.png");

    idle_0.saveToFile(idlePath + "idleRight0.png");
    idle_1.saveToFile(idlePath + "idleRight1.png");
    idle_0.saveToFile(idlePath + "idleRight2.png");
    idle_1.saveToFile(idlePath + "idleRight3.png");

    // RUN
    idle_0.saveToFile(idlePath + "runBottom0.png");
    idle_1.saveToFile(idlePath + "runBottom1.png");
    idle_0.saveToFile(idlePath + "runBottom2.png");
    idle_1.saveToFile(idlePath + "runBottom3.png");

    idle_0.saveToFile(idlePath + "runTop0.png");
    idle_1.saveToFile(idlePath + "runTop1.png");
    idle_0.saveToFile(idlePath + "runTop2.png");
    idle_1.saveToFile(idlePath + "runTop3.png");

    idle_0.saveToFile(idlePath + "runLeft0.png");
    idle_1.saveToFile(idlePath + "runLeft1.png");
    idle_0.saveToFile(idlePath + "runLeft2.png");
    idle_1.saveToFile(idlePath + "runLeft3.png");

    idle_0.saveToFile(idlePath + "runRight0.png");
    idle_1.saveToFile(idlePath + "runRight1.png");
    idle_0.saveToFile(idlePath + "runRight2.png");
    idle_1.saveToFile(idlePath + "runRight3.png");

    // ATTACK
    idle_0.saveToFile(idlePath + "attackBottom0.png");
    idle_1.saveToFile(idlePath + "attackBottom1.png");
    idle_0.saveToFile(idlePath + "attackBottom2.png");
    idle_1.saveToFile(idlePath + "attackBottom3.png");

    idle_0.saveToFile(idlePath + "attackTop0.png");
    idle_1.saveToFile(idlePath + "attackTop1.png");
    idle_0.saveToFile(idlePath + "attackTop2.png");
    idle_1.saveToFile(idlePath + "attackTop3.png");

    idle_0.saveToFile(idlePath + "attackLeft0.png");
    idle_1.saveToFile(idlePath + "attackLeft1.png");
    idle_0.saveToFile(idlePath + "attackLeft2.png");
    idle_1.saveToFile(idlePath + "attackLeft3.png");

    idle_0.saveToFile(idlePath + "attackRight0.png");
    idle_1.saveToFile(idlePath + "attackRight1.png");
    idle_0.saveToFile(idlePath + "attackRight2.png");
    idle_1.saveToFile(idlePath + "attackRight3.png");

}

void createSetsFromRuns(string path) {

    cout << "creating set from runs for monster: " << path;

    sf::Image run_0;
    sf::Image run_1;
    sf::Image run_2;
    sf::Image run_3;

    run_0.loadFromFile(path + "0.png");
    run_1.loadFromFile(path + "1.png");
    run_2.loadFromFile(path + "2.png");
    run_3.loadFromFile(path + "3.png");

    // IDLE
    run_0.saveToFile(path + "idleBottom0.png");
    run_1.saveToFile(path + "idleBottom1.png");
    run_2.saveToFile(path + "idleBottom2.png");
    run_3.saveToFile(path + "idleBottom3.png");

    run_0.saveToFile(path + "idleTop0.png");
    run_1.saveToFile(path + "idleTop1.png");
    run_2.saveToFile(path + "idleTop2.png");
    run_3.saveToFile(path + "idleTop3.png");

    run_0.saveToFile(path + "idleLeft0.png");
    run_1.saveToFile(path + "idleLeft1.png");
    run_2.saveToFile(path + "idleLeft2.png");
    run_3.saveToFile(path + "idleLeft3.png");

    run_0.saveToFile(path + "idleRight0.png");
    run_1.saveToFile(path + "idleRight1.png");
    run_2.saveToFile(path + "idleRight2.png");
    run_3.saveToFile(path + "idleRight3.png");

    // RUN
    run_0.saveToFile(path + "runBottom0.png");
    run_1.saveToFile(path + "runBottom1.png");
    run_2.saveToFile(path + "runBottom2.png");
    run_3.saveToFile(path + "runBottom3.png");

    run_0.saveToFile(path + "runTop0.png");
    run_1.saveToFile(path + "runTop1.png");
    run_2.saveToFile(path + "runTop2.png");
    run_3.saveToFile(path + "runTop3.png");

    run_0.saveToFile(path + "runLeft0.png");
    run_1.saveToFile(path + "runLeft1.png");
    run_2.saveToFile(path + "runLeft2.png");
    run_3.saveToFile(path + "runLeft3.png");

    run_0.saveToFile(path + "runRight0.png");
    run_1.saveToFile(path + "runRight1.png");
    run_2.saveToFile(path + "runRight2.png");
    run_3.saveToFile(path + "runRight3.png");

    // ATTACK
    run_0.saveToFile(path + "attackBottom0.png");
    run_1.saveToFile(path + "attackBottom1.png");
    run_2.saveToFile(path + "attackBottom2.png");
    run_3.saveToFile(path + "attackBottom3.png");

    run_0.saveToFile(path + "attackTop0.png");
    run_1.saveToFile(path + "attackTop1.png");
    run_2.saveToFile(path + "attackTop2.png");
    run_3.saveToFile(path + "attackTop3.png");

    run_0.saveToFile(path + "attackLeft0.png");
    run_1.saveToFile(path + "attackLeft1.png");
    run_2.saveToFile(path + "attackLeft2.png");
    run_3.saveToFile(path + "attackLeft3.png");

    run_0.saveToFile(path + "attackRight0.png");
    run_1.saveToFile(path + "attackRight1.png");
    run_2.saveToFile(path + "attackRight2.png");
    run_3.saveToFile(path + "attackRight3.png");

}


void editWhitePixelsToTransparent(string monster_path) {

    cout << "editing white pixels to transparent: " << monster_path << "\n";

    sf::Color whiteColor = sf::Color(255, 255, 255);
    //sf::Color whiteColor = sf::Color(136, 68, 0);
    sf::Color transparentColor = sf::Color(0, 0, 0, 0);
    //sf::Color transparentColor = sf::Color(255, 127, 39);

    std::vector < std::string > png_files;

    for (const auto& entry : filesystem::directory_iterator(monster_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            png_files.push_back(entry.path().string());
        }
    }

    for (auto& png : png_files) {
        sf::Image img;
        img.loadFromFile(png.c_str());

        for (int y = 0; y < img.getSize().y; y++)
            for (int x = 0; x < img.getSize().x; x++) {
                if (img.getPixel(x, y) == whiteColor) {
                    img.setPixel(x, y, transparentColor);
                }

            }

        img.saveToFile(png.c_str());
    }

}

void test()
{
    printf("     ");
    for (int a = 1; a < 20; ++a)
        printf("%4d ", a);

    printf("\ratk\\def\n");

    for (int dex_atk = 1; dex_atk < 30; ++dex_atk)
    {
        printf("%4d", dex_atk);
        for (int dex_def = 1; dex_def < 30; ++dex_def)
        {
            int hit = 0, tests = 1000;

            //srand(0);
            for (int i = 0; i < tests; ++i)
            {
                if (rand() % (dex_atk+10) - rand() % (dex_def+5) > 0)
                    ++hit;

            }

            printf(" %3.0f%%", 100.f * hit / tests);
        }
        printf("\n");
    }
}

void createTab(int width, int height) {
    

    //int tab[width][height];
    std::vector<std::vector<int>> tab(width, std::vector<int>(height));
     
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            std::cout << tab[i][j] << " ";
}

int main()
{
    // TOOLS - be careful with that
    //createSetsFromIdle("assets/monsters/jaszczur/");             // TO-DO
    //createSetsFromRuns("assets/monsters/jaszczur/");               // TO-DO
    //editWhitePixelsToTransparent("assets/monsters/jaszczur/");   // TO-DO
    test();

    // LOADS
	loadFonts();
	loadTextures();		// TO-DO "FROM FILE"
	loadItems();		// TO-DO "FROM FILE"
    loadDialogues();
    loadQuests();
	loadPrefabs();		// TO-DO "FROM FILE"
	

	window->setKeyRepeatEnabled(false);	// TO-DO commentary
	
    // PROGRAMS
	//game();
	//mapEditor();
    buildingEditor();
    
}