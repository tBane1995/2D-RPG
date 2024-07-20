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

#include "headers/Fonts.hpp"
#include "headers/Textures.hpp"

#include "headers/Collisions.hpp"
#include "headers/Pathfinding.hpp"

#include "headers/GameObjects.hpp"
#include "headers/Tiles.hpp"	// gameObject::Terrain and gameObject::Floor

#include "headers/Paths.hpp"
#include "headers/Items.hpp"
#include "headers/States.hpp"
#include "headers/Player.hpp"
#include "headers/Units.hpp"
#include "headers/Monsters.hpp"
#include "headers/Natures.hpp"
#include "headers/Furnitures.hpp"
#include "headers/Walls.hpp"
#include "headers/Dialogues.hpp"
#include "headers/Character.hpp"
#include "headers/PlayerInventory.hpp"
#include "headers/Prefabs.hpp"
#include "headers/Buildings.hpp"
#include "headers/loadGameObjects.hpp"
#include "headers/Maps.hpp"
#include "headers/MapEditorPalette.hpp"

#include "Game.hpp"
#include "MapEditor.hpp"


int main()
{
	loadFonts();
	loadTextures();		// TO-DO "FROM FILE"
	loadItems();		// TO-DO "FROM FILE"
	loadPrefabs();		// TO-DO "FROM FILE"
	

	window->setKeyRepeatEnabled(false);	// TO-DO commentary
	
	game();
	mapEditor();
	
	
}