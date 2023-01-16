#pragma once
#include <SFML/Network.hpp>
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <list>
#include <ctime>
#include <chrono>
#include <Windows.h>
#include <array>
#include "Player.hpp"
#include "Bullet.hpp"
#include "TileMap.hpp"
#include "EnemyManager.hpp"
#include "Enemy.hpp"

#define MAX_PLAYERS 5

using namespace std;
using namespace sf;

enum PacketTypes
{
	NewConnect,
	SetID,
	ListOfCliends,
	Disconect,
	ServerFull,
	SetTickets,
	Ping,
	MouseClickLeft,
	MouseClickRight,
	CreateBall,
	ChangeBallColor,
	DeletePoint,
	SetPlayerPos,
	Keyboard_W_Clicked,
	Keyboard_S_Clicked,
	Keyboard_A_Clicked,
	Keyboard_D_Clicked,
	SetPlayerMovingState,
	Keyboard_W_Relesed,
	Keyboard_S_Relesed,
	Keyboard_A_Relesed,
	Keyboard_D_Relesed,
	RefreshPing,
	MouseRelesedLeft,
	CreateBullet,
	ClearBulletVector,
	SetPlayerPosition,
	PlayerWallColDetected,
	PlayerAngleChange,
	DeleteBullet,
	Keyboard_R_Clicked,
	Keyboard_R_Relesed,
	SetWeaponInfoAfterReload,
	SetLaserPointPlayer,
	PlayerIsShooting,
	PlayerShooted,
	CreateEnemy,
	CreateEnemyAfterConnect,
	DeleteEnemy,
	SetPlayerReload,
	Keyboard_Space_Clicked,
	Keyboard_F5_Clicked,
	SetPlayerStatusForGameplay,
	GameisLose,
	GameStarted,
	UDPPort
};
enum SendPacketsType
{
	All,
	WithoutOne,
	OnlyOne
};

class Server
{
	TcpListener server;
	UdpSocket udpSocket;
	IpAddress serverIP;
	TcpSocket* clients[MAX_PLAYERS];
	Player players[MAX_PLAYERS];
	Clock* serverTimer;
	vector<Enemy> enemies;
	EnemyManager* eM;
	chrono::system_clock serverTime;
	chrono::system_clock::time_point tab[3];
	double serverTimeBySFMLClock;
	TileMap tileMap;
	double serverTickets;
	unsigned short serverPort;
	unsigned short serverPortUDP;
	float serverTick = 1 / 128.f;
	float enemyTimeToResp = 2.f;
	bool startRespEnemy;
	double dt;
	bool Clicked_Key_Space;
	int clientsID;
	int entityID;
	bool isGameOn;
	vector<Bullet*> bullets;

	void addNewClient();
	void receiveData();
	int getFreeID();
	double getServerTickets();
	void sendPackets(Packet* p, int clientID, SendPacketsType type);
	void sendPacketsUDP(Packet* p, int clientID, SendPacketsType type);
	float GetLenghtVector(Vector2f v);
	float determinant(Vector2f& x1, Vector2f& x2);
	array<Vector2f, 4>& GetVertices(RectangleShape& r);
	void GetRaycast(RectangleShape& wall, Player& p, Vector2f mousePos);
	void GetRaycastEnemy(Enemy& e, Player& p, Vector2f mousePos);
	void createBullet(Vector2f pos, Vector2f dirr, int ownerID, int entityID);
	Vector2f UptadePlayerMousePos(Player& p);
	void updateServerByTick(double dt);
	void updateServerByNoTick(double dt);
	void StartGamePlay();
	void GamePlay(float dt);
	void CreateEnemyByTime(float dt);
	void CreateEnemy(int TileID);
	void CreateEnemies();
public:
	void startServer();
	Server();
};

