#include "Server.hpp"

void Server::addNewClient()
{
	TcpSocket* newClient = new TcpSocket;

	if (server.accept(*newClient) == Socket::Done)
	{
		Packet p;

		//znajdz wolne id
		int freeID = getFreeID();
		if (freeID == -1)
		{
			p << PacketTypes::ServerFull;
			newClient->send(p);
			newClient->disconnect();
			cout << "Proba polaczenia nowego klienta, serwer pelny." << endl;
			return;
		}

		int newClientID = freeID;
		newClient->setBlocking(false);
		clients[newClientID] = newClient;

		players[newClientID].setOnline(true);
		players[newClientID].clientID = newClientID;
		players[newClientID].setID(newClientID);
		players[newClientID].setPos({ 1056.f,776.f });

		cout << "Nowy klient: " << newClient->getRemoteAddress().getPublicAddress() << ":" << newClient->getRemotePort() << " ID: " << newClientID << endl;
		clientsID++;

		p.clear();
		p << PacketTypes::SetID << newClientID;
		sendPackets(&p, newClientID, SendPacketsType::OnlyOne); // ustaw nowe id dla nowego clienta

		p.clear();
		p << PacketTypes::NewConnect << newClientID << players[newClientID].getPos().x << players[newClientID].getPos().y;
		sendPackets(&p, newClientID, SendPacketsType::WithoutOne); // powiedz innym ze dolaczyl nowy client

		//list<int>* newListOfCliends = new list<int>;
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (players[i].getOnline())
			{
				p.clear();
				p << PacketTypes::SetPlayerPos << i << players[i].getPos().x << players[i].getPos().y << players[i].readyForGameplay;// TODO dodaj rotacje graczy
				sendPackets(&p, newClientID, SendPacketsType::OnlyOne);
			}
		}


		p.clear();
		p << PacketTypes::SetTickets << getServerTickets();
		sendPackets(&p, newClientID, SendPacketsType::OnlyOne); // wyslij nowemu clientowi tickety
	}
	else
	{
		delete newClient;
	}
}

