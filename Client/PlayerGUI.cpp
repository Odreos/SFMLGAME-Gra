#include "PlayerGUI.hpp"

PlayerGUI::PlayerGUI(Player* p)
{
	playerView = View({ 0,0 }, { WINDOW_X,WINDOW_Y });
	textPing.setFont(f);
	textPing.setFillColor(Color::Green);
	textPing.setPosition({ 0,0 });
	textPing.setCharacterSize(20);

	weaponInfo.setFont(f);
	weaponInfo.setFillColor(Color::Green);
	weaponInfo.setPosition({ 0,0 });
	weaponInfo.setCharacterSize(40);

	playersStatusInfo.setFont(f);
	playersStatusInfo.setFillColor(Color::Green);
	playersStatusInfo.setPosition({ 0,0 });
	playersStatusInfo.setCharacterSize(20);

	drawElements = 0;
	this->p = p;
}

void PlayerGUI::update(Vector2f pos)
{
	textPing.setPosition({ pos.x - WINDOW_X/2, pos.y - WINDOW_Y/2 });
	weaponInfo.setString(p->weapon.ammoAndMagInfo);
	weaponInfo.setPosition({ pos.x - WINDOW_X / 2, pos.y - (float)(WINDOW_Y * 0.1) + WINDOW_Y / 2 });
	playersStatusInfo.setPosition({ pos.x - WINDOW_X / 2, (pos.y - WINDOW_Y / 2) + 20 });
	setViewPos(pos);
}

void PlayerGUI::setFont(Font& t)
{
	f = t;
}

void PlayerGUI::setPingText(string s)
{
	textPing.setString(s);
}

void PlayerGUI::setPlayersStatusInfo(string s)
{
	playersStatusInfo.setString(s);
}

void PlayerGUI::setWeaponInfo(string s)
{
	weaponInfo.setString(s);
}

void PlayerGUI::setView(RenderWindow& w)
{
	w.setView(playerView);
}

void PlayerGUI::setViewPos(Vector2f pos)
{
	playerView.setCenter(pos);
}

void PlayerGUI::draw(RenderWindow& w)
{
	if (drawElements)
	{
		w.draw(textPing);
		w.draw(playersStatusInfo);
	}
	w.draw(weaponInfo);
}
