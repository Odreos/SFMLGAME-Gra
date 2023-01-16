#include "TileMap.hpp"

TileMap::TileMap()
{
	txt.loadFromFile(TILE_PNG);
	endTXT.loadFromFile(TILE_END_PNG);
	AddTileToVector();
	/*RectangleShape r1;
	r1.setPosition({ 11 * TILE_SIZE, 4 * TILE_SIZE });
	r1.setFillColor(Color::Red);
	r1.setSize({ 3 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r1);

	RectangleShape r2;
	r2.setPosition({ 19 * TILE_SIZE, 4 * TILE_SIZE });
	r2.setFillColor(Color::Red);
	r2.setSize({ 3 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r2);

	RectangleShape r3;
	r3.setPosition({ 11 * TILE_SIZE, 5 * TILE_SIZE });
	r3.setFillColor(Color::Red);
	r3.setSize({ 1 * TILE_SIZE, 4 * TILE_SIZE });
	rects.push_back(r3);

	RectangleShape r4;
	r4.setPosition({ 21 * TILE_SIZE, 5 * TILE_SIZE });
	r4.setFillColor(Color::Red);
	r4.setSize({ 1 * TILE_SIZE, 5 * TILE_SIZE });
	rects.push_back(r4);

	RectangleShape r5;
	r5.setPosition({ 6 * TILE_SIZE, 6 * TILE_SIZE });
	r5.setFillColor(Color::Red);
	r5.setSize({ 5 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r5);

	RectangleShape r6;
	r6.setPosition({ 5 * TILE_SIZE, 6 * TILE_SIZE });
	r6.setFillColor(Color::Red);
	r6.setSize({ 1 * TILE_SIZE, 4 * TILE_SIZE });
	rects.push_back(r6);

	RectangleShape r7;
	r7.setPosition({ 6 * TILE_SIZE, 8 * TILE_SIZE });
	r7.setFillColor(Color::Red);
	r7.setSize({ 2 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r7);

	RectangleShape r8;
	r8.setPosition({ 12 * TILE_SIZE, 8 * TILE_SIZE });
	r8.setFillColor(Color::Red);
	r8.setSize({ 4 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r8);

	RectangleShape r9;
	r9.setPosition({ 5 * TILE_SIZE, 11 * TILE_SIZE });
	r9.setFillColor(Color::Red);
	r9.setSize({ 4 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r9);

	RectangleShape r10;
	r10.setPosition({ 5 * TILE_SIZE, 11 * TILE_SIZE });
	r10.setFillColor(Color::Red);
	r10.setSize({ 1 * TILE_SIZE, 3 * TILE_SIZE });
	rects.push_back(r10);

	RectangleShape r11;
	r11.setPosition({ 5 * TILE_SIZE, 13 * TILE_SIZE });
	r11.setFillColor(Color::Red);
	r11.setSize({ 7 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r11);

	RectangleShape r12;
	r12.setPosition({ 11 * TILE_SIZE, 11 * TILE_SIZE });
	r12.setFillColor(Color::Red);
	r12.setSize({ 1 * TILE_SIZE, 2 * TILE_SIZE });
	rects.push_back(r12);

	RectangleShape r13;
	r13.setPosition({ 21 * TILE_SIZE, 4 * TILE_SIZE });
	r13.setFillColor(Color::Red);
	r13.setSize({ 1 * TILE_SIZE, 7 * TILE_SIZE });
	rects.push_back(r13);

	RectangleShape r14;
	r14.setPosition({ 21 * TILE_SIZE, 7 * TILE_SIZE });
	r14.setFillColor(Color::Red);
	r14.setSize({ 4 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r14);

	RectangleShape r15;
	r15.setPosition({ 21 * TILE_SIZE, 10 * TILE_SIZE });
	r15.setFillColor(Color::Red);
	r15.setSize({ 4 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r15);

	RectangleShape r16;
	r16.setPosition({ 28 * TILE_SIZE, 7 * TILE_SIZE });
	r16.setFillColor(Color::Red);
	r16.setSize({ 1 * TILE_SIZE, 3 * TILE_SIZE });
	rects.push_back(r16);

	RectangleShape r17;
	r17.setPosition({ 21 * TILE_SIZE, 12 * TILE_SIZE });
	r17.setFillColor(Color::Red);
	r17.setSize({ 8 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r17);

	RectangleShape r18;
	r18.setPosition({ 28 * TILE_SIZE, 13 * TILE_SIZE });
	r18.setFillColor(Color::Red);
	r18.setSize({ 1 * TILE_SIZE, 5 * TILE_SIZE });
	rects.push_back(r18);

	RectangleShape r19;
	r19.setPosition({ 23 * TILE_SIZE, 15 * TILE_SIZE });
	r19.setFillColor(Color::Red);
	r19.setSize({ 1 * TILE_SIZE, 3 * TILE_SIZE });
	rects.push_back(r19);

	RectangleShape r20;
	r20.setPosition({ 23 * TILE_SIZE, 17 * TILE_SIZE });
	r20.setFillColor(Color::Red);
	r20.setSize({ 6 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r20);

	RectangleShape r21;
	r21.setPosition({ 5 * TILE_SIZE, 15 * TILE_SIZE });
	r21.setFillColor(Color::Red);
	r21.setSize({ 1 * TILE_SIZE, 4 * TILE_SIZE });
	rects.push_back(r21);

	RectangleShape r22;
	r22.setPosition({ 10 * TILE_SIZE, 15 * TILE_SIZE });
	r22.setFillColor(Color::Red);
	r22.setSize({ 7 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r22);

	RectangleShape r23;
	r23.setPosition({ 16 * TILE_SIZE, 15 * TILE_SIZE });
	r23.setFillColor(Color::Red);
	r23.setSize({ 1 * TILE_SIZE, 3 * TILE_SIZE });
	rects.push_back(r23);

	RectangleShape r24;
	r24.setPosition({ 19 * TILE_SIZE, 15 * TILE_SIZE });
	r24.setFillColor(Color::Red);
	r24.setSize({ 1 * TILE_SIZE, 4 * TILE_SIZE });
	rects.push_back(r24);

	RectangleShape r25;
	r25.setPosition({ 5 * TILE_SIZE, 19 * TILE_SIZE });
	r25.setFillColor(Color::Red);
	r25.setSize({ 5 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r25);

	RectangleShape r26;
	r26.setPosition({ 13 * TILE_SIZE, 19 * TILE_SIZE });
	r26.setFillColor(Color::Red);
	r26.setSize({ 7 * TILE_SIZE, 1 * TILE_SIZE });
	rects.push_back(r26);*/
}

