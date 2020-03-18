#include "MapSetup.h"

MapSetup::MapSetup()
{
	tileMap.loadTexture("gfx/marioTiles.png");

	GameObject tile;
	std::vector<GameObject> tiles;

	for (int i = 0; i < 10; i++)
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}

	tiles[0].setCollider(false);
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16));
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tiles[4].setCollider(false);
	tiles[4].setTextureRect(sf::IntRect(0, 34, 16, 16));
	tiles[5].setCollider(false);
	tiles[5].setTextureRect(sf::IntRect(17, 34, 16, 16));
	tiles[6].setCollider(false);
	tiles[6].setTextureRect(sf::IntRect(34, 34, 16, 16));
	tiles[7].setCollider(false);
	tiles[7].setTextureRect(sf::IntRect(0, 17, 16, 16));
	tiles[8].setCollider(false);
	tiles[8].setTextureRect(sf::IntRect(17, 17, 16, 16));
	tiles[9].setCollider(false);
	tiles[9].setTextureRect(sf::IntRect(34, 17, 16, 16));

	tileMap.setTileSet(tiles);

	//Map dimensions
	sf::Vector2u mapSize(12, 6);

	//build map
	std::vector<int> map = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3,
		0, 0, 0, 1, 3, 0, 0, 0, 0, 7, 8, 9,
		1, 2, 3, 4, 6, 1, 2, 3, 0, 7, 8, 9,
		4, 5, 6, 0, 0, 4, 5, 6, 0, 4, 5, 6,
	};

	tileMap.setTileMap(map, mapSize);
	tileMap.setPosition(sf::Vector2f(0, 484));
	tileMap.buildLevel();
}

void MapSetup::MapRender(sf::RenderWindow* window)
{
	tileMap.render(window);
}

void MapSetup::Collision(GameObject &player)
{
	std::vector<GameObject>* world = tileMap.getLevel();
	
	for (int i = 0; i < (int)world->size(); i++)
	{
		float diffX = ((*world)[i].getPosition().x + 8) - (player.getPosition().x + 8);
		float diffY = ((*world)[i].getPosition().y + 8) - (player.getPosition().y + 8);
		
		//if collision should occur
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(&player, &(*world)[i]))
			{
				if (abs(diffY) < abs(diffX))
				{
					player.setVelocity(0.0f, player.getVelocity().y);
				}
				else
				{
					player.collisionResponse(&(*world)[i]);
				}
			}
		}
	}
}

MapSetup::~MapSetup()
{

}
