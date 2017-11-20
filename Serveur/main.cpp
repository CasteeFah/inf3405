#include <string>
#include <iostream>
#include <winsock2.h>
#include <strstream>
#include "SocketManager.h"
#include "MessageManager.h"
#include "UserManager.h"
#include "User.h"
#include <ctime>


// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )
extern DWORD WINAPI socketHandle(void* socket);
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
			CreateThread(0, 0, socketHandle, (void*)socket, 0, &nThreadID);
		}
		else {
			std::cout << "erreur" <<
				std::endl;
		}
	}
}

void receiveMessage(void* socket) {
	while (true) {
		char buffer[150]; // define max length
		recv(*(SOCKET*)socket, buffer, 150, 0);

		time_t currentTime;
		time(&currentTime);
		struct tm* date = NULL;
		localtime_s(date, &currentTime);

		std::cout << 1900 + date->tm_year << "-" << date->tm_mon + 1 << "-" << date->tm_mday << "@" << date->tm_hour << ":" << date->tm_min << ":" << date->tm_sec << std::endl;

		//Message message(user.getUsername(), ,date, message);


		//send(*(SOCKET*)socket, message, 150, 0);
	}
}

void authentication(void* socket) {
	char* username = "";
	char* password = "";
	int userId = -1;
	Ptr_UserManager userManager = UserManager::getInstance();
	
	send(*(SOCKET*)socket, "user", 4, 0);
	recv(*(SOCKET*)socket, username, 10, 0);
	userId = userManager->findUserId(username);
	if (userId != -1) {// user exist
		send(*(SOCKET*)socket, "oldUser", 4, 0);
		recv(*(SOCKET*)socket, password, 4, 0);
		// verify password
		User user = userManager->getUser(userId);
		std::string realPassword = user.getPassword();
		if (password != realPassword) {
			send(*(SOCKET*)socket, "badpw", 4, 0);
		}
	}
	else {
		send(*(SOCKET*)socket, "newUser", 4, 0);
		recv(*(SOCKET*)socket, password, 4, 0);
		//create new User
		User* user = new User(username, password);
		userManager->addUser(*user);
	}
	send(*(SOCKET*)socket, "result", 4, 0);

}

DWORD WINAPI socketHandle(void* socket) {
	receiveMessage(socket);

	return 0;
}