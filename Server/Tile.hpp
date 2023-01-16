#pragma once
#include "Definitions.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

struct sNode
{
	bool bObstacle = false;
	bool bVisited = false;
	float fGlobalGoal;
	float fLocalGoal;
	int x;
	int y;
	int tileID;
	vector<sNode*> vecNeighbours;
	sNode* parent;
};

class Tile
{
	int idOfTexture;

public:
	sNode node;
	bool isColiding;
	int xMapCord, yMapCord, IdMapCord;
	RectangleShape tile;
	Tile();
	void SetTexture(Texture& t);
	//Texture& GetTexture();
	void SetPosition(Vector2f pos);
	void SetMapCord(int x, int y, int z);
	Vector2i GetMapCord();
	void Draw(RenderWindow& window);
};

