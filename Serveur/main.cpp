#include <string>
#include <iostream>
#include <Winsock2.h>
#include <strstream>
#include "SocketManager.h"

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )


int main() {
	SocketManager socketManager;
	socketManager.init();
	while (true) {
		sockaddr_in sinRemote;
		int nAddrSize = sizeof(sinRemote);
		SOCKET sd = accept(socketManager.getServerSocket(), (sockaddr*)&sinRemote, &nAddrSize);
		if (sd != INVALID_SOCKET) {
			std::cout << "Connection acceptee De : " <<
				inet_ntoa(sinRemote.sin_addr) << ":" <<
				ntohs(sinRemote.sin_port) << "." <<
				std::endl;
			//socketManager.add(&sd);
			DWORD nThreadID;
			CreateThread(0, 0, EchoHandler, (void*)sd, 0, &nThreadID);
		}
		else {
			std::cerr << "erreur" <<
				std::endl;
			    return 1;
		}
	}
}

DWORD WINAPI EchoHandler(void* sd) {
	std::cout << "echo handled" << std::endl;
	return 0;
}