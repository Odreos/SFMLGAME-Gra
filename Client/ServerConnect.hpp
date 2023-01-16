#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>
#include "Ball.hpp"
#include "MovePoint.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
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
enum GameHandleInputMouse
{
	MouseClicked_Left,
	MouseRelesed_Left,
	MouseClicked_Right,
	MouseChangeAngle
};
enum GameHandleInputKeyboard
{
	Keyboard_W,
	Keyboard_S,
	Keyboard_A,
	Keyboard_D,
	Keyboard_W_Rel,
	Keyboard_S_Rel,
	Keyboard_A_Rel,
	Keyboard_D_Rel,
	Keyboard_R,
	Keyboard_R_Rel,
	Keyboard_Space,
	Keyboard_F5
};

class ServerConnect
{
	TcpSocket server;
	UdpSocket serverUDP;
	IpAddress serverIP;
	Clock* clientTime;
	Texture* plrTXT;
	Texture* zombiTXT;
	double* clientTicketsDelay;
	double* clientTickets;
	double* dt;
	int clients[MAX_PLAYERS];
	Player *players;
	unsigned short serverPort;
	unsigned short serverPortUDP;
	int ourID;
	vector<Ball>* balls;
	vector<MovePoint*>* movePoints;
	vector<Bullet>* bullets;
	EnemyManager* eM;
	Text* pingText;
	bool goodConnect;
	double timeEs;
	bool gameStarted;
	bool gameLose;
	int* Ping;
	chrono::system_clock serverConnectTimer;
	chrono::system_clock::time_point tab[5];
	chrono::system_clock::time_point gameStartTime;
	chrono::system_clock::time_point PingServerDelay[2];
	//double timeServerClient[10];
	//double timeServerClient2[5];
	//double timeServerClientDelta[5];

	double PingServerTickets[2];

	void sendDataTCP(Packet& p);
	void receiveDataTCP();
	void receiveDataUDP();
	void serverLoop();
	int getClientID();
	double getClientTickets();
	void setClientTickets(double t);
	void setGameTicketsPointer(double* delay, double* tick, double* DT);
	void setBallsPointer(vector<Ball>* b);
	void setMovePointsPointer(vector<MovePoint*>* moveP);
	void setEnemyManagerPointer(EnemyManager* em);
	void setBulletsPointer(vector<Bullet>* b);
	void setPlayersPointer(Player* p);
	void createBall(Vector2f pos, int id);
	void correctDelay(double serverTickets);
	Ball* getBallByID(int ID);
	void SetTextPing(Text* t);
	void RefreshPing(bool secondTime, double serverTickets);
	MovePoint* getMovePointByID(int ID);
	void setInitialTimeGame(chrono::system_clock::time_point x);
	double* getGameTickets();
	void setMyID(int* id);
	void setPing(int* ping);
	friend class Game;
public:
	bool pingChecked;

	ServerConnect();
	bool connectToServer();
	void updateServerConnect();
	void gameHandleInput(GameHandleInputKeyboard gHIK);
	void getGameHandleInputMouse(GameHandleInputMouse gHIM, Vector2f pos);
};