void Server::receiveData()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (clients[i] != nullptr)
		{
			Socket::Status status;
			Packet newPacket;
			status = clients[i]->receive(newPacket);
			switch (status)
			{
			case Socket::Status::Disconnected:
			{
				cout << "Klient odlaczyl sie od serwera. Jego ID: " << i << endl;
				Packet p;
				p << PacketTypes::Disconect << i;
				clients[i]->disconnect();
				clients[i] = NULL;
				players[i].setOnline(false);
				players[i].weapon.SetDefaultInfo();
				players[i].readyForGameplay = 0;
				sendPackets(&p, NULL, SendPacketsType::All);
			}
			break;
			case Socket::Status::Done:
			{
				PacketTypes pT;
				int pTINT = -1;
				newPacket >> pTINT;
				pT = static_cast<PacketTypes>(pTINT);
				switch (pT)
				{
				case PacketTypes::Ping:
				{
					int clientID;
					newPacket >> clientID;
					Packet p;
					p << PacketTypes::Ping << getServerTickets();
					sendPackets(&p, clientID, SendPacketsType::OnlyOne);
				}
				break;
				case PacketTypes::MouseClickLeft:
				{
					int clientID;
					newPacket >> clientID;

					players[clientID].weapon.shooting = true;

					Packet p;
					p << PacketTypes::PlayerIsShooting << clientID << true;
					sendPackets(&p, NULL, SendPacketsType::All);

				}
				break;
				case PacketTypes::Keyboard_W_Clicked:
				{
					int playerID;
					newPacket >> playerID;
					players[playerID].setMovingState(true);
					players[playerID].setDir(PlayerDirection::MoveUp);

					Packet p;
					p << PacketTypes::SetPlayerMovingState << true << getServerTickets() << playerID << PlayerDirection::MoveUp << players[playerID].getPos().x << players[playerID].getPos().y;
					sendPackets(&p, NULL, SendPacketsType::All);
				}
				break;
				case PacketTypes::Keyboard_S_Clicked:
				{
					int playerID;
					newPacket >> playerID;
					players[playerID].setMovingState(true);
					players[playerID].setDir(PlayerDirection::MoveDown);

					Packet p;
					p << PacketTypes::SetPlayerMovingState << true << getServerTickets() << playerID << PlayerDirection::MoveDown << players[playerID].getPos().x << players[playerID].getPos().y;
					sendPackets(&p, NULL, SendPacketsType::All);
				}
				break;
				case PacketTypes::Keyboard_A_Clicked:
				{
					int playerID;
					newPacket >> playerID;
					players[playerID].setMovingState(true);
					players[playerID].setDir(PlayerDirection::MoveLeft);

					Packet p;
					p << PacketTypes::SetPlayerMovingState << true << getServerTickets() << playerID << PlayerDirection::MoveLeft << players[playerID].getPos().x << players[playerID].getPos().y;
					sendPackets(&p, NULL, SendPacketsType::All);
				}
				break;
				case PacketTypes::Keyboard_D_Clicked:
				{
					int playerID;
					newPacket >> playerID;
					players[playerID].setMovingState(true);
					players[playerID].setDir(PlayerDirection::MoveRight);

					Packet p;
					p << PacketTypes::SetPlayerMovingState << true << getServerTickets() << playerID << PlayerDirection::MoveRight << players[playerID].getPos().x << players[playerID].getPos().y;
					sendPackets(&p, NULL, SendPacketsType::All);
				}
				break;
				case PacketTypes::Keyboard_W_Relesed:
				{
					int playerID;
					newPacket >> playerID;
					if (players[playerID].getDir() == PlayerDirection::MoveUp)
					{
						players[playerID].setMovingState(false);

						Packet p;
						p << PacketTypes::SetPlayerMovingState << false << playerID << players[playerID].getPos().x << players[playerID].getPos().y;
						sendPackets(&p, NULL, SendPacketsType::All);
					}
				}
				break;
				case PacketTypes::Keyboard_S_Relesed:
				{
					int playerID;
					newPacket >> playerID;
					if (players[playerID].getDir() == PlayerDirection::MoveDown)
					{
						players[playerID].setMovingState(false);

						Packet p;
						p << PacketTypes::SetPlayerMovingState << false << playerID << players[playerID].getPos().x << players[playerID].getPos().y;
						sendPackets(&p, NULL, SendPacketsType::All);
					}
				}
				break;
				case PacketTypes::Keyboard_A_Relesed:
				{
					int playerID;
					newPacket >> playerID;
					if (players[playerID].getDir() == PlayerDirection::MoveLeft)
					{
						players[playerID].setMovingState(false);

						Packet p;
						p << PacketTypes::SetPlayerMovingState << false << playerID << players[playerID].getPos().x << players[playerID].getPos().y;
						sendPackets(&p, NULL, SendPacketsType::All);
					}
				}
				break;
				case PacketTypes::Keyboard_D_Relesed:
				{
					int playerID;
					newPacket >> playerID;
					if (players[playerID].getDir() == PlayerDirection::MoveRight)
					{
						players[playerID].setMovingState(false);

						Packet p;
						p << PacketTypes::SetPlayerMovingState << false << playerID << players[playerID].getPos().x << players[playerID].getPos().y;
						sendPackets(&p, NULL, SendPacketsType::All);
					}
				}
				break;
				case PacketTypes::RefreshPing:
				{
					int playerID;
					newPacket >> playerID;
					Packet p;
					p << PacketTypes::RefreshPing << getServerTickets();
					sendPackets(&p, playerID, SendPacketsType::OnlyOne);
				}
				break;
				case PacketTypes::MouseRelesedLeft:
				{
					int clientID;
					newPacket >> clientID;

					players[clientID].weapon.shooting = false;

					Packet p;
					p << PacketTypes::PlayerIsShooting << clientID << false;
					sendPackets(&p, NULL, SendPacketsType::All);
				}
				break;
				case PacketTypes::PlayerAngleChange:
				{
					int clientID;
					newPacket >> clientID;
					float angle;
					newPacket >> angle;

					players[clientID].setPlayerAngle(angle);
					Packet p;
					p << PacketTypes::PlayerAngleChange << clientID << angle;
					sendPackets(&p, NULL, SendPacketsType::All);
				}
				break;
				case PacketTypes::Keyboard_R_Clicked:
				{
					int clientID;
					newPacket >> clientID;
					if (players[clientID].weapon.SetForceToReload())
					{
						Packet pack;
						pack << PacketTypes::SetPlayerReload << clientID << true;
						sendPackets(&pack, NULL, SendPacketsType::All);
					}
				}
				break;
				case PacketTypes::Keyboard_F5_Clicked:
				{
					int clientID;
					newPacket >> clientID;

					players[clientID].readyForGameplay = !players[clientID].readyForGameplay;

					Packet pack;
					pack << PacketTypes::SetPlayerStatusForGameplay << clientID << players[clientID].readyForGameplay;
					sendPackets(&pack, NULL, SendPacketsType::All);

					if (!isGameOn)
					{
						bool startGame = 1;
						for (auto& p : players)
						{
							if (p.getOnline())
								if (!p.readyForGameplay)
									startGame = 0;
						}
						if (startGame)
							StartGamePlay();
					}
				}
				break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
	}
}

int Server::getFreeID()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (!players[i].isOnline)
			return i;
	}
	return -1;
}