void TileMap::AddTileToVector()
{
	Vector2i vTL = { 0,0 };
	Vector2i vBR = MapSize;
	Vector2i vTile;
	for (vTile.y = vTL.y; vTile.y < vBR.y; vTile.y++)
		for (vTile.x = vTL.x; vTile.x < vBR.x; vTile.x++)
		{
			if (WorldMap[vTile.y * MapSize.x + vTile.x] == '#')
			{
				string id = to_string(1);
				Tile* t = new Tile();
				t->SetPosition({ (float)vTile.x * TILE_SIZE ,(float)vTile.y * TILE_SIZE });
				//t->tile.setOrigin(t->tile.getSize() / 2.f);
				t->SetMapCord(vTile.x, vTile.y, (vTile.y * MapSize.x + vTile.x));
				t->SetTexture(txt);
				t->isColiding = 1;
				//Map.push_back(t);

				t->node.x = vTile.x;
				t->node.y = vTile.y;
				t->node.bObstacle = true;
				t->node.parent = nullptr;
				t->node.bVisited = false;
				t->node.tileID = t->IdMapCord;

				Map[vTile.x][vTile.y] = *t;
				allTiles.push_back(*t);
			}
			if (WorldMap[vTile.y * MapSize.x + vTile.x] == '.')
			{
				string id = to_string(2);
				Tile* t = new Tile();
				t->isColiding = 0;
				t->SetMapCord(vTile.x, vTile.y, (vTile.y * MapSize.x + vTile.x));
				t->SetPosition({ (float)vTile.x * TILE_SIZE ,(float)vTile.y * TILE_SIZE });
				//t->tile.setOrigin(t->tile.getSize() / 2.f);

				t->node.x = vTile.x;
				t->node.y = vTile.y;
				t->node.bObstacle = false;
				t->node.parent = nullptr;
				t->node.bVisited = false;
				t->node.tileID = t->IdMapCord;

				Map[vTile.x][vTile.y] = *t;
				allTiles.push_back(*t);
			}
			if (WorldMap[vTile.y * MapSize.x + vTile.x] == 'X')
			{
				string id = to_string(2);
				Tile* t = new Tile();
				t->isColiding = 0;
				t->specialInfo = 1;
				t->SetMapCord(vTile.x, vTile.y, (vTile.y * MapSize.x + vTile.x));
				t->SetPosition({ (float)vTile.x * TILE_SIZE ,(float)vTile.y * TILE_SIZE });
				t->SetTexture(endTXT);
				//t->tile.setOrigin(t->tile.getSize() / 2.f);

				t->node.x = vTile.x;
				t->node.y = vTile.y;
				t->node.bObstacle = false;
				t->node.parent = nullptr;
				t->node.bVisited = false;
				t->node.tileID = t->IdMapCord;

				Map[vTile.x][vTile.y] = *t;
				allTiles.push_back(*t);
			}
		}

	for (int x = 0; x < MapSize.x; x++)
	{
		for (int y = 0; y < MapSize.y; y++)
		{
			if (y > 0)
				allTiles[y * MapSize.x + x].node.vecNeighbours.push_back(&allTiles[(y - 1) * MapSize.x + (x + 0)].node);
			if (y < MapSize.y - 1)
				allTiles[y * MapSize.x + x].node.vecNeighbours.push_back(&allTiles[(y + 1) * MapSize.x + (x + 0)].node);
			if (x > 0)
				allTiles[y * MapSize.x + x].node.vecNeighbours.push_back(&allTiles[(y + 0) * MapSize.x + (x - 1)].node);
			if (x < MapSize.x - 1)
				allTiles[y * MapSize.x + x].node.vecNeighbours.push_back(&allTiles[(y + 0) * MapSize.x + (x + 1)].node);
		}
	}



}

