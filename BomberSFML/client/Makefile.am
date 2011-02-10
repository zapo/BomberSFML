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
    Game.h \
    Game.cpp \
    ShootEventHandler.cpp \
    ShootEventHandler.h \
    MouseEventHandler.h \
    MouseEventHandler.cpp \
    Anim.h

AM_CPPFLAGS=$(SFML_CFLAGS) -I../../../BomberSFML-network/

client_LDADD=$(SFML_LIBS) -L../../../BomberSFML-network/Debug -lBomberSFML-network -lboost_serialization