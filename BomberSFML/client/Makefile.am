bin_PROGRAMS=client

client_SOURCES=\
    BomberSFML.cpp \
    Bullet.cpp \
    Bullet.h \
    ClosingEventHandler.cpp \
    ClosingEventHandler.h \
    EventHandler.cpp \
    EventHandler.h \
    MoveEventHandler.cpp \
    MoveEventHandler.h \
    Window.cpp \
    Window.h \
    Connection.h \
    Connection.cpp \
    Character.h \
    Character.cpp \
    Game.h \
    Game.cpp \
    ShootEventHandler.cpp \
    ShootEventHandler.h \
    MouseEventHandler.h \
    MouseEventHandler.cpp \
    Anim.h \
    Layer.h \
    Layer.cpp

AM_CPPFLAGS = $(SFML_CFLAGS) -I../../../BomberSFML-network/src/

client_LDADD = $(SFML_LIBS) ../../../BomberSFML-network/build/libBomberSFML-network.la -lboost_serialization
