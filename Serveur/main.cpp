#include <string>
#include <iostream>
#include <winsock2.h>
#include <strstream>
#include "SocketManager.h"
#include "MessageManager.h"
#include "UserManager.h"

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )
extern DWORD WINAPI EchoHandler(void* sd_);
// extern function :	look for username
//						create user
//						check pass
//						emit last 15 messages
//						emit new message

int main() {
	Ptr_SocketManager socketManager = SocketManager::getInstance();
	Ptr_UserManager userManager = UserManager::getInstance();
	Ptr_MessageManager messageManager = MessageManager::getInstance();

	socketManager->init(); 
	while (true) {
		sockaddr_in sinRemote;
		int nAddrSize = sizeof(sinRemote);
		SOCKET socket = accept(socketManager->getServerSocket(), (sockaddr*)&sinRemote, &nAddrSize);
		if (socket != INVALID_SOCKET) {
			std::cout << "socket connected" << std::endl;
			char adr[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &sinRemote.sin_addr, adr, INET_ADDRSTRLEN);
			std::cout << "Connection acceptee De : " <<
				adr << ":" <<
				ntohs(sinRemote.sin_port) << "." <<
				std::endl;
			//socketManager.add(&sd); >> apres credential check
			DWORD nThreadID;
			//CreateThread(0, 0, EchoHandler, (void*)sd, 0, &nThreadID);
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
void receiveMessage(void* socket) {
	while(true) {
		char message[150]; // define max length
		recv(*(SOCKET*)socket, message, 150, 0);
	}
}

void authentication(void* socket, Ptr_UserManager userManager) {
	char* username;
	char* password;
	int userId;
	
	send(*(SOCKET*)socket, "user", 4, 0);
	recv(*(SOCKET*)socket, username, 10, 0);
	userId = userManager->findUserId(username);
	if (userId != -1) {// user exist
		send(*(SOCKET*)socket, "oldUser", 4, 0);
		recv(*(SOCKET*)socket, password, 4, 0);
		// validate
		if wrong{
			send(*(SOCKET*)socket, "badpw", 4, 0);
		}
	} 
	else {
		send(*(SOCKET*)socket, "newUser", 4, 0);
		recv(*(SOCKET*)socket, password, 4, 0);
		//save
	}
	send(*(SOCKET*)socket, "result", 4, 0);

}

DWORD WINAPI socketHandle(void* socket, ) {
	
}