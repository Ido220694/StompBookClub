CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system
CFLAGS += -pthread
LDFLAGS += -pthread

all: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/ClientsMain.o bin/connectionHandler.o bin/Book.o bin/ReadFromKeyboard.o bin/User.o bin/Inventory.o bin/ProtocolImpl.o bin/Frame.o $(LDFLAGS) 

StompBookClubClient: bin/connectionHandler.o bin/Book.o bin/ReadFromKeyboard.o bin/User.o bin/ClientsMain.o bin/Inventory.o bin/ProtocolImpl.o bin/Frame.o
	
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/Book.o: src/Book.cpp
	g++ $(CFLAGS) -o bin/Book.o src/Book.cpp
	
bin/ReadFromKeyboard.o: src/ReadFromKeyboard.cpp
	g++ $(CFLAGS) -o bin/ReadFromKeyboard.o src/ReadFromKeyboard.cpp

bin/User.o: src/User.cpp
	g++ $(CFLAGS) -o bin/User.o src/User.cpp

bin/ClientsMain.o: src/ClientsMain.cpp
	g++ $(CFLAGS) -o bin/ClientsMain.o src/ClientsMain.cpp

bin/Inventory.o: src/Inventory.cpp
	g++ $(CFLAGS) -o bin/Inventory.o src/Inventory.cpp

bin/ProtocolImpl.o: src/ProtocolImpl.cpp
	g++ $(CFLAGS) -o bin/ProtocolImpl.o src/ProtocolImpl.cpp

bin/Frame.o: src/Frame.cpp
	g++ $(CFLAGS) -o bin/Frame.o src/Frame.cpp

	
.PHONY: clean
clean:
	rm -f bin/*