double Server::getServerTickets()
{
	return serverTickets;
}

void Server::sendPackets(Packet* p, int clientID, SendPacketsType type)
{
	if (type == SendPacketsType::All) // send to all clients
	{

		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (clients[i] != nullptr)
				if (clients[i] != NULL)
					clients[i]->send(*p);
		}
	}
	else if (type == SendPacketsType::WithoutOne) //send to all clients without this one
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (clients[i] != nullptr)
				if (i != clientID)
				{
					clients[i]->send(*p);
				}
		}
	}
	else if (type == SendPacketsType::OnlyOne) // send to this one client
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (clients[i] != nullptr)
				if (i == clientID)
				{
					clients[i]->send(*p);
					break;
				}
		}
	}
}

float Server::GetLenghtVector(Vector2f v)
{
	return sqrtf(pow(v.x, 2) + pow(v.y, 2));
}

float Server::determinant(Vector2f& x1, Vector2f& x2)
{
	return (x1.y * x2.x - x1.x * x2.y);
}

array<Vector2f, 4>& Server::GetVertices(RectangleShape& r)
{
	array<Vector2f, 4> VertexArray;
	Transform transform = r.getTransform();
	for (int i = 0; i < r.getPointCount(); ++i)
	{
		VertexArray[i] = transform.transformPoint(r.getPoint(i));
	}
	return VertexArray;
}

void Server::GetRaycast(RectangleShape& wall, Player& p, Vector2f mousePos)
{
	Vector2f pPos = p.getPos();
	array<Vector2f, 4> wallVertices = GetVertices(wall);

	bool findPoint = 0;
	//wallVertices[0] top left
	//wallVertices[1] top right
	//wallVertices[2] down right
	//wallVertices[3] down left

	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
		{
			float x1 = wallVertices[3].x;
			float y1 = wallVertices[3].y;

			float x2 = wallVertices[0].x;
			float y2 = wallVertices[0].y;

			float x3 = pPos.x;
			float y3 = pPos.y;

			float x4 = mousePos.x;
			float y4 = mousePos.y;

			float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
			if (den == 0) { continue; }
			float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
			float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

			if (t > 0 && t < 1 && u>0)
			{
				Vector2f pES;
				pES.x = (x1 + t * (x2 - x1));
				pES.y = (y1 + t * (y2 - y1));
				float len = GetLenghtVector({ pES.x - x3, pES.y - y3 });
				
				p.pointsOfLaserEndWalls[len] = pES;
				findPoint = 1;
				if (p.lenghtForWalls == 0)
				{
					p.lenghtForWalls = len;
					p.WallPlayerLookAt = &wall;
				}
				else if (p.lenghtForWalls >= len)
				{
					p.lenghtForWalls = len;
					p.WallPlayerLookAt = &wall;
				}
			}

		}


		float x1 = wallVertices[i].x;
		float y1 = wallVertices[i].y;

		float x2 = wallVertices[i + 1].x;
		float y2 = wallVertices[i + 1].y;

		float x3 = pPos.x;
		float y3 = pPos.y;

		float x4 = mousePos.x;
		float y4 = mousePos.y;

		float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0) { continue; }
		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0 && t < 1 && u>0)
		{
			Vector2f pES;
			pES.x = (x1 + t * (x2 - x1));
			pES.y = (y1 + t * (y2 - y1));
			float len = GetLenghtVector({ pES.x - x3, pES.y - y3 });
			p.pointsOfLaserEndWalls[len] = pES;
			findPoint = 1;

			if (p.lenghtForWalls == 0)
			{
				p.lenghtForWalls = len;
				p.WallPlayerLookAt = &wall;
			}
			else if (p.lenghtForWalls >= len)
			{
				p.lenghtForWalls = len;
				p.WallPlayerLookAt = &wall;
			}
		}
	}
}

