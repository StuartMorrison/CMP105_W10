#pragma once
#include "Framework/TileMap.h"
#include "Framework/Collision.h"
class MapSetup :
	public TileMap
{
public:

	TileMap tileMap;

	MapSetup();
	void MapRender(sf::RenderWindow* window);
	void Collision(GameObject &player);
	~MapSetup();
};

