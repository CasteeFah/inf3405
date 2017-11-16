#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <algorithm>
#include <strstream>
#include <stdio.h>
#include <vector>
#include <memory>

class SocketManager
{
public:
	static Ptr_SocketManager getInstance();
	~SocketManager();
	void init();
	SOCKET getServerSocket();
	void add(SOCKET* sd);

private:
	SocketManager();
	static Ptr_SocketManager thisInstance;
	WSADATA wsaData;
	SOCKET ServerSocket;
	hostent *thisHost;
	char* ip;
	int port = 10000;
	sockaddr_in service;
	std::vector<SOCKET*> sockets;
};

typedef std::shared_ptr<SocketManager> Ptr_SocketManager;