void TileMap::LoadTileTextures()
{
	//_data->assets.LoadTexture("1", INGAME_STATE_TILE_TXT_GRASS);
	//_data->assets.LoadTexture("2", INGAME_STATE_TILE_TXT_STONE);
	//_data->assets.LoadTexture("3", INGAME_STATE_TILE_TXT_GRAVEL);
}

bool TileMap::CheckCollBullet(Bullet* b, float dt)
{
	Vector2f movement = b->velo;

	Vector2f newVelo({ movement.x * (float)dt, movement.y * (float)dt });

	Vector2f bPos = b->bullet.getPosition();

	Vector2f PotentialPos = { bPos.x + newVelo.x , bPos.y + newVelo.y };

	//cout << p->GetPos().x << " PLAYER " << p->GetPos().y << endl;

	int playerx = bPos.x / TILE_SIZE;
	int playery = bPos.y / TILE_SIZE;

	Vector2i TopLeft = { max(playerx - 1,0),max(playery - 1,0) };
	Vector2i BottomRight = { min(playerx + 1,MapSize.x),min(playery + 1,MapSize.y) };

	int xcell, ycell;

	for (ycell = TopLeft.y; ycell <= BottomRight.y; ycell++)
	{
		for (xcell = TopLeft.x; xcell <= BottomRight.x; xcell++)
		{
			if (WorldMap[ycell * MapSize.x + xcell] == '#')
			{
				Vector2f vNearestPoint;
				vNearestPoint.x = max((float)xcell * TILE_SIZE, min(bPos.x, (float)xcell * TILE_SIZE + TILE_SIZE));
				vNearestPoint.y = max((float)ycell * TILE_SIZE, min(bPos.y, (float)ycell * TILE_SIZE + TILE_SIZE));

				Vector2f vRayToNearest = vNearestPoint - PotentialPos;
				float nMag = sqrtf(pow(vRayToNearest.x, 2) + pow(vRayToNearest.y, 2));
				float fOverlap = b->bullet.getRadius() - nMag;
				if (isnan(fOverlap)) fOverlap = 0;

				if (fOverlap > 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool TileMap::RectvsRectCol(Player& p, float dt)
{
	Vector2f playerPos = p.getPos();
	Vector2f playerHalfSize = p.player.getSize() / 2.f;

	Vector2f movement = p.getVelo();
	Vector2f newVelo({ movement.x * dt, movement.y * dt });
	Vector2f moveNorm;

	switch (p.getDir())
	{
	case MoveUp: // up
	{
		newVelo.x = 0;
		newVelo.y = newVelo.y * -1;
		moveNorm = { 0,-1 };
	}
	break;
	case MoveDown: // down
	{
		newVelo.x = 0;
		moveNorm = { 0,1 };
	}
	break;
	case MoveLeft: // left
	{
		newVelo.x = newVelo.x * -1;
		newVelo.y = 0;
		moveNorm = { -1,0 };
	}
	break;
	case MoveRight: // right
	{
		newVelo.y = 0;
		moveNorm = { 1,0 };
	}
	break;
	default:
		break;
	}
	//cout << p->GetPos().x << " PLAYER " << p->GetPos().y << endl;

	Vector2f playerPotentialPos = { playerPos.x + newVelo.x , playerPos.y + newVelo.y };

	int playerx = p.getPos().x / TILE_SIZE;
	int playery = p.getPos().y / TILE_SIZE;

	Vector2i TopLeft = { max(playerx - 1,0),max(playery - 1,0) };
	Vector2i BottomRight = { min(playerx + 1,MapSize.x),min(playery + 1,MapSize.y) };

	Vector2f wallPos;
	Vector2f wallHalfSize;
	Vector2f delta;
	Vector2f intersect;

	int xcell, ycell;

	for (ycell = TopLeft.y; ycell <= BottomRight.y; ycell++)
	{
		for (xcell = TopLeft.x; xcell <= BottomRight.x; xcell++)
		{
			if (Map[xcell][ycell].isColiding)
			{
				RectangleShape& wall = Map[xcell][ycell].tile;
				wallPos = wall.getPosition();
				wallPos.x += TILE_SIZE / 2;
				wallPos.y += TILE_SIZE / 2;
				wallHalfSize = wall.getSize() / 2.f;

				delta = playerPotentialPos - wallPos;
				intersect = { fabs(delta.x) - (playerHalfSize.x + wallHalfSize.x), fabs(delta.y) - (playerHalfSize.y + wallHalfSize.y) };

				if (intersect.x < 0.f && intersect.y < 0.f)
				{
					playerPotentialPos = { playerPotentialPos.x + intersect.x * moveNorm.x,playerPotentialPos.y + intersect.y * moveNorm.y };

					p.setPos(playerPotentialPos);
					return true;
				}
			}
		}
	}
	return false;
}

bool TileMap::Solve_AStar(Enemy* enemy, Vector2f EndPoint)
{
	// Reset Navigation Graph - default all node states
	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			allTiles[y * MapSize.x + x].node.bVisited = false;
			allTiles[y * MapSize.x + x].node.fGlobalGoal = INFINITY;
			allTiles[y * MapSize.x + x].node.fLocalGoal = INFINITY;
			allTiles[y * MapSize.x + x].node.parent = nullptr;
		}

	auto distance = [](sNode* a, sNode* b) // For convenience
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
	{
		return distance(a, b);
	};

	// Setup starting conditions
	Vector2f ePos = enemy->GetPos();
	sNode* nodeStart = &GetTileByPos(ePos).node;
	sNode* nodeEnd = &GetTileByPos(EndPoint).node;

	//cout << "start: " << nodeStart->tileID << " end: " << nodeEnd->tileID << endl;

	sNode* nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	// Add start node to not tested list - this will ensure it gets tested.
	// As the algorithm progresses, newly discovered nodes get added to this
	// list, and will themselves be tested later
	list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	// if the not tested list contains nodes, there may be better paths
	// which have not yet been explored. However, we will also stop 
	// searching when we reach the target - there may well be better
	// paths but this one will do - it wont be the longest.
	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
	{
		// Sort Untested nodes by global goal, so lowest is first
		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

		// Front of listNotTestedNodes is potentially the lowest distance node. Our
		// list may also contain nodes that have been visited, so ditch these...
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		// ...or abort because there are no valid nodes left to test
		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true; // We only explore a node once


		// Check each of this node's neighbours...
		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{
			// ... and only if the neighbour is not visited and is 
			// not an obstacle, add it to NotTested List
			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
			{
				listNotTestedNodes.push_back(nodeNeighbour);
			}

			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			// If choosing to path through this node is a lower distance than what 
			// the neighbour currently has set, update the neighbour to use this node
			// as the path source, and set its distance scores as necessary
			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
			}
		}
	}

	vector<int> tilesIDPath;

	if (nodeEnd != nullptr)
	{
		sNode* p = nodeEnd;
		while (p->parent != nullptr)
		{
			tilesIDPath.push_back(p->tileID);
			p = p->parent;
		}
	}

	reverse(tilesIDPath.begin(), tilesIDPath.end());

	//cout << tilesIDPath.size() << endl;

	enemy->AddIDToTileMove(tilesIDPath);

	//cout << enemy->mapTileIDToMove.size() << endl;

	return true;
}

void TileMap::SetVisibleTilesToDraw(Vector2f pPos)
{
	visibleTiles.clear();

	int playerx = pPos.x / TILE_SIZE;
	int playery = pPos.y / TILE_SIZE;

	Vector2i TopLeft = { max(playerx - PLAYER_FOV_X,0),max(playery - PLAYER_FOV_Y,0) };
	Vector2i BottomRight = { min(playerx + PLAYER_FOV_X,MapSize.x - 1),min(playery + PLAYER_FOV_Y,MapSize.y - 1) };

	int xcell, ycell;
	for (ycell = TopLeft.y; ycell <= BottomRight.y; ycell++)
	{
		for (xcell = TopLeft.x; xcell <= BottomRight.x; xcell++)
		{
			if (Map[xcell][ycell].isColiding || Map[xcell][ycell].specialInfo)
				visibleTiles.push_back(Map[xcell][ycell]);
		}
	}
}

Tile& TileMap::GetTileByPos(Vector2f pos)
{
	int xPos = pos.x / TILE_SIZE;
	int yPos = pos.y / TILE_SIZE;

	return allTiles[yPos * MapSize.x + xPos];
	//return Map[xPos][yPos];
}

Vector2f TileMap::TilePosByID(Vector2f pos)
{
	return GetTileByPos(pos).tile.getPosition();
}

void TileMap::Update(Vector2f pPos)
{
	SetVisibleTilesToDraw(pPos);
}

void TileMap::Draw(RenderWindow& window)
{
	//for (auto& a : Map)
	//{
	//	for (auto& x : a)
	//	{
	//		if (x.isColiding)
	//			x.Draw(window);
	//	}
	//}
	for (auto& r : visibleTiles)
		r.Draw(window);
}

//bool TileMap::CheckCollPlayer(Player* p, float dt)
//{
//
//	Vector2f movement = p->getVelo();
//
//	Vector2f newVelo({ movement.x * (float)dt, movement.y * (float)dt });
//
//	switch (p->getDir())
//	{
//	case MoveUp: // up
//	{
//		newVelo.x = 0;
//		newVelo.y = newVelo.y * -1;
//	}
//	break;
//	case MoveDown: // down
//	{
//		newVelo.x = 0;
//	}
//	break;
//	case MoveLeft: // left
//	{
//		newVelo.x = newVelo.x * -1;
//		newVelo.y = 0;
//	}
//	break;
//	case MoveRight: // right
//	{
//		newVelo.y = 0;
//	}
//	break;
//	default:
//		break;
//	}
//
//	Vector2f PotentialPos = { p->getPos().x + newVelo.x , p->getPos().y + newVelo.y };
//	Vector2f PotentialPos2 = p->getPos();
//	//cout << p->GetPos().x << " PLAYER " << p->GetPos().y << endl;
//
//	int playerx = p->getPos().x / TILE_SIZE;
//	int playery = p->getPos().y / TILE_SIZE;
//
//	Vector2i TopLeft = { max(playerx - 1,0),max(playery - 1,0) };
//	Vector2i BottomRight = { min(playerx + 1,MapSize.x),min(playery + 1,MapSize.y) };
//
//	int xcell, ycell;
//	int i = 0;
//	for (ycell = TopLeft.y; ycell <= BottomRight.y; ycell++)
//	{
//		for (xcell = TopLeft.x; xcell <= BottomRight.x; xcell++)
//		{
//			//if (WorldMap[ycell * MapSize.x + xcell] == '#')
//			if(Map[xcell][ycell].isColiding)
//			{
//				Vector2f vNearestPoint;
//				vNearestPoint.x = max((float)xcell * TILE_SIZE, min(p->getPos().x, (float)xcell * TILE_SIZE + TILE_SIZE));
//				vNearestPoint.y = max((float)ycell * TILE_SIZE, min(p->getPos().y, (float)ycell * TILE_SIZE + TILE_SIZE));
//
//				Vector2f vRayToNearest = vNearestPoint - PotentialPos;
//				float nMag = sqrtf(powf(vRayToNearest.x, 2) + powf(vRayToNearest.y, 2));
//				float fOverlap = p->player.getRadius() - nMag;
//				if (isnan(fOverlap)) fOverlap = 0;
//
//				if (fOverlap > 0)
//				{
//					Vector2f RNorm = { vRayToNearest.x / nMag, vRayToNearest.y / nMag };
//					PotentialPos = PotentialPos - RNorm * fOverlap;
//
//					if (i == 0 || i == 1 || i == 2)
//					{
//						if (i == 0)
//						{
//							if (p->getDir() == MoveLeft)
//							{
//								if (Map[xcell][ycell + 1].isColiding)
//								{
//									PotentialPos = PotentialPos2;
//								}
//							}
//
//							if (Map[xcell + 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//						}
//						else if (i == 1)
//						{
//							float srodekX = xcell * TILE_SIZE + TILE_SIZE / 2;
//
//							if (p->getPos().x < srodekX && Map[xcell - 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//							else if (p->getPos().x > srodekX && Map[xcell + 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//						}
//						else if (i == 2)
//						{
//							float srodekX = xcell * TILE_SIZE + TILE_SIZE / 2;
//							if (p->getDir() == MoveRight)
//							{
//								if (Map[xcell][ycell + 1].isColiding)
//								{
//									PotentialPos = PotentialPos2;
//								}
//							}
//							else
//							if (p->getPos().x < srodekX && Map[xcell - 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//							else if (p->getPos().x > srodekX && Map[xcell + 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//						}
//					}
//
//					if (i == 3)
//					{
//						float srodekY = ycell * TILE_SIZE + TILE_SIZE / 2;
//
//						if (p->getPos().y < srodekY && Map[xcell][ycell - 1].isColiding)
//						{
//							PotentialPos = PotentialPos2;
//						}
//						else if (p->getPos().y > srodekY && Map[xcell][ycell + 1].isColiding)
//						{
//							PotentialPos = PotentialPos2;
//						}
//					}
//
//					if (i == 6 || i==7 || i==8)
//					{
//						if (i == 6)
//						{
//							if (Map[xcell + 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//							
//						}
//						else if (i==7)
//						{
//							if (Map[xcell + 1][ycell].isColiding || Map[xcell - 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//						}
//						else if(i==8)
//						{
//							if (Map[xcell - 1][ycell].isColiding)
//							{
//								PotentialPos = PotentialPos2;
//							}
//						}
//					}
//					p->setPos(PotentialPos);
//					return true;
//				}
//			}
//			i++;
//		}
//	}
//	return false;
//	if (PotentialPos != PotentialPos2)
//	{
//		p->setPos(PotentialPos);
//		return true;
//	}
//	else
//	{
//		//p->setPos(PotentialPos2);
//		return false;
//	}
//	return false;
//}

