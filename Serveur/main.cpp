#include <string>
#include <iostream>
#include <winsock2.h>
#include <strstream>
#include "SocketManager.h"
#include "UserManager.h"


// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )
extern DWORD WINAPI EchoHandler(void* sd_);
// extern function :	look for username
//						create user
//						check pass
//						emit last 5 message
//						emit new message

int main() {
	SocketManager socketManager;
	// UserManager
	// MessageManager

	socketManager.init(); 
	while (true) {
		sockaddr_in sinRemote;
		int nAddrSize = sizeof(sinRemote);
		SOCKET sd = accept(socketManager.getServerSocket(), (sockaddr*)&sinRemote, &nAddrSize);
		if (sd != INVALID_SOCKET) {
			std::cout << "socket connected" << std::endl;
			char adr[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &sinRemote.sin_addr, adr, INET_ADDRSTRLEN);
			std::cout << "Connection acceptee De : " <<
				adr << ":" <<
				ntohs(sinRemote.sin_port) << "." <<
				std::endl;
			//socketManager.add(&sd); >> apres credential check
			DWORD nThreadID;
			CreateThread(0, 0, EchoHandler, (void*)sd, 0, &nThreadID);
		}
		else {
			std::cout << "erreur" <<
				std::endl;
		}
	}
}

DWORD WINAPI EchoHandler(void* sd) {
	std::cout << "echo handled" << std::endl;
	return 0;
}