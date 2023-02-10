#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

class PlayerGUI
{
public:
	View playerView;
	Text textPing;
	Text weaponInfo;
	Text playersStatusInfo;
	Font f;
	Player* p;
	bool drawElements;

	PlayerGUI(Player* p);
	void update(Vector2f pos);
	void setFont(Font& t);
	void setPingText(string s);
	void setPlayersStatusInfo(string s);
	void setWeaponInfo(string s);
	void setView(RenderWindow& w);
	void setViewPos(Vector2f pos);
	void draw(RenderWindow& w);
};

