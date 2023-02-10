#include "ServerConnect.hpp"

void ServerConnect::sendDataTCP(Packet& p)
{
	server.send(p);
}

void ServerConnect::receiveDataTCP()
{
	Packet* newPacket = new Packet;
	if (server.receive(*newPacket) == Socket::Done)
	{
		int packetType;
		*newPacket >> packetType;
		switch (static_cast<PacketTypes> (packetType))
		{
		case PacketTypes::NewConnect:
		{
			int newClientID;
			*newPacket >> newClientID;
			Vector2f pos;
			*newPacket >> pos.x >> pos.y;

			clients[newClientID] = newClientID;
			players[newClientID].setOnline(true);
			players[newClientID].setID(newClientID);
			players[newClientID].setPos(pos);
			players[newClientID].setPlayerTxt(*plrTXT);
			players[newClientID].weapon.isLaserOn = 1;
		}
		break;
		case PacketTypes::SetID:
		{
			int id;
			*newPacket >> id;
			ourID = id;

			clients[id] = id;
			players[id].setOnline(true);
			players[id].setID(id);
			players[id].setPlayerTxt(*plrTXT);
			players[id].weapon.isLaserOn = 1;
		}
		break;
		case PacketTypes::SetPlayerPos:
		{

			int item;
			*newPacket >> item;
			clients[item] = item;
			players[item].setOnline(true);
			players[item].setPlayerTxt(*plrTXT);
			players[item].setID(item);
			players[item].weapon.isLaserOn = 1;
			Vector2f pos;
			*newPacket >> pos.x >> pos.y;
			players[item].setPos(pos);
			bool x;
			*newPacket >> x;
			players[item].isReadyForGameplay = x;

		}
		break;
		case PacketTypes::Disconect:
		{
			int id;
			*newPacket >> id;
			clients[id] = NULL;
			players[id].setOnline(false);
			players[id].isReadyForGameplay = 0;
		}
		break;
		case PacketTypes::ServerFull:
		{
			cout << "Serwer jest pelny!" << endl;
			return;
		}
		break;
		case PacketTypes::SetTickets:
		{
			float serverTickets;
			*newPacket >> serverTickets;
			setClientTickets(serverTickets);

			Packet p;
			p << PacketTypes::Ping << getClientID();
			sendDataTCP(p);
		}
		break;
		case PacketTypes::Ping:
		{
			static int y = 0;
			double serverTickets;
			*newPacket >> serverTickets;
			if (y == 1)
			{
				PingServerTickets[1] = serverTickets;
				PingServerDelay[1] = serverConnectTimer.now();

				double serverTicketsDiff = PingServerTickets[1] - PingServerTickets[0];
				chrono::duration<double> ClientPingDiff = chrono::duration_cast<chrono::duration<double>>(PingServerDelay[1] - PingServerDelay[0]);
				double ping = PingServerTickets[1] + (ClientPingDiff.count() /2);

				setClientTickets(ping);

				goodConnect = 1;
				y = 0;
			}
			else if (y == 0)
			{
				PingServerTickets[0] = serverTickets;
				PingServerDelay[0] = serverConnectTimer.now();
				Packet p;
				p << PacketTypes::Ping << getClientID();
				sendDataTCP(p);
				y = 1;
			}

		}
		break;
		case PacketTypes::SetPlayerMovingState:
		{
			bool t;
			*newPacket >> t;
			if (t)
			{
				double serverTickets;
				*newPacket >> serverTickets;
				int playerID;
				*newPacket >> playerID;
				PlayerDirection x;
				int playerD;
				*newPacket >> playerD;
				x = static_cast<PlayerDirection>(playerD);
				Vector2f pos;
				*newPacket >> pos.x >> pos.y;

				double diff = fabs(*clientTickets - serverTickets);

				players[playerID].setMovingState(true);
				players[playerID].setDir(x);
				players[playerID].setPos(pos);
			}
			else
			{
				int playerID;
				*newPacket >> playerID;
				Vector2f pos;
				*newPacket >> pos.x >> pos.y;

				players[playerID].setMovingState(false);
				players[playerID].setPos(pos);
			}
		}
		break;
		case PacketTypes::RefreshPing:
		{
			double serverTickets;
			*newPacket >> serverTickets;
			RefreshPing(true, serverTickets);
		}
		break;
		case PacketTypes::SetPlayerPosition:
		{
			int playerID;
			*newPacket >> playerID;
			Vector2f pos;
			*newPacket >> pos.x >> pos.y;
			players[playerID].setPos(pos);
		}
		break;
		case PacketTypes::PlayerWallColDetected:
		{
			int playerID;
			*newPacket >> playerID;
			Vector2f pos;
			*newPacket >> pos.x >> pos.y;
			players[playerID].setPos(pos);
		}
		break;
		case PacketTypes::PlayerAngleChange:
		{
			int id;
			*newPacket >> id;
			float angle;
			*newPacket >> angle;
			players[id].player.setRotation(angle);
		}
		break;
		case PacketTypes::SetWeaponInfoAfterReload:
		{
			int currentAmmo;
			*newPacket >> currentAmmo;
			int allAmmo;
			*newPacket >> allAmmo;

			players[ourID].weapon.SetAllAmmo(allAmmo);
			players[ourID].weapon.SetCurrentAmmo(currentAmmo);
			players[ourID].weapon.isReloading = 0;
		}
		break;
		case PacketTypes::PlayerIsShooting:
		{
			int playerID;
			*newPacket >> playerID;

			bool x;
			*newPacket >> x;
			if (x)
			{
				players[playerID].weapon.shooting = 1;
				players[playerID].muzzle.Play();
			}
			else
			{
				players[playerID].weapon.shooting = 0;
				players[playerID].muzzle.Stop();
			}
		}
		break;
		case PacketTypes::PlayerShooted:
		{
			players[ourID].weapon.currentAmmo -= 1;
		}
		break;
		case PacketTypes::CreateEnemyAfterConnect:
		{
			int enemyVectorSize;
			*newPacket >> enemyVectorSize;
			for (int i = 0; i < enemyVectorSize; i++)
			{
				int eID;
				Vector2f ePos;

				*newPacket >> eID >> ePos.x >> ePos.y;

				Enemy* e = new Enemy;
				e->SetID(eID);
				e->SetPos(ePos);
				eM->AddEnemy(e);
			}
		}
		break;
		case PacketTypes::DeleteEnemy:
		{
			int enemyID;
			*newPacket >> enemyID;

			eM->DeleteEnemy(enemyID);
		}
		break;
		case PacketTypes::SetPlayerReload:
		{
			int playerID;
			*newPacket >> playerID;
			bool x;
			*newPacket >> x;
			players[playerID].weapon.isReloading = x;
		}
		break;
		case PacketTypes::CreateEnemy:
		{
			double serverTicket;
			*newPacket >> serverTicket;
			int eID;
			*newPacket >> eID;
			Vector2f ePos;
			*newPacket >> ePos.x >> ePos.y;
			int tileIDSize;
			*newPacket >> tileIDSize;
			vector<int> tileID;

			for (int i = 0; i < tileIDSize; i++)
			{
				int es;
				*newPacket >> es;
				tileID.push_back(es);
			}

			Enemy* e = new Enemy;
			e->SetID(eID);
			e->SetPos(ePos);
			e->SetEnemyTxt(zombiTXT);
			e->AddIDToTileMove(tileID);
			eM->AddEnemy(e);
		}
		break;
		case PacketTypes::SetPlayerStatusForGameplay:
		{
			int clientID;
			*newPacket >> clientID;
			bool x;
			*newPacket >> x;
			players[clientID].isReadyForGameplay = x;
		}
		break;
		case PacketTypes::GameisLose:
		{
			gameLose = 1;
			eM->ClearEnemiesVec();
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				players[i].weapon.SetDefaultInfo();
				players[i].isReadyForGameplay = 0;
			}

		}
		break;
		case PacketTypes::GameStarted:
		{
			gameStarted = 1;
		}
		break;
		default:
			break;
		}
	}
	else
	{
		delete newPacket;
	}
}