void Server::GetRaycastEnemy(Enemy& e, Player& p, Vector2f mousePos)
{
	Vector2f pPos = p.getPos();
	array<Vector2f, 4> wallVertices = GetVertices(e.enemy);

	bool findPoint = 0;
	//wallVertices[0] top left
	//wallVertices[1] top right
	//wallVertices[2] down right
	//wallVertices[3] down left

	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
		{
			float x1 = wallVertices[3].x;
			float y1 = wallVertices[3].y;

			float x2 = wallVertices[0].x;
			float y2 = wallVertices[0].y;

			float x3 = pPos.x;
			float y3 = pPos.y;

			float x4 = mousePos.x;
			float y4 = mousePos.y;

			float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
			if (den == 0) { continue; }
			float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
			float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

			if (t > 0 && t < 1 && u>0)
			{
				Vector2f pES;
				pES.x = (x1 + t * (x2 - x1));
				pES.y = (y1 + t * (y2 - y1));
				float len = GetLenghtVector({ pES.x - x3, pES.y - y3 });

				p.pointsOfLaserEndBots[len] = pES;
				findPoint = 1;
				if (p.lenghtForBots == 0)
				{
					p.lenghtForBots = len;
					p.EnemyPlayerLookAt = &e;
				}
				else if (p.lenghtForBots >= len)
				{
					p.lenghtForBots = len;
					p.EnemyPlayerLookAt = &e;
				}
			}

		}


		float x1 = wallVertices[i].x;
		float y1 = wallVertices[i].y;

		float x2 = wallVertices[i + 1].x;
		float y2 = wallVertices[i + 1].y;

		float x3 = pPos.x;
		float y3 = pPos.y;

		float x4 = mousePos.x;
		float y4 = mousePos.y;

		float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0) { continue; }
		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

		if (t > 0 && t < 1 && u>0)
		{
			Vector2f pES;
			pES.x = (x1 + t * (x2 - x1));
			pES.y = (y1 + t * (y2 - y1));
			float len = GetLenghtVector({ pES.x - x3, pES.y - y3 });
			p.pointsOfLaserEndBots[len] = pES;
			findPoint = 1;

			if (p.lenghtForBots == 0)
			{
				p.lenghtForBots = len;
				p.EnemyPlayerLookAt = &e;
			}
			else if (p.lenghtForBots >= len)
			{
				p.lenghtForBots = len;
				p.EnemyPlayerLookAt = &e;
			}
		}
	}
}

Vector2f Server::UptadePlayerMousePos(Player& p)
{
	float pAngle = p.getPlayerAngle();

	float lenght = 10.f;

	float pAngleRad = (pAngle-90) / 180 * M_PI;

	Vector2f mousePos = { cosf(pAngleRad) * lenght + p.getPos().x, sinf(pAngleRad) * lenght + p.getPos().y };
	return mousePos;
}

