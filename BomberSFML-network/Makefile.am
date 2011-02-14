ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libBomberSFML-network.la
libBomberSFML_network_la_SOURCES = \
    src/Message.h \
    src/Message.cpp \
    src/DataMessage.h
    
libBomberSFML_network_la_LIBADD = -lsfml-network
libBomberSFML_network_la_LDFLAGS = -version-info 0:0:1
include_HEADERS = src/Message.h src/DataMessage.h

