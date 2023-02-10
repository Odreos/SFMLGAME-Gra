#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>
#include "Player.hpp"
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
	SetPlayerPosition,
	PlayerWallColDetected,
	PlayerAngleChange,
	Keyboard_R_Clicked,
	Keyboard_R_Relesed,
	SetWeaponInfoAfterReload,
	PlayerIsShooting,
	PlayerShooted,
	CreateEnemy,
	CreateEnemyAfterConnect,
	DeleteEnemy,
	SetPlayerReload,
	Keyboard_F5_Clicked,
	SetPlayerStatusForGameplay,
	GameisLose,
	GameStarted,
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

	double PingServerTickets[2];

	void sendDataTCP(Packet& p);
	void receiveDataTCP();
	void serverLoop();
	int getClientID();
	double getClientTickets();
	void setClientTickets(double t);
	void setGameTicketsPointer(double* delay, double* tick, double* DT);
	void setEnemyManagerPointer(EnemyManager* em);
	void setPlayersPointer(Player* p);
	void correctDelay(double serverTickets);
	void SetTextPing(Text* t);
	void RefreshPing(bool secondTime, double serverTickets);
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