void ServerConnect::serverLoop()
{
	while (!goodConnect)
	{
		receiveDataTCP();
	}
	receiveDataTCP();
}

int ServerConnect::getClientID()
{
	return ourID;
}

double ServerConnect::getClientTickets()
{
	return *clientTicketsDelay;
}

void ServerConnect::setClientTickets(double t)
{
	*clientTicketsDelay = t;
}

void ServerConnect::setGameTicketsPointer(double* delay, double* tick, double* DT)
{
	clientTicketsDelay = delay;
	clientTickets = tick;
	dt = DT;
}

void ServerConnect::setEnemyManagerPointer(EnemyManager* em)
{
	eM = em;
}

void ServerConnect::setPlayersPointer(Player* p)
{
	players = p;
}

void ServerConnect::correctDelay(double serverTickets)
{

}

void ServerConnect::SetTextPing(Text* t)
{
	pingText = t;
}

void ServerConnect::RefreshPing(bool secondTime, double serverTickets)
{
	static double clientTFirst = 0;
	if (!secondTime)
	{
		if (pingChecked)
		{
			pingChecked = 0;
			clientTFirst = *clientTickets;
			Packet p;
			p << PacketTypes::RefreshPing << getClientID();
			sendDataTCP(p);
		}
	}
	else
	{
		double clientTSecond = *clientTickets;

		double diffClientTickets = clientTSecond - clientTFirst;
		double diffClientServerTickets = (clientTSecond - serverTickets);

		double serverPing = diffClientTickets - *dt;

			*clientTicketsDelay -= diffClientServerTickets;

		*Ping = (diffClientTickets * 1000);

		pingChecked = 1;
	}
}

