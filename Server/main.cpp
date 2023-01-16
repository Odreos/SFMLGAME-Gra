#include "Server.hpp"

int main()
{
	Server server;

	return 0;
}

//#include <SFML/Network.hpp>
//#include "Server.hpp"
//#include <iomanip>
//#include <iostream>
//
//using namespace std;
//using namespace sf;
//
//
/////////////////////////////// TCP SERVER //////////////////////////////////////////////////
//TcpListener server;
//TcpSocket client;
//
//int main2()
//{
//    //Server server;
//
//    bool connect = 0;
//    bool wyslane = 0;
//    int iloscPakietow = 5000;
//
//    Clock t;
//    Time time;
//    if (server.listen(53000) != sf::Socket::Done)
//    {
//        cout << "blad dzialania" << endl;
//    }
//
//    cout << "server dziala" << endl;
//
//    while (1)
//    {
//        if (server.accept(client) == Socket::Done)
//        {
//            cout << "dolaczyl nowy gracz" << endl;
//            client.setBlocking(false);
//            connect = 1;
//            t.restart();
//        }
//
//        if (connect && !wyslane)
//        {
//            Packet p;
//            for (int i = 0; i < iloscPakietow; i++)
//            {
//                p << 1 << i;
//                client.send(p);
//                p.clear();
//            }
//            time = t.getElapsedTime();
//            wyslane = 1;
//        }
//        cout << "Czas wyslania: " << ((float)(time.asMicroseconds()) / 1000);
//    }
//
//    return 0;
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//UdpSocket server2;
//
//int iloscPakietow = 5000;
//bool wyslane = 0;
//
//int main()
//{
//	Clock t;
//	Time time;
//
//	sf::IpAddress recipient = IpAddress::getLocalAddress();
//	unsigned short port = 54000;
//
//	Packet p;
//
//	while (1)
//	{
//		if (!wyslane)
//		{
//			t.restart();
//			for (int i = 0; i < iloscPakietow; i++)
//			{
//				p.clear();
//				p << 1 << i;
//				server2.send(p, recipient, port);
//			}
//			wyslane = 1;
//			time = t.getElapsedTime();
//            cout << "Czas: " << ((float)(time.asMicroseconds()) / 1000) << endl;
//		}
//	}
//
//	return 0;
//}