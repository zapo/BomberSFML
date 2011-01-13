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

  
   socket.Bind(receive_port);

   socket.Receive(buffer, sizeof(buffer), received, servAddr, receive_port);

    cout << buffer << endl;

    socket.Close();
   

  

  socket.Close();
  return 0;
}
