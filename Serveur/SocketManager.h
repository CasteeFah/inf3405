#pragma once
#include <WinSock2.h>
#include <iostream>
#include <algorithm>
#include <strstream>
#include <stdio.h>

int port = 10000;

class SocketManager
{
public:
	SocketManager();
	~SocketManager();
	void init();
	SOCKET getServerSocket();

private:
	WSADATA wsaData;
	SOCKET ServerSocket;
	hostent *thisHost;
	char* ip;
	sockaddr_in service;
};