void Server::updateServerByTick(double dt)
{
	for (auto& p : players)
	{
		if (p.getOnline())
		{
			if (p.weapon.shooting)
			{
				p.pointsOfLaserEndWalls.clear();
				p.pointsOfLaserEndBots.clear();
				p.lenghtForWalls = 0;
				p.lenghtForBots = 0;
				p.EnemyPlayerLookAt = nullptr;
				p.WallPlayerLookAt = nullptr;

				p.weapon.mousePos = UptadePlayerMousePos(p);

				Vector2f mousePos = p.weapon.mousePos;

				for (auto& r : tileMap.allTiles)
				{
					if (r.isColiding)
					{
						GetRaycast(r.tile, p, mousePos);
					}
				}

				for (auto& e : enemies)
				{
					GetRaycastEnemy(e, p, mousePos);
				}

				if (p.pointsOfLaserEndBots.size() || p.pointsOfLaserEndWalls.size())
				{
					if (p.pointsOfLaserEndBots.size() > 0 && p.pointsOfLaserEndWalls.size() > 0)
					{
						float l1 = p.pointsOfLaserEndBots.begin()->first;
						float l2 = p.pointsOfLaserEndWalls.begin()->first;

						if (l2 < l1)
						{
							p.laserPoint = p.pointsOfLaserEndWalls.begin()->second;
							p.isWallCloser = 1;
							p.isEnemyCloser = 0;
						}
						else
						{
							p.laserPoint = p.pointsOfLaserEndBots.begin()->second;
							p.isWallCloser = 0;
							p.isEnemyCloser = 1;
						}
					}
					else
					{
						if (p.pointsOfLaserEndWalls.size() > 0)
						{
							p.laserPoint = p.pointsOfLaserEndWalls.begin()->second;
							p.isWallCloser = 1;
							p.isEnemyCloser = 0;
						}
						else
						{
							p.laserPoint = p.pointsOfLaserEndBots.begin()->second;
							p.isWallCloser = 0;
							p.isEnemyCloser = 1;
						}
					}

				}
				else
				{
					p.laserPoint = { 0,0 };
					p.isWallCloser = 0;
					p.isEnemyCloser = 0;
				}

				if (p.weapon.shooting)
				{
					if (p.weapon.Fire())
					{
						Packet packet;
						packet << PacketTypes::PlayerShooted;
						sendPackets(&packet, p.getID(), SendPacketsType::OnlyOne);

						if (p.isEnemyCloser)
						{
							p.EnemyPlayerLookAt->enemyHP -= p.weapon.damage;
						}

						if (p.weapon.currentAmmo == 0)
						{
							Packet pac;
							pac << PacketTypes::SetPlayerReload << p.getID() << true;
							sendPackets(&pac, NULL, SendPacketsType::All);
						}
					}
				}
			}
		}
	}
	GamePlay(dt);
}

void Server::updateServerByNoTick(double dt)
{
	for (auto& p : players)
	{
		if (p.getOnline())
		{
			if (p.getMovingState())
			{

				if (tileMap.RectvsRectCol(p, dt))
				{
					//coll
				}
				else
					p.movePlayer(dt);

			}


			p.weapon.Update(dt);

			if (p.weapon.isReloadingForCheck)
			{
				if (!p.weapon.isReloading)
				{
					p.weapon.isReloadingForCheck = 0;

					Packet packet;
					packet << PacketTypes::SetWeaponInfoAfterReload << p.weapon.currentAmmo << p.weapon.allAmmo;
					sendPackets(&packet, p.getID(), SendPacketsType::OnlyOne);

					packet.clear();
					packet << PacketTypes::SetPlayerReload << p.getID() << false;
					sendPackets(&packet, NULL, SendPacketsType::All);
				}
			}
		}
	}
}

void Server::StartGamePlay()
{
	Packet pack;
	pack << PacketTypes::GameStarted;
	sendPackets(&pack, NULL, SendPacketsType::All);
	pack.clear();
	for (auto& p : players)
	{
		if (p.getOnline())
		{
			pack.clear();
			p.setPos(tileMap.GetTilePosByID(941));

			pack << PacketTypes::SetPlayerPosition << p.playerID << p.getPos().x << p.getPos().y;
			sendPackets(&pack, NULL, SendPacketsType::All);
		}
	}
	isGameOn = 1;
}

