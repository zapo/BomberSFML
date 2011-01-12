/****************************************
*                                      *
*             Serveur                  *
*                                      *
****************************************/

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv){

  sf::IPAddress servAddr= sf::IPAddress::LocalHost;
  unsigned short receive_port = 8888;
  unsigned short write_port = 7777;

  sf::SocketUDP socket;

  char buffer[128+1];
  strcpy(buffer, "Hello World !!!\n");

  std::size_t received;

  /*if(!socket.Bind(receive_port))
    cout << "Error on Binding\n";

  if(socket.Receive(buffer, sizeof(buffer), received, servAddr, receive_port) != sf::Socket::Done)
  cout << "Error on reception\n";*/

  if(socket.Send(buffer, sizeof(buffer), servAddr, write_port) != sf::Socket::Done)
    cout << "Error on Sending\n";

  strcpy(buffer, "");
  //socket.Close();    
float test = 2.2;
    sf::Sleep(test);
  if(!socket.Bind(receive_port))
    cout << "Error on Binding\n";

  if(socket.Receive(buffer, sizeof(buffer), received, servAddr, receive_port) != sf::Socket::Done)
  cout << "Error on reception\n";

  cout << buffer << endl;

  socket.Close();

  return 0;
}
