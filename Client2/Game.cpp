#include "Game.hpp"

Game::Game()
{
    gameTicketsDelay = 0;
    gameTickets = 0;
    dt = 0;
    server = new ServerConnect;
    clientTimeBySFMLClock = 0;

    f.loadFromFile(GAME_FONT);
    gameInfo.setFont(f);
    gameInfo.setFillColor(Color::Green);
    gameInfo.setPosition({ 0,0 });
    gameInfo.setCharacterSize(100);
    showGameInfo = 0;

    playertxt.loadFromFile(PLAYER_PNG);
    zombitxt.loadFromFile(ZOMBI_PNG);
    eM = new EnemyManager(&enemies);
    server->setEnemyManagerPointer(eM);
    server->SetTextPing(&textPing);
    server->plrTXT = &playertxt;
    server->zombiTXT = &zombitxt;
    server->setGameTicketsPointer(&gameTicketsDelay, &gameTickets, &dt);
    server->setPlayersPointer(&players[0]);
    server->setInitialTimeGame(tab[0]);
    server->setPing(&ping);
    if (!server->connectToServer())
    {
        cout << "Brak polaczenia" << endl;
        return;
    }
    timer = new Clock;
    tab[0] = gameTime.now();
    server->setMyID(&myID);

    pGUI = new PlayerGUI(&players[myID]);
    pGUI->setFont(f);
    pGUI->setViewPos({100,100});

    focus = 1;
    startGame();
}

void Game::startGame()
{
    gameLoop();
}

void Game::gameLoop()
{
    window.create(VideoMode(WINDOW_X, WINDOW_Y), "My window");

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::LostFocus)
                focus = 0;
            if (event.type == Event::GainedFocus)
                focus = 1;
        }

        tab[2] = gameTime.now();

        chrono::duration<double> dtCh = chrono::duration_cast<chrono::duration<double>>(tab[2] - tab[1]);

        float oldDt = dt;

        dt = timer->restart().asSeconds();
        clientTimeBySFMLClock += dt;
        static double refreshPing = 0;
        refreshPing += dt;

        if (refreshPing > 0.3)
        {
            fps = dt;
            if (server->pingChecked)
            {
                server->RefreshPing(false, 0);
                refreshPing = 0;
            }
        }

        if (server->gameLose)
        {
            showGameInfo = 1;
            gameInfo.setFillColor(Color::Red);
            gameInfo.setString("Game lost");
            server->gameLose = 0;
        }
        if (server->gameStarted)
        {
            showGameInfo = 1;
            gameInfo.setFillColor(Color::Green);
            gameInfo.setString("Game start");
            server->gameStarted = 0;
        }
        if (showGameInfo)
        {
            float showGameInfoTime = 1.5;
            static float showGameInfoTimeDT = 0;
            showGameInfoTimeDT += dt;

            Vector2f pPos = players[myID].getPos();

            Vector2f textPos = { pPos.x - 120, pPos.y - 50 };
            gameInfo.setPosition(textPos);
            if (showGameInfoTimeDT > showGameInfoTime)
            {
                showGameInfoTimeDT = 0;
                showGameInfo = 0;
            }
        }

        tab[1] = gameTime.now();

        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(tab[1] - tab[0]);

        gameTickets = clientTimeBySFMLClock;
        gameTickets += gameTicketsDelay;


        static float refreshByTicks = 0;
        refreshByTicks += dt;
        updateByNoTick(dt);
        handleInputByNoTick();
        if (refreshByTicks >= serverTick)
        {
            handleInput();
            refreshByTicks -= serverTick;
        }
        draw();
    }
}