void ServerConnect::setInitialTimeGame(chrono::system_clock::time_point x)
{
	gameStartTime = x;
}

double* ServerConnect::getGameTickets()
{
	return clientTicketsDelay;
}

void ServerConnect::setMyID(int* id)
{
	*id = ourID;
}

void ServerConnect::setPing(int* ping)
{
	Ping = ping;
}

ServerConnect::ServerConnect()
{
	this->serverPort = 55000;
	this->serverPortUDP = 55002;
	this->serverIP = IpAddress::getLocalAddress();
	clientTime = new Clock();
	string ip;
	cout << "Podaj ip servera: "; cin >> ip;
	cout << "Podaj port servera: "; cin >> serverPort;
	serverIP = IpAddress(ip);

	//serverIP = IpAddress("2.tcp.eu.ngrok.io");
	//cout << "Podaj port servera: "; cin >> serverPort;

	goodConnect = 0;
	timeEs = 0;
	pingChecked = 1;
	gameStarted = 0;
	gameLose = 0;
}

bool ServerConnect::connectToServer()
{
	ourID = NULL;
	if (this->server.connect(serverIP, serverPort) == Socket::Done)
	{
		cout << "Polaczono z serwerem: " << serverIP << ":" << serverPort << " Na porcie: " << server.getRemotePort() << endl;

		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			clients[i] = NULL;
		}

		server.setBlocking(false);
		this->serverLoop();
		return true;
	}
	else
	{
		cout << "Brak polaczenia z serwerem." << endl;
		return false;
	}
}

void ServerConnect::updateServerConnect()
{
	serverLoop();
}

void ServerConnect::gameHandleInput(GameHandleInputKeyboard gHIK)
{
	Packet p;
	switch (gHIK)
	{
	case Keyboard_W:
	{
		p << PacketTypes::Keyboard_W_Clicked << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_S:
	{
		p << PacketTypes::Keyboard_S_Clicked << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_A:
	{
		p << PacketTypes::Keyboard_A_Clicked << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_D:
	{
		p << PacketTypes::Keyboard_D_Clicked << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_W_Rel:
	{
		p << PacketTypes::Keyboard_W_Relesed << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_S_Rel:
	{
		p << PacketTypes::Keyboard_S_Relesed << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_A_Rel:
	{
		p << PacketTypes::Keyboard_A_Relesed << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_D_Rel:
	{
		p << PacketTypes::Keyboard_D_Relesed << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_R:
	{
		p << PacketTypes::Keyboard_R_Clicked << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_R_Rel:
	{
		p << PacketTypes::Keyboard_R_Relesed << getClientID();
		sendDataTCP(p);
	}
	break;
	case Keyboard_F5:
	{
		p << PacketTypes::Keyboard_F5_Clicked << getClientID();
		sendDataTCP(p);
	}
	break;
	default:
		break;
	}
}

void ServerConnect::getGameHandleInputMouse(GameHandleInputMouse gHIM, Vector2f pos)
{
	switch (gHIM)
	{
	case GameHandleInputMouse::MouseClicked_Left:
	{
		Packet p;
		p << PacketTypes::MouseClickLeft << getClientID();
		sendDataTCP(p);
	}
	break;
	case GameHandleInputMouse::MouseRelesed_Left:
	{
		Packet p;
		p << PacketTypes::MouseRelesedLeft << getClientID();
		sendDataTCP(p);
	}
	break;
	case GameHandleInputMouse::MouseClicked_Right:
		break;
	case GameHandleInputMouse::MouseChangeAngle:
	{
		Packet p;
		p << PacketTypes::PlayerAngleChange << getClientID() << pos.x;
		sendDataTCP(p);
	}
	break;
	default:
		break;
	}
}
