/***************************************
*                                      *
*             Client                   *
*                                      *
****************************************/

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv){

  sf::IPAddress servAddr= sf::IPAddress::LocalHost;
  unsigned short write_port = 8888;
  unsigned short receive_port = 7777;
  std::size_t received;


  sf::SocketUDP socket;

  char buffer[128+1];
  strcpy(buffer,"Hello World !!!\n");

  /* Envoi de donnée sur le socket */
  /*if(socket.Send(buffer, sizeof(buffer), servAddr, write_port) != sf::Socket::Done)
    cout << "Error on socket\n";

  strcpy(buffer, "");
  */
   socket.Bind(receive_port);

   socket.Receive(buffer, sizeof(buffer), received, servAddr, receive_port);

    cout << buffer << endl;

    socket.Close();
    float test = 3.2;
    sf::Sleep(test);
  /* Envoi de donnée sur le socket */
  if(socket.Send(buffer, sizeof(buffer), servAddr, write_port) != sf::Socket::Done)
    cout << "Error on socket\n";

  cout << "Message envoyé sur le socket\n";
  

  socket.Close();
  return 0;
}