void Game::handleInput()
{
    static bool Clicked_Mouse_Left = 0;
    Vector2i pixelPos = Mouse::getPosition(window);
    static Vector2f mousePosStatic = window.mapPixelToCoords(pixelPos);
    static Vector2f mousePosStaticForAngle = window.mapPixelToCoords(pixelPos);
    if (focus)
    {
        Vector2f mousePos = window.mapPixelToCoords(pixelPos);

        if (mousePos.x != mousePosStaticForAngle.x || mousePos.y != mousePosStaticForAngle.y)
        {
            mousePosStaticForAngle = mousePos;
            Vector2f playerPos = players[myID].getPos();
            playerAngle = atan2(mousePos.x - playerPos.x, mousePos.y - playerPos.y) * (180 / M_PI * -1) + 180;

            sendServerInfo(ServerInfo::ChangePlayerAngle);
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (Clicked_Mouse_Left == 0)
            {
                Clicked_Mouse_Left = 1;
                sendServerInfo(ServerInfo::MouseClickedLeft1);
            }
        }
        else
        {
            if (Clicked_Mouse_Left == 1)
            {
                if (players[myID].weapon.shooting)
                    players[myID].weapon.shooting = 0;
                Clicked_Mouse_Left = 0;
                sendServerInfo(ServerInfo::MouseRelesedLeft1);
            }
        }
    }
}

