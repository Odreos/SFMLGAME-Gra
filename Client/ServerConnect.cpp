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

			cout << "Dolaczyl gracz ID: " << newClientID << " pos: " << pos.x << " " << pos.y << endl;
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
			cout << "Dolaczono do serwera, moje id: " << ourID << endl;
			clients[id] = id;
			players[id].setOnline(true);
			players[id].setID(id);
			players[id].setPlayerTxt(*plrTXT);
			players[id].weapon.isLaserOn = 1;

			Packet p;
			p << UDPPort << 55002;
			sendDataTCP(p);
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
			cout << "Nowy gracz: " << item << " pos: " << pos.x << " " << pos.y << endl;

		}
		break;
		case PacketTypes::Disconect:
		{
			int id;
			*newPacket >> id;
			cout << "Klient: " << id << " odlaczyl sie." << endl;
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
			//timeEs = static_cast <double>(clock()) / CLOCKS_PER_SEC;
			//tab[0] = serverConnectTimer.now();
			//timeServerClient[0] = serverTickets;
			//timeServerClient2[0] = serverTickets;
			//timeServerClient[1] = timeEs;

			Packet p;
			p << PacketTypes::Ping << getClientID();
			sendDataTCP(p);
		}
		break;
		case PacketTypes::Ping:
		{
			//static int i = 0;
			//static int j = 1; // 3 // 5 // 7 
			//float serverTickets;
			//*newPacket >> serverTickets;
			//float oldTickets = getClientTickets();
			//float diffTickets = fabs(serverTickets - oldTickets); 
			//float newClientTicket = serverTickets + diffTickets / 2;
			//cout << "Server T:" << serverTickets << " Client T: " << oldTickets << " diff: "
			//	 << diffTickets << " newClient T: " << newClientTicket << " (ms) " << (newClientTicket - serverTickets)*1000<< endl;
			//setClientTickets(newClientTicket);
			//if (i < 5)
			//{
			//	Packet p;
			//	p << PacketTypes::Ping << getClientID();
			//	sendDataTCP(p);
			//	i++;
			//}
			//else
			//{
			//	float time2 = static_cast <double>(clock()) / CLOCKS_PER_SEC;
			//	cout << "DIFFFF: " << time2 - timeEs << endl;
			//	goodConnect = 1;
			//}
			//timeServerClient[j + 1] = serverTickets;
			//timeServerClient[j + 2] = timeEs;

			//timeEs = static_cast <double>(clock()) / CLOCKS_PER_SEC;


			//tab[i + 1] = serverConnectTimer.now();
			//timeServerClient2[i + 1] = serverTickets;

			//if (i < 4)
			//{
			//	Packet p;
			//	p << PacketTypes::Ping << getClientID();
			//	sendDataTCP(p);
			//	i++;
			//	j += 2;
			//}
			//else
			//{
			//	//double avgDelay = 0;
			//	//for (int x = 0; x < 9; x += 2)
			//	//{
			//	//	cout << "Server T: " << timeServerClient[x] << " Client Clock: " << timeServerClient[x + 1] << endl;
			//	//	avgDelay += timeServerClient[x] - timeServerClient[x + 1];
			//	//}
			//	//cout << "AvgDelay: " << avgDelay / 5 << endl;
			//	//cout << "Ping Server: " << pingServer / 5 << endl;
			//	//cout << "Ping Client: " << pingClient / 5 << endl;
			//	//setClientTickets((avgDelay / 5));
			//	double chronoPing[4];
			//	for (int x = 0; x < 4; x++)
			//	{
			//		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(tab[x+1] - tab[x]);
			//		chronoPing[x] = time_span.count() / 2;
			//	}

			//	for (int x = 0; x < 4; x++)
			//	{
			//		cout << "Chrono delay: " << chronoPing[x] << endl;
			//	}
			//	chrono::duration<double> time_span_zero = chrono::duration_cast<chrono::duration<double>>(tab[0] - gameStartTime);
			//	//for (int x = 0; x < 4; x++)
			//	//{
			//	//	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(tab[x] - gameStartTime);
			//	//	timeServerClientDelta[x] = timeServerClient2[x] - time_span.count();
			//	//	timeServerClientDelta[x] += chronoPing[x];
			//	//}

			//	chrono::duration<double> time_span_one = chrono::duration_cast<chrono::duration<double>>(tab[1] - gameStartTime);
			//	chrono::duration<double> time_span_two = chrono::duration_cast<chrono::duration<double>>(tab[2] - gameStartTime);
			//	chrono::duration<double> time_span_three = chrono::duration_cast<chrono::duration<double>>(tab[3] - gameStartTime);
			//	chrono::duration<double> time_span_four = chrono::duration_cast<chrono::duration<double>>(tab[4] - gameStartTime);
			//	timeServerClientDelta[0] = timeServerClient2[1] - time_span_one.count();
			//	timeServerClientDelta[0] += chronoPing[0];

			//	timeServerClientDelta[1] = timeServerClient2[2] - time_span_two.count();
			//	timeServerClientDelta[1] += chronoPing[1];

			//	timeServerClientDelta[2] = timeServerClient2[3] - time_span_three.count();
			//	timeServerClientDelta[2] += chronoPing[2];

			//	timeServerClientDelta[3] = timeServerClient2[4] - time_span_four.count();
			//	timeServerClientDelta[3] += chronoPing[3];

			//	sort(timeServerClientDelta, timeServerClientDelta+4);

			//	for (int x = 0; x < 4; x++)
			//		cout << "Delta: " << timeServerClientDelta[x] << endl;

			//	double mediana = (timeServerClientDelta[1] + timeServerClientDelta[2]) / 2;

			//	double sredniaArytmetyczna = (timeServerClientDelta[0] + timeServerClientDelta[1] + timeServerClientDelta[2] + timeServerClientDelta[3]) / 4;

			//	cout << "Srednia atytmetyczna: " << sredniaArytmetyczna << endl;

			//	double odchylenieStandardowe = sqrtf(((powf(timeServerClientDelta[0] - sredniaArytmetyczna, 2) + powf(timeServerClientDelta[1] - sredniaArytmetyczna, 2) + powf(timeServerClientDelta[2] - sredniaArytmetyczna, 2) + powf(timeServerClientDelta[3] - sredniaArytmetyczna, 2)) / 4));

			//	double sredniaArytmetycznaPoprawna = 0;

			//	int poprawneLiczby = 0;

			//	cout << "Odchylenie standardowe: " << odchylenieStandardowe << endl;

			//	for (int x = 0; x < 4; x++)
			//	{
			//		if (timeServerClientDelta[x] < (mediana+odchylenieStandardowe))
			//		{
			//			poprawneLiczby += 1;
			//			sredniaArytmetycznaPoprawna += timeServerClientDelta[x];
			//		}
			//	}
			//	if (poprawneLiczby == 0)
			//	{
			//		cout << "nie dizleimy przez 0" << endl;
			//		return;
			//	}
			//	else
			//		cout << "Poprawne liczby: " << poprawneLiczby << endl;
			//	sredniaArytmetycznaPoprawna /= poprawneLiczby;

			//	setClientTickets(sredniaArytmetycznaPoprawna);

			//	cout << "Poprawny ping: " << sredniaArytmetycznaPoprawna << endl;

			//	goodConnect = 1;
			//}

			static int y = 0;
			double serverTickets;
			*newPacket >> serverTickets;
			if (y == 1)
			{
				PingServerTickets[1] = serverTickets;
				PingServerDelay[1] = serverConnectTimer.now();

				double serverTicketsDiff = PingServerTickets[1] - PingServerTickets[0];
				chrono::duration<double> ClientPingDiff = chrono::duration_cast<chrono::duration<double>>(PingServerDelay[1] - PingServerDelay[0]);
				
				cout << "Ping 2: " << PingServerTickets[1] << " Ping 1: " << PingServerTickets[0] << endl;
				cout << "Diff ping: SVR(" << serverTicketsDiff * 1000 << " ms) CL(" << ClientPingDiff.count() * 1000 << " ms)" << endl;
				double ping = PingServerTickets[1] + (ClientPingDiff.count() /2);
				cout << "Ping: " << ping << endl;

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
		case PacketTypes::CreateBall:
		{
			double serverTicket;
			*newPacket >> serverTicket;
			int pointID;
			*newPacket >> pointID;
			Vector2f pos;
			*newPacket >> pos.x >> pos.y;
			float diff = *clientTickets - serverTicket;
			//pos *= diff;

			//cout << "GT: " << (*clientTickets + *clientTicketsDelay) << " ST " << serverTicket << endl;
			//cout << "diff " << diff << " POS " << pos.x << " " << pos.y << endl;

			//cout << "KLIK! Server Ticket: " << serverTicket << " Client Ticket: " << *clientTickets << " Diff: " << *clientTickets - serverTicket << endl;

			//cout << "Tworze kulke. Moje T: " << getClientTickets() << " sT: " << serverTicket << endl;

			//createBall(pos, ballID);

			cout << "Create point: " << pointID << " ST: " << serverTicket << " CT: " << *clientTickets << " Diff: " << diff << endl;

			Vector2f pos2;
			Vector2f velo({ 0,100 });
			pos2.x = pos.x + (velo.x * diff);
			pos2.y = pos.y + (velo.y * diff);

			MovePoint* mP = new MovePoint(pos2);
			mP->setID(pointID);
			mP->setVelo(velo);
			movePoints->push_back(mP);
		}
		break;
		case PacketTypes::ChangeBallColor:
		{
			int ballID;
			*newPacket >> ballID;

			cout << "Zmiana koloru ID: " << ballID << " Pos(" << getBallByID(ballID)->ball.getPosition().x << ", " << getBallByID(ballID)->ball.getPosition().y << ")" << endl;

		}
		break;
		case PacketTypes::DeletePoint:
		{

			double serverTicket;
			*newPacket >> serverTicket;
			int pointID;
			*newPacket >> pointID;

			//MovePoint* mP2 = getMovePointByID(pointID);

			//cout << "Delete point: " << pointID << " ST: " << serverTicket << " CT: " << *clientTickets << " Pos( " << mP2->getPos().x << "," << mP2->getPos().y << ")" << endl;

			//movePoints->erase(remove_if(movePoints->begin(), movePoints->end(), [pointID](MovePoint* mP) {return mP->getID() == pointID; }), movePoints->end());

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
				//cout << "Diff: " << diff << " 1pos:(" << pos.x << "," << pos.y << ") ";
				//pos.x *= diff;
				//pos.y *= diff;
				//cout << "2pos:(" << pos.x << "," << pos.y << ") " << endl;

				cout << "Player " << playerID << " is moving. Ct: " << *clientTickets << " St: " << serverTickets << " diff: " << *clientTickets - serverTickets << endl;

				players[playerID].setMovingState(true);
				players[playerID].setDir(x);
				players[playerID].setPos(pos);
				//players[playerID].SetCorrectPosByDT(diff/2);
				//players[playerID].setPos(pos);
			}
			else
			{
				int playerID;
				*newPacket >> playerID;
				Vector2f pos;
				*newPacket >> pos.x >> pos.y;

				cout << "Poprawka gracza: " << playerID << " z: (" << players[playerID].getPos().x << "," << players[playerID].getPos().y
					<< ") na: (" << pos.x << "," << pos.y << ") diff: (" 
					<< players[playerID].getPos().x - pos.x << "," << players[playerID].getPos().y - pos.y << ")" << endl;

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
		case PacketTypes::CreateBullet:
		{
			double serverTickets;
			*newPacket >> serverTickets;
			
			int playerID;
			*newPacket >> playerID;

			int entityID;
			*newPacket >> entityID;

			players[playerID].weapon.currentAmmo -= 1;

			Vector2f bPos;
			*newPacket >> bPos.x >> bPos.y;

			Vector2f dir;
			*newPacket >> dir.x >> dir.y;

			Bullet* b = new Bullet;
			b->SetDirection(dir);
			b->SetID(entityID);
			b->SetOwnerID(playerID);
			b->SetPos(bPos);

			bullets->push_back(*b);
		}
		break;
		case PacketTypes::ClearBulletVector:
		{
			bullets->clear();
		}
		break;
		case PacketTypes::SetPlayerPosition:
		{
			int playerID;
			*newPacket >> playerID;
			Vector2f pos;
			*newPacket >> pos.x >> pos.y;
			players[playerID].setPos(pos);
			//cout << "SetPlayerPos: " << playerID << " pos(" << pos.x << ", " << pos.y << ")" << endl;
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
		case PacketTypes::DeleteBullet:
		{

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
		case PacketTypes::SetLaserPointPlayer:
		{
			int playerID;
			*newPacket >> playerID;
			Vector2f point;
			*newPacket >> point.x >> point.y;

			players[playerID].weapon.laserPoint = point;
			cout << "Laser point: " << point.x << " " << point.y << endl;
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

			//cout << "Create enemy:" << endl;
			//cout << "Server Ticket: " << serverTicket << endl;
			//cout << "Enemy ID: " << eID << endl;
			//cout << "Enemy Pos: " << ePos.x << " " << ePos.y << endl;
			//cout << "Enemy Vec Size: " << tileIDSize << endl;

			for (int i = 0; i < tileIDSize; i++)
			{
				int es;
				*newPacket >> es;
				tileID.push_back(es);

				//cout << "Tile id." << i << " val: " << es << endl;
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

void ServerConnect::receiveDataUDP()
{
	Packet p;
	if (serverUDP.receive(p, serverIP, serverPortUDP) == Socket::Done)
	{
		cout << "receinve" << endl;
		int packetType;
		p >> packetType;
		switch (static_cast<PacketTypes> (packetType))
		{
		case PacketTypes::SetPlayerPosition:
		{
			int id;
			p >> id;
			cout << "Odebrane UPD: " << id << endl;
		}
		break;
		default:
			break;
		}
	}
}

void ServerConnect::serverLoop()
{
	while (!goodConnect)
	{
		receiveDataTCP();
		receiveDataUDP();
	}
	receiveDataTCP();
	receiveDataUDP();
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

void ServerConnect::setBallsPointer(vector<Ball>* b)
{
	balls = b;
}

void ServerConnect::setMovePointsPointer(vector<MovePoint*>* moveP)
{
	movePoints = moveP;
}

void ServerConnect::setEnemyManagerPointer(EnemyManager* em)
{
	eM = em;
}

void ServerConnect::setBulletsPointer(vector<Bullet>* b)
{
	bullets = b;
}

void ServerConnect::setPlayersPointer(Player* p)
{
	players = p;
}

void ServerConnect::createBall(Vector2f pos, int id)
{
	Ball* b = new Ball;
	b->setPos(pos);
	b->setID(id);
	balls->push_back(*b);
}

void ServerConnect::correctDelay(double serverTickets)
{
}

Ball* ServerConnect::getBallByID(int ID)
{
	for (auto& b : *balls)
	{
		if (b.getID() == ID)
			return &b;
	}
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

		//*clientTickets = serverTickets + diffClientTickets / 2;

		//if (*clientTicketsDelay > serverTickets)
			*clientTicketsDelay -= diffClientServerTickets;

		*Ping = (diffClientTickets * 1000);

		pingChecked = 1;
	}
}

MovePoint* ServerConnect::getMovePointByID(int ID)
{
	for (auto& b : *movePoints)
	{
		if (b->getID() == ID)
			return b;
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
	//string ip;
	//cout << "Podaj ip servera: "; cin >> ip;
	//cout << "Podaj port servera: "; cin >> serverPort;
	//serverIP = IpAddress(ip);

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
		if (serverUDP.bind(serverPortUDP) == Socket::Done)
		{
			cout << "UDP socket bind: " << serverPortUDP << endl;
		}
		serverUDP.setBlocking(false);
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
	case Keyboard_Space:
	{
		p << PacketTypes::Keyboard_Space_Clicked << getClientID();
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
