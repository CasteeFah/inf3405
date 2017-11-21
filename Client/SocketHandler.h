#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

class SocketHandler;
typedef std::shared_ptr<SocketHandler> Ptr_SocketHandler;

class SocketHandler
{
public:
	static Ptr_SocketHandler getInstance();
	SocketHandler();
	~SocketHandler();
	void connectToServer();
	SOCKET thisSocket;

private: 
	static Ptr_SocketHandler thisInstance;
};