void Server::GamePlay(float dt)
{
	if (isGameOn)
	{
		bool lose = 0;
		for (auto& e : enemies)
		{
			if (e.mapTileIDToMove.front() == 941) // TODO zmiana tego tileID
			{
				lose = 1;
			}
		}

		bool isPlayerOnline = 0;
		for (auto& p : players)
		{
			if (p.getOnline())
			{
				isPlayerOnline = 1;
			}
		}

		if (!isPlayerOnline) lose = 1;

		if (lose)
		{
			enemies.clear();
			Packet pack;
			pack << PacketTypes::GameisLose;
			sendPackets(&pack, NULL, SendPacketsType::All);

			for (auto& p : players)
			{
				p.readyForGameplay = 0;
				p.weapon.SetDefaultInfo();
			}
			isGameOn = 0;
		}
		else
		{
			enemies.erase(
				remove_if(
					enemies.begin(),
					enemies.end(),
					[this](Enemy& e)
					{
						if (e.GetEnemyHP() <= 0)
						{
							Packet packet;
							packet << PacketTypes::DeleteEnemy << e.GetID();
							sendPackets(&packet, NULL, SendPacketsType::All);
							return true;
						}
						else
							return false;
					}), enemies.end());


			CreateEnemyByTime(dt);
			eM->Update(dt);
		}
	}
}

void Server::CreateEnemyByTime(float dt)
{
	static float time = 0;
	time += dt;
	if (time > enemyTimeToResp)
	{
		int tileID = (rand() % 95) - 33;

		while (tileMap.GetTileByID(tileID).isColiding)
		{
			tileID = (rand() % 95) - 33;
		}

		CreateEnemy(tileID);

		time -= enemyTimeToResp;
	}
}

void Server::CreateEnemy(int TileID)
{
	Enemy* e = new Enemy();
	e->SetPos(tileMap.GetTilePosByID(TileID));
	e->SetID(entityID);
	e->SetEnemyHP(100);

	tileMap.Solve_AStar(e, 941);
	eM->AddEnemy(e);
	entityID++;

	Packet p;
	p << PacketTypes::CreateEnemy << getServerTickets() << e->GetID() << e->GetPos().x << e->GetPos().y << e->mapTileIDToMoveVector.size();
	for (auto& id : e->mapTileIDToMoveVector)
		p << id;
	sendPackets(&p, NULL, SendPacketsType::All);
}

void Server::CreateEnemies()
{
	Enemy* e = new Enemy();
	e->SetPos({ 1020.f, 750.f });
	e->SetID(entityID);
	e->SetEnemyHP(100);
	eM->AddEnemy(e);
	entityID++;
}

void Server::startServer()
{
	static float tickCounter = 0;
	while (true)
	{

		tab[2] = serverTime.now();

		chrono::duration<double> dtCh = chrono::duration_cast<chrono::duration<double>>(tab[2] - tab[1]);

		dt = serverTimer->restart().asSeconds();
		serverTimeBySFMLClock += dt;

		tab[1] = serverTime.now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(tab[1] - tab[0]);
		serverTickets = serverTimeBySFMLClock;
		tickCounter = 0;

		static float refreshByTicks = 0;
		refreshByTicks += dt;

		updateServerByNoTick(dt);
		addNewClient();
		receiveData();
		if (refreshByTicks >= serverTick)
		{
			updateServerByTick(refreshByTicks);
			refreshByTicks -= serverTick;
		}
	}
}

Server::Server()
{
	srand(time(NULL));
	tab[0] = serverTime.now();
	entityID = 0;
	serverPort = 55000;
	clientsID = 0;
	isGameOn = 0;
	do
	{
		cout << "Podaj port: "; cin >> serverPort;
	} while (server.listen(serverPort) != Socket::Done);

	system("cls");
	//cout << "Serwer dziala. IP: " << serverIP << ":" << serverPort << endl;
	//cout << "IP lokalne: " << IpAddress::getLocalAddress() << endl;
	//cout << "IP globalne: " << IpAddress::getPublicAddress() << endl;
	//cout << "Port: " << serverPort << endl;

	cout << "Server TCP zostal uruchomiony na porcie: "<< serverPort << endl;
	server.setBlocking(false);
	udpSocket.setBlocking(false);

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		clients[i] = nullptr;
	}

	startRespEnemy = 0;
	serverTickets = 0;
	serverTimer = new Clock;
	serverTimeBySFMLClock = 0;
	eM = new EnemyManager(&enemies);
	this->startServer();
}
