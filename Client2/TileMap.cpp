#include "TileMap.hpp"

TileMap::TileMap()
{
	txt.loadFromFile(TILE_PNG);
	endTXT.loadFromFile(TILE_END_PNG);
	AddTileToVector();
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
	for (int x = 0; x < MapSize.x; x++)
		for (int y = 0; y < MapSize.y; y++)
		{
			allTiles[y * MapSize.x + x].node.bVisited = false;
			allTiles[y * MapSize.x + x].node.fGlobalGoal = INFINITY;
			allTiles[y * MapSize.x + x].node.fLocalGoal = INFINITY;
			allTiles[y * MapSize.x + x].node.parent = nullptr;
		}

	auto distance = [](sNode* a, sNode* b)
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b)
	{
		return distance(a, b);
	};

	Vector2f ePos = enemy->GetPos();
	sNode* nodeStart = &GetTileByPos(ePos).node;
	sNode* nodeEnd = &GetTileByPos(EndPoint).node;

	sNode* nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)
	{
		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true;

		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{
			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
			{
				listNotTestedNodes.push_back(nodeNeighbour);
			}

			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;
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

	enemy->AddIDToTileMove(tilesIDPath);

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

	for (auto& r : visibleTiles)
		r.Draw(window);
}