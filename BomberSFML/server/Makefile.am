bin_PROGRAMS=server

server_SOURCES=\
    BomberSFML-server.cpp \
    ../client/Character.cpp \
    ../client/Character.h \
    Client.h \
    Client.cpp \
    Channel.cpp \
    Channel.h
    
AM_CPPFLAGS=$(SFML_CFLAGS) -I../../../BomberSFML-network
server_LDADD=$(SFML_LIBS) ../../../BomberSFML-network/build/libBomberSFML-network.la -lboost_serialization
