#include "Tile.hpp"
#include <iostream>
Tile::Tile()
{
	idOfTexture = -1;
	xMapCord = 0;
	yMapCord = 0;
	isColiding = 0;
	//tiletxt.setTexture(txt);
	//Vector2u tsize = txt.getSize();
	//tiletxt.scale(TILE_SIZE / tsize.x, TILE_SIZE / tsize.y);

	tile.setSize({ TILE_SIZE ,TILE_SIZE });
}

void Tile::SetTexture(Texture& t)
{
	//Vector2u tsize = t.getSize();
	tile.setTexture(&t);
	//tile.scale(TILE_SIZE / tsize.x, TILE_SIZE / tsize.y);
}

//Texture& Tile::GetTexture()
//{
//	//return txt;
//
//}

void Tile::SetPosition(Vector2f pos)
{
	tile.setPosition(pos);
}

void Tile::SetMapCord(int x, int y, int z)
{
	xMapCord = x;
	yMapCord = y;
	IdMapCord = z;
}

Vector2i Tile::GetMapCord()
{
	return Vector2i{ xMapCord,yMapCord };
}

void Tile::Draw(RenderWindow& window)
{
	window.draw(tile);
}
