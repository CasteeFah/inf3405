#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <algorithm>
#include <strstream>
#include <stdio.h>
#include <vector>




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
	int port = 10000;
	sockaddr_in service;
	std::vector<SOCKET*> sockets;
};
