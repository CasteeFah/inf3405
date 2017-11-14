#pragma once
#include <WinSock2.h>
#include <iostream>
#include <algorithm>
#include <strstream>
#include <stdio.h>
#include <vector>

int port = 10000;

class SocketManager
{
public:
	SocketManager();
	~SocketManager();
	void init();
	SOCKET getServerSocket();
	void add(SOCKET* sd);

private:
	WSADATA wsaData;
	SOCKET ServerSocket;
	hostent *thisHost;
	char* ip;
	sockaddr_in service;
	std::vector<SOCKET*> sockets;
};
