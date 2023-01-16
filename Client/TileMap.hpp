#pragma once

#include "Tile.hpp"
#include "Definitions.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Enemy.hpp"
#include <list>

using namespace sf;
using namespace std;

class TileMap
{
	string WorldMap =
		"################################"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..........###.....###.........#"
		"#..........#.........#.........#"
		"#....#######.........#.........#"
		"#....#.....#.........####...#..#"
		"#....###...#####.....#......#..#"
		"#....#...............#......#..#"
		"#....................####......#"
		"#....####..#...................#"
		"#....#.....#.........########..#"
		"#....#######................#..#"
		"#...........................#..#"
		"#....#....#######..#...#....#..#"
		"#....#..........#..#...#....#..#"
		"#....#..........#..#...######..#"
		"#....#.............#...........#"
		"#....#####...#######...........#"
		"#..............................#"
		"#..............................#"
		"#...........#########......#...#"
		"#....#####.................#...#"
		"#....................#######...#"
		"#.....................#....#...#"
		"#.......####...####...#........#"
		"#.......#.........#............#"
		"#..............................#"
		"#............X.................#"
		"#.......#.........#............#"
		"################################";


	Vector2i MapSize = { MAP_SIZE,MAP_SIZE };
	//vector<Tile*> Map;

public:
	Tile Map[MAP_SIZE][MAP_SIZE];
	vector<Tile> allTiles;
	vector<Tile> visibleTiles;
	Texture txt;
	Texture endTXT;

	TileMap();
	void AddTileToVector();
	void LoadTileTextures();
	//bool CheckCollPlayer(Player* p, float dt);
	bool CheckCollBullet(Bullet* b, float dt);
	bool RectvsRectCol(Player& p, float dt);
	bool Solve_AStar(Enemy* enemy, Vector2f EndPoint);
	//bool BulletColl(float dt, Bullet* b);
	void SetVisibleTilesToDraw(Vector2f pPos);
	Tile& GetTileByPos(Vector2f pos);
	Vector2f TilePosByID(Vector2f pos);
	void Update(Vector2f pPos);
	void Draw(RenderWindow& window);

};

