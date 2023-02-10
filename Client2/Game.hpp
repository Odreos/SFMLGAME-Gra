#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ServerConnect.hpp"
#include <thread>
#include <ctime>
#include <array>
#include <map>
#include "Player.hpp"
#include "Definitions.hpp"
#include "TileMap.hpp"
#include "PlayerGUI.hpp"
#include "EnemyManager.hpp"
#include "Enemy.hpp"

using namespace std;
using namespace sf;

#define MAX_PLAYERS 5

enum ServerInfo
{
	MouseClickedLeft1,
	MouseRelesedLeft1,
	Key_W_Clicked,
	Key_S_Clicked,
	Key_A_Clicked,
	Key_D_Clicked,
	Key_W_Relesed,
	Key_S_Relesed,
	Key_A_Relesed,
	Key_D_Relesed,
	Key_R_Clicked,
	Key_R_Relesed,
	ChangePlayerAngle,
	Key_Space_Clicked,
	Key_F5_Clicked
};


class Game
{
	ServerConnect* server;
	RenderWindow window;
	Clock* timer;
	TileMap tileMap;
	PlayerGUI* pGUI;
	chrono::system_clock gameTime;
	chrono::system_clock::time_point tab[3];
	Text textPing;
	Font f;
	Texture playertxt;
	Texture zombitxt;
	Player players[MAX_PLAYERS];
	Text gameInfo;
	bool showGameInfo;
	vector<Enemy*> enemies;
	EnemyManager* eM;
	map<float, Vector2f> pointsOfWhereIsPlayerLookAt;
	CircleShape pointLaserPlayer;
	Vector2f pointWherePlayerLookAt;
	double clientTimeBySFMLClock;
	double gameTicketsDelay;
	double gameTickets;
	double dt;
	int myID;
	int ping;
	double fps;
	bool focus;
	float playerAngle;
	float serverTick = 1 / 128.f;

	void gameLoop();
	void handleInput();
	void handleInputByNoTick();
	void updateByTick(double dt);
	void updateByNoTick(double dt);
	void sendServerInfo(ServerInfo s);
	void GetRaycast(RectangleShape& wall, Player& p, Vector2f mousePos);
	array<Vector2f, 4>& GetVertices(RectangleShape& r);
	float GetLenghtVector(Vector2f v);
	void GetPointWherePlayerLookAt(Player& p);
	void draw();
public:
	Game();
	void startGame();
};