void Game::handleInputByNoTick()
{
    static bool Clicked_Key_W = 0;
    static bool Clicked_Key_S = 0;
    static bool Clicked_Key_A = 0;
    static bool Clicked_Key_D = 0;
    static bool Clicked_Key_R = 0;
    static bool Clicked_Key_T = 0;
    static bool Clicked_Key_F1 = 0;
    static bool Clicked_Key_F5 = 0;
    static bool Clicked_Key_Space = 0;

    if (focus)
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            if (Clicked_Key_W == 0)
            {
                Clicked_Key_W = 1;
                sendServerInfo(ServerInfo::Key_W_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_W == 1)
            {
                Clicked_Key_W = 0;
                sendServerInfo(ServerInfo::Key_W_Relesed);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::S))
        {
            if (Clicked_Key_S == 0)
            {
                Clicked_Key_S = 1;
                sendServerInfo(ServerInfo::Key_S_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_S == 1)
            {
                Clicked_Key_S = 0;
                sendServerInfo(ServerInfo::Key_S_Relesed);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::A))
        {
            if (Clicked_Key_A == 0)
            {
                Clicked_Key_A = 1;
                sendServerInfo(ServerInfo::Key_A_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_A == 1)
            {
                Clicked_Key_A = 0;
                sendServerInfo(ServerInfo::Key_A_Relesed);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            if (Clicked_Key_D == 0)
            {
                Clicked_Key_D = 1;
                sendServerInfo(ServerInfo::Key_D_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_D == 1)
            {
                Clicked_Key_D = 0;
                sendServerInfo(ServerInfo::Key_D_Relesed);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::F1))
        {
            if (!Clicked_Key_F1)
            {
                pGUI->drawElements = !pGUI->drawElements;
            }
            Clicked_Key_F1 = 1;
        }
        else
        {
            Clicked_Key_F1 = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::R))
        {
            if (Clicked_Key_R == 0)
            {
                players[myID].weapon.SetReloading(true);
                Clicked_Key_R = 1;
                sendServerInfo(ServerInfo::Key_R_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_R == 1)
            {
                Clicked_Key_R = 0;
                sendServerInfo(ServerInfo::Key_R_Relesed);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            if (Clicked_Key_Space == 0)
            {
                Clicked_Key_Space = 1;
                sendServerInfo(ServerInfo::Key_Space_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_Space == 1)
            {
                Clicked_Key_Space = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::F5))
        {
            if (Clicked_Key_F5 == 0)
            {
                Clicked_Key_F5 = 1;
                sendServerInfo(ServerInfo::Key_F5_Clicked);
            }
        }
        else
        {
            if (Clicked_Key_F5 == 1)
            {
                Clicked_Key_F5 = 0;
            }
        }

    }
}

void Game::updateByTick(double dt)
{
}

void Game::updateByNoTick(double dt)
{
    server->updateServerConnect();

    for (auto& p : players)
    {
        if (p.getOnline())
        {
            if (p.getMovingState())
            {
                if (tileMap.RectvsRectCol(p, dt))
                {
                }
                else
                    p.movePlayer(dt);
            }
            p.update(dt);
            p.weapon.Update(dt);
        }
    }

    tileMap.Update(players[myID].getPos());

    eM->Update(dt);



    string s;
    s = "Ping: " + to_string(ping) + " ms" + " Fps: " + to_string((int)(1 / fps));
    pGUI->setPingText(s);
    string playersInfo;
    for (auto& p : players)
    {
        if (p.isOnline)
        {
            playersInfo += "Player " + to_string(p.playerID) + " is " + (p.isReadyForGameplay == true ? "ready\n" : "not ready\n");
        }
    }
    pGUI->setPlayersStatusInfo(playersInfo);
    pGUI->update(players[myID].getPos());
}

float Game::GetLenghtVector(Vector2f v)
{
    return sqrtf(pow(v.x, 2) + pow(v.y, 2));
}

void Game::GetPointWherePlayerLookAt(Player& p)
{
    p.pointsOfLaserEndWalls.clear();
    p.pointsOfLaserEndBots.clear();
    p.lenghtForWalls = 0;
    p.lenghtForBots = 0;
    p.BotPlayerLookAt = nullptr;
    p.WallPlayerLookAt = nullptr;

    float pAngle = p.player.getRotation();

    float lenght = 10.f;

    float pAngleRad = (pAngle-90) / 180 * M_PI;

    Vector2f mousePos = { cosf(pAngleRad) * lenght + p.getPos().x, sinf(pAngleRad) * lenght + p.getPos().y };

    pointLaserPlayer.setPosition(mousePos);

    for (auto& r : tileMap.allTiles)
    {
        if(r.isColiding)
        GetRaycast(r.tile, p, mousePos);
    }
}

void Game::GetRaycast(RectangleShape& wall, Player& p, Vector2f mousePos)
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

array<Vector2f, 4>& Game::GetVertices(RectangleShape& r)
{
    array<Vector2f, 4> VertexArray;
    Transform transform = r.getTransform();
    for (int i = 0; i < r.getPointCount(); ++i)
    {
        VertexArray[i] = transform.transformPoint(r.getPoint(i));
    }
    return VertexArray;
}

void Game::sendServerInfo(ServerInfo s)
{
    switch (s)
    {
    case ServerInfo::MouseClickedLeft1:
    {
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f mousePos = window.mapPixelToCoords(pixelPos);
        server->getGameHandleInputMouse(GameHandleInputMouse::MouseClicked_Left, mousePos);
    }
    break;
    case ServerInfo::MouseRelesedLeft1:
    {
        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f mousePos = window.mapPixelToCoords(pixelPos);
        server->getGameHandleInputMouse(GameHandleInputMouse::MouseRelesed_Left, mousePos);
    }
    break;
    case ServerInfo::Key_W_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_W);
    }
    break;
    case ServerInfo::Key_S_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_S);
    }
    break;
    case ServerInfo::Key_A_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_A);
    }
    break;
    case ServerInfo::Key_D_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_D);
    }
    break;
    case ServerInfo::Key_W_Relesed:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_W_Rel);
    }
    break;
    case ServerInfo::Key_S_Relesed:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_S_Rel);
    }
    break;
    case ServerInfo::Key_A_Relesed:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_A_Rel);
    }
    break;
    case ServerInfo::Key_D_Relesed:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_D_Rel);
    }
    break;
    case ServerInfo::ChangePlayerAngle:
    {
        server->getGameHandleInputMouse(GameHandleInputMouse::MouseChangeAngle, { playerAngle,0 });
    }
    break;
    case ServerInfo::Key_R_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_R);
    }
    break;
    case ServerInfo::Key_R_Relesed:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_R_Rel);
    }
    break;
    case ServerInfo::Key_Space_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_Space);
    }
    break;
    case ServerInfo::Key_F5_Clicked:
    {
        server->gameHandleInput(GameHandleInputKeyboard::Keyboard_F5);
    }
    break;
    default:
        break;
    }
}

void Game::draw()
{
    window.clear(Color::Black);

    pGUI->setView(window);

    tileMap.Draw(window);

    eM->Draw(window);

    for (auto& p : players)
    {
        if (p.getOnline())
            p.draw(window);
    }

    pGUI->draw(window);
    window.draw(pointLaserPlayer);
    if (showGameInfo)
        window.draw(gameInfo);
    window.display();
}