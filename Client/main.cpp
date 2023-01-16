#include "Game.hpp"

int main()
{
	Game g;
	return 0;
}

//#include "Game.hpp"
//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <array>
//#include "Definitions.hpp"
//#include "TileMap.hpp"
//#include "Tile.hpp"
//#include "EnemyManager.hpp"
//#include "Enemy.hpp"
//#include <map>
//#include <SFML/Network.hpp>
//#include <iomanip>
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//
//using namespace std;
//using namespace sf;
//
//vector<RectangleShape> rects;
//vector<Tile*> visibleRects;
//vector<ConvexShape> shadows;
//map<float, Vector2f> pointsOfLaserEndWalls;
//map<float, Vector2f> pointsOfLaserEndBots;
//float lenghtForWalls = 0;
//float lenghtForBots = 0;
//RectangleShape* WallPlayerLookAt;
//CircleShape* BotPlayerLookAt;
//vector<CircleShape> bots;
//RectangleShape player;
//RectangleShape laser;
//Vector2f playerPos = {1000.f,800.f};
//
//float GetLenghtVector(Vector2f v)
//{
//	return sqrtf(pow(v.x, 2) + pow(v.y, 2));
//}
//
//float determinant(Vector2f x1, Vector2f x2)
//{
//    return (x1.y * x2.x - x1.x * x2.y);
//}
//
//array<Vector2f, 4>& GetVertices(RectangleShape& r)
//{
//    array<Vector2f, 4> VertexArray;
//    Transform transform = r.getTransform();
//    for (int i = 0; i < r.getPointCount(); ++i)
//    {
//        VertexArray[i] = transform.transformPoint(r.getPoint(i));
//    }
//    return VertexArray;
//}
//
//ConvexShape getShadows(array<Vector2f, 4> VertexArray, Vector2f pPos) //returns a vector of quadrilaterals representing the shadows
//{
//    ConvexShape result;
//    for (int i(0); i < VertexArray.size(); i += 4) //you store the points of the objects casting shadows in rectanglePoints
//    {
//        Vector2f limitPoint1 = VertexArray[i]; //extreme point 1 from the player's perspective
//        Vector2f limitPoint2 = VertexArray[i]; //extreme point 2 from the player's perspective
//        for (int j(0); j < 4; j++)
//        {
//            bool result = true; //buffer to know whether or not the point considered is an extreme point with det>0
//            bool result2 = true; //buffer to know whether or not the point considered is an extreme point with det<0
//            for (int k(0); k < 4, k != j; k++) //testing the determinants with the other points of the object
//            {
//                if (determinant(VertexArray[i + j] - pPos, VertexArray[i + k] - pPos) > 0) //case det>0
//                    result = false;
//                else //case det<0
//                    result2 = false;
//            }
//            if (result)
//                limitPoint1 = VertexArray[i + j]; //we have found our first extreme point
//            if (result2)
//                limitPoint2 = VertexArray[i + j]; //we have found our second extreme point
//        }
//        Vector2f projection1 = (limitPoint1 - pPos) * 100.f; //cast the first extreme point from the player's perspective
//        projection1 += pPos;
//        Vector2f projection2 = (limitPoint2 - pPos) * 100.f; //cast the second extreme point from the player's perspective
//        projection2 += pPos;
//        ConvexShape shadow(4);
//        shadow.setPoint(0, limitPoint1);
//        shadow.setPoint(1, limitPoint2);
//        shadow.setPoint(2, projection2);
//        shadow.setPoint(3, projection1);
//		shadow.setFillColor(Color::Black);
//
//		result = shadow;
//        //result.push_back(shadow);
//    }
//
//    return result;
//}
//
//void GetVisibleRects(TileMap& tileMap, Vector2f pPos)
//{
//    shadows.clear();
//    for (auto& v : tileMap.visibleTiles)
//    {
//        shadows.push_back(getShadows(GetVertices(v.tile), playerPos));
//    }
//}
//
//void GetRaycast(RectangleShape& wall, Vector2f pPos, Vector2f mousePos)
//{
//    array<Vector2f, 4> wallVertices = GetVertices(wall);
//
//    bool findPoint = 0;
//    //wallVertices[0] top left
//    //wallVertices[1] top right
//    //wallVertices[2] down right
//    //wallVertices[3] down left
//
//    for (int i = 0; i < 3; i++)
//    {
//        if (i == 2)
//        {
//            float x1 = wallVertices[3].x;
//            float y1 = wallVertices[3].y;
//
//            float x2 = wallVertices[0].x;
//            float y2 = wallVertices[0].y;
//
//            float x3 = pPos.x;
//            float y3 = pPos.y;
//
//            float x4 = mousePos.x;
//            float y4 = mousePos.y;
//
//            float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
//            if (den == 0) { continue; }
//            float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
//            float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
//
//            if (t > 0 && t < 1 && u>0)
//            {
//                Vector2f p;
//                p.x = (x1 + t * (x2 - x1));
//                p.y = (y1 + t * (y2 - y1));
//                float len = GetLenghtVector({ p.x - x3, p.y - y3 });
//                pointsOfLaserEndWalls[len] = p;
//                findPoint = 1;
//                if (lenghtForWalls == 0)
//                {
//                    lenghtForWalls = len;
//                    WallPlayerLookAt = &wall;
//                }
//                else if (lenghtForWalls >= len)
//                {
//                    lenghtForWalls = len;
//                    WallPlayerLookAt = &wall;
//                }
//            }
//
//        }
//
//
//        float x1 = wallVertices[i].x;
//        float y1 = wallVertices[i].y;
//
//        float x2 = wallVertices[i+1].x;
//        float y2 = wallVertices[i+1].y;
//
//        float x3 = pPos.x;
//        float y3 = pPos.y;
//
//        float x4 = mousePos.x;
//        float y4 = mousePos.y;
//
//        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
//        if (den == 0) { continue;}
//        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
//        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
//
//        if (t > 0 && t < 1 && u>0)
//        {
//            Vector2f p;
//            p.x = (x1 + t * (x2 - x1));
//            p.y = (y1 + t * (y2 - y1));
//            float len = GetLenghtVector({ p.x - x3, p.y - y3 });
//            pointsOfLaserEndWalls[len] = p;
//            findPoint = 1;
//
//            if (lenghtForWalls == 0)
//            {
//                lenghtForWalls = len;
//                WallPlayerLookAt = &wall;
//            }
//            else if (lenghtForWalls >= len)
//            {
//                lenghtForWalls = len;
//                WallPlayerLookAt = &wall;
//            }
//        }
//    }
//}
//
//void GetRaycastToCircle(CircleShape& circle, Vector2f pPos, Vector2f mousePos)
//{
//    float LAB = sqrtf(powf((mousePos.x - pPos.x), 2) + powf((mousePos.y - pPos.y), 2));
//
//    float Dx = (mousePos.x - pPos.x) / LAB;
//    float Dy = (mousePos.y - pPos.y) / LAB;
//
//    Vector2f circlePos = circle.getPosition();
//    float circleRadius = circle.getRadius();
//
//    float t = Dx * (circlePos.x - pPos.x) + Dy * (circlePos.y - pPos.y);
//
//    Vector2f E;
//    E.x = t * Dx + pPos.x;
//    E.y = t * Dy + pPos.y;
//
//    float LEC = sqrtf(powf((E.x - circlePos.x), 2) + powf((E.y - circlePos.y), 2));
//
//        if (LEC < circleRadius)
//        {
//            float dt = sqrtf(pow(circleRadius, 2) - powf(LEC, 2));
//
//            Vector2f F, G;
//            F.x = (t - dt) * Dx + pPos.x;
//            F.y = (t - dt) * Dy + pPos.y;
//            float lenF = GetLenghtVector(F - pPos);
//            pointsOfLaserEndBots[lenF] = F;
//
//            //G.x = (t + dt) * Dx + pPos.x;
//            //G.y = (t + dt) * Dy + pPos.y;
//            //float lenG = GetLenghtVector(G - pPos);
//            //pointsOfLaserEnd[lenG] = G;
//
//            if (lenghtForBots == 0)
//            {
//                lenghtForBots = lenF;
//                BotPlayerLookAt = &circle;
//            }
//            else if (lenghtForBots >= lenF)
//            {
//                lenghtForBots = lenF;
//                BotPlayerLookAt = &circle;
//            }
//        }
//
//        else if (LEC == circleRadius)
//        {
//            float lenE = GetLenghtVector(E - pPos);
//            pointsOfLaserEndBots[lenE] = E;
//
//            if (lenghtForBots == 0)
//            {
//                lenghtForBots = lenE;
//                BotPlayerLookAt = &circle;
//            }
//            else if (lenghtForBots >= lenE)
//            {
//                lenghtForBots = lenE;
//                BotPlayerLookAt = &circle;
//            }
//
//        }
//}
//
////void GetRaycastToCircle2(CircleShape& circle, Vector2f pPos, Vector2f mousePos)
////{
////    Vector2f cPos = circle.getPosition();
////
////    float distX = pPos.x - mousePos.x;
////    float distY = pPos.y - mousePos.y;
////    float len = sqrt((distX * distX) + (distY * distY));
////
////    float dot = (((cPos.x - pPos.x) * (mousePos.x - pPos.x)) + ((cPos.y - pPos.y) * (mousePos.y - pPos.y))) / pow(len, 2);
////
////    float closestX = pPos.x + (dot * (mousePos.x - pPos.x));
////    float closestY = pPos.y + (dot * (mousePos.y - pPos.y));
////
////    distX = closestX - cPos.x;
////    distY = closestY - cPos.y;
////    float distance = sqrt((distX * distX) + (distY * distY));
////
////    if (distance <= circle.getRadius()) 
////    {
////        Vector2f E;
////        E.x = closestX;
////        E.y = closestY;
////
////        float len = GetLenghtVector(E - pPos);
////        pointsOfLaserEnd[len] = E;
////    }
////}
//
//bool RectvsRectCol(RectangleShape& player, RectangleShape& wall, Vector2f& move, float dt);
//
//#include "Animation.hpp"
//
//int sdadsa()
//{
//    //Game g;
//
//    RenderWindow window;
//    window.create(VideoMode(1280, 1024, 32), "a");
//
//    Clock timer;
//    float dt;
//
//    Player p;
//    p.setPos({ 1080,770 });
//    TileMap tileMap;
//    View v;
//    Vector2f playerVisibleRect = { (float)PLAYER_FOV_X * TILE_SIZE, (float)PLAYER_FOV_Y * TILE_SIZE };
//    Vector2f playerVisibleRect2 = { 1280, 1024 };
//    v.setSize(playerVisibleRect2);
//
//    RectangleShape rect;
//    rect.setSize({ TILE_SIZE, TILE_SIZE });
//    rect.setFillColor(Color::Red);
//
//
//    vector<Enemy*> enemies;
//    EnemyManager eM(&enemies);
//
//    //vector<int> id = { 461, 462, 463, 464, 465, 433, 401, 400 };
//    Enemy ene;
//    ene.SetPosByTileID(460);
//    //ene.AddIDToTileMove(id);
//    eM.AddEnemy(&ene);
//
//    while (window.isOpen())
//    {
//        dt = timer.restart().asSeconds();
//
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Key::W)) { p.setDir(PlayerDirection::MoveUp); p.setMovingState(true); }
//        else if (Keyboard::isKeyPressed(Keyboard::Key::S)) { p.setDir(PlayerDirection::MoveDown); p.setMovingState(true); }
//        else if (Keyboard::isKeyPressed(Keyboard::Key::A)) { p.setDir(PlayerDirection::MoveLeft); p.setMovingState(true); }
//        else if (Keyboard::isKeyPressed(Keyboard::Key::D)) { p.setDir(PlayerDirection::MoveRight); p.setMovingState(true); }
//        else if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();
//        else p.setMovingState(false);
//
//        Vector2i pixelPos = Mouse::getPosition(window);
//        Vector2f mousePosStatic = window.mapPixelToCoords(pixelPos);
//        static bool Clicked_Mouse_Left = 0;
//
//        rect.setPosition(tileMap.TilePosByID(mousePosStatic));
//
//        if (Mouse::isButtonPressed(Mouse::Left))
//        {
//            if (Clicked_Mouse_Left == 0)
//            {
//                Clicked_Mouse_Left = 1;
//                tileMap.Solve_AStar(&ene, mousePosStatic);
//            }
//        }
//        else
//        {
//            if (Clicked_Mouse_Left == 1)
//            {
//                Clicked_Mouse_Left = 0;
//            }
//        }
//
//        tileMap.Update(p.getPos());
//
//        if (p.getMovingState())
//        {
//            if (tileMap.RectvsRectCol(p, dt))
//            {
//            }
//            else
//                p.movePlayer(dt);
//        }
//        p.update(dt);
//        v.setCenter(p.getPos());
//
//        eM.Update(dt);
//
//        window.clear();
//        window.setView(v);
//
//        tileMap.Draw(window);
//        p.draw(window);
//        eM.Draw(window);
//        window.draw(rect);
//        window.display();
//    }
//    return 0;
//}
//
//
///*int w = 1024;
//int h = 720;
//Vector2f playerVisibleRect = { (float)PLAYER_FOV_X * TILE_SIZE, (float)PLAYER_FOV_Y * TILE_SIZE };
//TileMap tileMap;
//
//RenderWindow window;
//window.create(VideoMode(w, h, 32), "a");
//
//srand(time(NULL));
//
//
//player.setFillColor(Color::Blue);
//player.setPosition({ playerPos });
//player.setSize({ PLAYER_SIZE, PLAYER_SIZE });
//player.setOrigin({ PLAYER_SIZE / 2, PLAYER_SIZE / 2 });
//
//View v;
//Text fps;
//Font f;
//f.loadFromFile(GAME_FONT);
//
//fps.setFont(f);
//fps.setFillColor(Color::Cyan);
//fps.setOutlineColor(Color::Black);
//fps.setOutlineThickness(2);
//fps.setPosition({ player.getPosition().x - playerVisibleRect.x/2, player.getPosition().y - playerVisibleRect.y/2 });
//fps.setCharacterSize(15);
//
//Clock timer;
//
//laser.setFillColor(Color::Green);
//laser.setSize({ 1,100 });
//laser.setOrigin({ laser.getSize().x / 2, 0});
//
//CircleShape laserPointTo;
//laserPointTo.setFillColor(Color::Green);
//laserPointTo.setPosition({ -5000,-5000 });
//laserPointTo.setRadius(3);
//laserPointTo.setOrigin(laserPointTo.getRadius(), laserPointTo.getRadius());
//
//RectangleShape wall;
//wall.setPosition({ 1000.f, 800.f });
//wall.setSize({ 200,50 });
//wall.setFillColor(Color::Red);
//
//int range = 1500 - 100 + 1;
//int num = rand() % range + 100;
//
//for (int i = 0; i < 50; i++)
//{
//    CircleShape bot;
//    bot.setFillColor(Color::Blue);
//    bot.setRadius(15);
//    bot.setOrigin(bot.getRadius(), bot.getRadius());
//    bot.setPosition({ (float)(rand() % range + 100), (float)(rand() % range + 100) });
//    bots.push_back(bot);
//}
//
//while (window.isOpen())
//{
//
//    Event event;
//    while (window.pollEvent(event))
//    {
//        if (event.type == Event::Closed)
//            window.close();
//    }
//
//    Vector2f move = { 0,0 };
//    if (Keyboard::isKeyPressed(Keyboard::Key::W)) move = { 0,-500 };
//    if (Keyboard::isKeyPressed(Keyboard::Key::S)) move = { 0,500 };
//    if (Keyboard::isKeyPressed(Keyboard::Key::A)) move = { -500,0 };
//    if (Keyboard::isKeyPressed(Keyboard::Key::D)) move = { 500,0 };
//    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();
//
//    float dt = timer.restart().asSeconds();
//
//    string s;
//    static float dtTime;
//    dtTime += dt;
//    s = "Fps: " + to_string((int)(1 / dt));
//    if (dtTime > 0.1)
//    {
//        fps.setString(s);
//        dtTime = 0;
//    }
//
//    move *= dt;
//
//    if (player.getGlobalBounds().intersects(wall.getGlobalBounds()))
//    {
//        player.setFillColor(Color::Yellow);
//    }
//    else
//    {
//        player.setFillColor(Color::Blue);
//    }
//
//    player.move(move);
//
//    playerPos = player.getPosition();
//    Vector2i pixelPos = Mouse::getPosition(window);
//    Vector2f mousePos = window.mapPixelToCoords(pixelPos);
//    float playerAngle = atan2(mousePos.x - playerPos.x, mousePos.y - playerPos.y) * (180 / M_PI * -1);
//
//
//    player.setRotation(playerAngle);
//    Vector2f laserPoint;
//    pointsOfLaserEndWalls.clear();
//    pointsOfLaserEndBots.clear();
//    lenghtForWalls = 0;
//    lenghtForBots = 0;
//    BotPlayerLookAt = nullptr;
//    WallPlayerLookAt = nullptr;
//    int playerx = playerPos.x / TILE_SIZE;
//    int playery = playerPos.y / TILE_SIZE;
//    for (auto& r : tileMap.allTiles)
//    {
//        if (r.isColiding)
//        {
//            float pAngle = playerAngle + 180;
//
//            if (pAngle >= 0 && pAngle <= 90)
//            {
//                if (r.xMapCord >= playerx && r.yMapCord <= playery)
//                {
//                    GetRaycast(r.tile, playerPos, mousePos);
//                }
//            }
//            if (pAngle >= 90 && pAngle <= 180)
//            {
//                if (r.xMapCord >= playerx && r.yMapCord >= playery)
//                {
//                    GetRaycast(r.tile, playerPos, mousePos);
//                }
//            }
//            if (pAngle >= 180 && pAngle <= 270)
//            {
//                if (r.xMapCord <= playerx && r.yMapCord >= playery)
//                {
//                    GetRaycast(r.tile, playerPos, mousePos);
//                }
//            }
//            if (pAngle >= 270 && pAngle <= 360)
//            {
//                if (r.xMapCord <= playerx && r.yMapCord <= playery)
//                {
//                    GetRaycast(r.tile, playerPos, mousePos);
//                }
//            }
//        }
//    }
//
//    GetRaycast(wall, playerPos, mousePos);
//    cout << pointsOfLaserEnd.size() << endl;
//
//    for (auto& b : bots)
//    {
//        float playerx = playerPos.x;
//        float playery = playerPos.y;
//        float pAngle = playerAngle + 180;
//        Vector2f bPos = b.getPosition();
//        if (pAngle >= 0 && pAngle <= 90)
//        {
//            if (bPos.x >= playerx && bPos.y <= playery)
//            {
//                GetRaycastToCircle(b, playerPos, mousePos);
//            }
//        }
//        if (pAngle >= 90 && pAngle <= 180)
//        {
//            if (bPos.x >= playerx && bPos.y >= playery)
//            {
//                GetRaycastToCircle(b, playerPos, mousePos);
//            }
//        }
//        if (pAngle >= 180 && pAngle <= 270)
//        {
//            if (bPos.x <= playerx && bPos.y >= playery)
//            {
//                GetRaycastToCircle(b, playerPos, mousePos);
//            }
//        }
//        if (pAngle >= 270 && pAngle <= 360)
//        {
//            if (bPos.x <= playerx && bPos.y <= playery)
//            {
//                GetRaycastToCircle(b, playerPos, mousePos);
//            }
//        }
//    }
//
//    if (pointsOfLaserEndWalls.size() > 0)
//    {
//        laserPoint = pointsOfLaserEndWalls.begin()->second;
//        if(WallPlayerLookAt)
//        laserPointTo.setPosition({ WallPlayerLookAt->getPosition().x + TILE_SIZE / 2, WallPlayerLookAt->getPosition().y + TILE_SIZE / 2 });
//    }
//    else
//    {
//        laserPointTo.setPosition({ 0,0 });
//        laserPoint = { 0,0 };
//    }
//
//    if (pointsOfLaserEndBots.size() || pointsOfLaserEndWalls.size())
//    {
//        if (pointsOfLaserEndBots.size() > 0 && pointsOfLaserEndWalls.size() > 0)
//        {
//            float l1 = pointsOfLaserEndBots.begin()->first;
//            float l2 = pointsOfLaserEndWalls.begin()->first;
//
//            if (l2 < l1)
//            {
//                    laserPoint = pointsOfLaserEndWalls.begin()->second;
//                    if(WallPlayerLookAt)
//                    laserPointTo.setPosition({ WallPlayerLookAt->getPosition().x + TILE_SIZE / 2, WallPlayerLookAt->getPosition().y + TILE_SIZE / 2 });
//            }
//            else
//            {
//                laserPoint = pointsOfLaserEndBots.begin()->second;
//                if (BotPlayerLookAt)
//                    laserPointTo.setPosition({ BotPlayerLookAt->getPosition().x, BotPlayerLookAt->getPosition().y});
//
//            }
//        }
//        else
//        {
//            if (pointsOfLaserEndWalls.size() > 0)
//            {
//                laserPoint = pointsOfLaserEndWalls.begin()->second;
//                if (WallPlayerLookAt)
//                    laserPointTo.setPosition({ WallPlayerLookAt->getPosition().x + TILE_SIZE / 2, WallPlayerLookAt->getPosition().y + TILE_SIZE / 2 });
//            }
//            else
//            {
//                laserPoint = pointsOfLaserEndBots.begin()->second;
//                if (BotPlayerLookAt)
//                    laserPointTo.setPosition({ BotPlayerLookAt->getPosition().x, BotPlayerLookAt->getPosition().y });
//
//            }
//        }
//
//    }
//    else
//    {
//        laserPointTo.setPosition({ 0,0 });
//        laserPoint = { 0,0 };
//    }
//
//    Vector2f vec = playerPos - laserPoint;
//
//    float lenght = GetLenghtVector(vec);
//
//    Vector2f vecNorm = vec / lenght;
//
//    laser.setPosition(vec);
//    laser.setSize({ 1, 1 * lenght });
//
//    fps.move(move);
//    v.setCenter(playerPos);
//    laser.setPosition(playerPos);
//    laser.setRotation(playerAngle);
//    window.setView(v);
//
//    tileMap.Update(playerPos);
//
//    window.clear(Color::Color(55, 55, 55, 0));
//
//
//    tileMap.Draw(window);
//
//    for (auto& b : bots)
//        window.draw(b);
//    window.draw(player);
//    window.draw(wall);
//    window.draw(fps);
//    window.draw(laser);
//    window.draw(laserPointTo);
//    window.display();
//}*/
//
////RenderWindow window;
////window.create(VideoMode(800, 600, 32), "a");
//
////Clock timer;
////float dt;
////TileMap tileMap;
////Player p;
//////p.setPos({ 1000.f,800.f });
//
////while (window.isOpen())
////{
////    dt = timer.restart().asSeconds();
//
////    Event event;
////    while (window.pollEvent(event))
////    {
////        if (event.type == Event::Closed)
////            window.close();
////    }
//
////    //Vector2f move = { 0,0 };
////    //float player_speed = 100;
////    if (Keyboard::isKeyPressed(Keyboard::Key::W)) { p.setDir(PlayerDirection::MoveUp); p.setMovingState(true); };
////    if (Keyboard::isKeyPressed(Keyboard::Key::S)) { p.setDir(PlayerDirection::MoveDown); p.setMovingState(true); };
////    if (Keyboard::isKeyPressed(Keyboard::Key::A)) { p.setDir(PlayerDirection::MoveLeft); p.setMovingState(true); }
////    if (Keyboard::isKeyPressed(Keyboard::Key::D)) { p.setDir(PlayerDirection::MoveRight); p.setMovingState(true); }
////    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();
//
////    //if (RectvsRectCol(player, wall, move, dt))
////    //{
//
////    //}
////    //else
////    //{
////    //    move *= dt;
////    //    player.move(move);
////    //}
//
////    tileMap.Update(p.getPos());
//
////    if (p.getMovingState())
////    {
////        if (tileMap.RectvsRectCol(p, dt))
////        {
////            //coll
////        }
////        else
////            p.movePlayer(dt);
////    }
//
////    window.clear(Color::Black);
//
////    tileMap.Draw(window);
////    p.draw(window);
////    window.display();
////}
//
//
//bool RectvsRectCol(RectangleShape& player, RectangleShape& wall, Vector2f& move, float dt)
//{
//    Vector2f playerPos = player.getPosition();
//    Vector2f playerHalfSize = player.getSize() / 2.f;
//    Vector2f wallPos = wall.getPosition();
//    Vector2f wallHalfSize = wall.getSize() / 2.f;
//
//    float player_speed = 100;
//    Vector2f moveNorm = { move.x / player_speed, move.y / player_speed };
//
//
//    Vector2f playerPotentialPos = { playerPos.x +  move.x * dt, playerPos.y + move.y * dt };
//
//    Vector2f delta = playerPotentialPos - wallPos;
//    Vector2f intersect = { fabs(delta.x) - (playerHalfSize.x + wallHalfSize.x), fabs(delta.y) - (playerHalfSize.y + wallHalfSize.y) };
//
//    if (intersect.x < 0.f && intersect.y < 0.f)
//    {
//        playerPotentialPos = { playerPotentialPos.x + intersect.x * moveNorm.x,playerPotentialPos.y + intersect.y * moveNorm.y };
//
//        player.setPosition(playerPotentialPos);
//        return true;
//    }
//
//    return false;
//}
//
////////////////////////////////////////////////// TCP SERVER /////////////////////////////////////////////////////
//TcpSocket server;
//
//int main2()
//{
//    //Game g;
//
//    int end = 5000 - 1;
//    bool start = 0;
//    bool aje = 0;
//    Clock t;
//    Time time;
//
//    if (server.connect(IpAddress::getLocalAddress(), 53000) != Socket::Done)
//    {
//        cout << "brak polaczenia" << endl;
//    }
//    else
//    {
//        cout << "jest polaczenie" << endl;
//    }
//
//    Packet p;
//
//    while (1)
//    {
//        if (server.receive(p) == Socket::Done)
//        {
//            start = 1;
//            if (start && !aje)
//            {
//                aje = 1;
//                t.restart();
//            }
//            int x, y;
//            p >> x >> y;
//            //cout << "Pakiet id: " << x << " dane: " << y << endl;
//            if (y == end)
//            {
//                time = t.getElapsedTime();
//                cout << "Czas: " << ((float)(time.asMicroseconds()) / 1000);
//            }
//        }
//    }
//
//    return 0;
//}
/////////////////////////////////////////////////////////////////////////////////////////
//
//
//UdpSocket socket;
//
//unsigned short port = 54000;
//
//IpAddress ip = IpAddress::getLocalAddress();
//
//int main()
//{
//    int end = 5000 - 1;
//    bool start = 0;
//    bool aje = 0;
//    Clock t;
//    Time time;
//
//    if (socket.bind(port) != sf::Socket::Done)
//    {
//        cout << "brak bindu" << endl;
//    }
//
//    socket.setBlocking(false);
//
//    Packet p;
//
//    while (1)
//    {
//        if (socket.receive(p, ip, port) == Socket::Done)
//        {
//            start = 1;
//            if (start && !aje)
//            {
//                aje = 1;
//                t.restart();
//            }
//            int x, y;
//            p >> x >> y;
//            //cout << "Pakiet id: " << x << " dane: " << y << endl;
//            if (y == end)
//            {
//                time = t.getElapsedTime();
//                cout << "Czas: " << ((float)(time.asMicroseconds()) / 1000);
//            }
//        }
//    }
//
//    return 0;
//}