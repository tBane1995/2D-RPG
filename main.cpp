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
#include "headers/Tiles.hpp"	// gameObject::Terrain and gameObject::Floor


#include "headers/GameStates.hpp"

#include "headers/Paths.hpp"
#include "headers/Items.hpp"
#include "headers/States.hpp"
#include "headers/Player.hpp"
#include "headers/Units.hpp"
#include "headers/Monsters.hpp"
#include "headers/Natures.hpp"
#include "headers/InventoryPanel.hpp"
#include "headers/TradePanel.hpp"
#include "headers/Furnitures.hpp"
#include "headers/Walls.hpp"
#include "headers/Dialogues.hpp"
#include "headers/Character.hpp"
#include "headers/Prefabs.hpp"
#include "headers/Buildings.hpp"
#include "headers/loadGameObjects.hpp"
#include "headers/Maps.hpp"
#include "headers/MapEditorPalette.hpp"
#include "headers/Quests.hpp"

#include "Game.hpp"
#include "MapEditor.hpp"

void editPixels() {

    sf::Image i;
    i.loadFromFile("assets/sets/items/wool hat/attackBottom0.png");

    //sf::Color color = sf::Color(127,127,127);
    sf::Color color = sf::Color(255,255,255);
    sf::Color newColor = i.getPixel(0, 0);
    //sf::Color newColor = sf::Color(150, 94, 63);

    string folder_path = "assets/sets/items/iron club";

    std::vector < std::string > png_files;

    for (const auto& entry : filesystem::directory_iterator(folder_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
            png_files.push_back(entry.path().string());
        }
    }

    for (auto& png : png_files) {
        sf::Image img;
        img.loadFromFile(png.c_str());

        for (int y = 0; y < img.getSize().y; y++)
            for (int x = 0; x < img.getSize().x; x++) {
                if (img.getPixel(x, y) == color) {
                    img.setPixel(x, y, newColor);
                }

            }

        img.saveToFile(png.c_str());
    }

}

int main()
{
    editPixels();   // TO-DO

	loadFonts();
	loadTextures();		// TO-DO "FROM FILE"
	loadItems();		// TO-DO "FROM FILE"
	loadPrefabs();		// TO-DO "FROM FILE"
	

	window->setKeyRepeatEnabled(false);	// TO-DO commentary
	
    
	game();
	mapEditor();
	    
	
}