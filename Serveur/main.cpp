#include <string>
#include <iostream>
#include <winsock2.h>
#include <strstream>
#include "SocketManager.h"
#include "MessageManager.h"
#include "UserManager.h"
#include "User.h"
#include <ctime>

const int MESSAGE_LENGTH = 500;

struct ThreadData {
    SOCKET socket_;
    sockaddr_in addr_;
    ThreadData(SOCKET socket, sockaddr_in addr) : socket_(socket), addr_(addr) {};
};

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )
extern DWORD WINAPI socketHandler(LPVOID threadData);
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



			DWORD nThreadID;
			CreateThread(0, 0, socketHandler, (new ThreadData(socket, sinRemote)), 0, &nThreadID);
		}
		else {
			std::cout << "erreur" <<
				std::endl;
		}
	}
}

void receiveMessage(LPVOID threadData) {
	Ptr_SocketManager socketManager = SocketManager::getInstance();
	ThreadData *data = (ThreadData*)threadData;

	socketManager->add(&(data->socket_));

	char adr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(data->addr_.sin_addr), adr, INET_ADDRSTRLEN);
	std::cout << adr << ":" << data->addr_.sin_port << std::endl;

	std::string ip = adr;
	std::string port = std::to_string(data->addr_.sin_port);

	while (true) {
		char buffer[MESSAGE_LENGTH]; // define max length
		int status = recv(data->socket_, buffer, MESSAGE_LENGTH, 0);
		if (status == SOCKET_ERROR) {
			std::cout << "disconected" << std::endl;
			return;
		}
		std::cout << buffer << std::endl;

		time_t currentTime;
		time(&currentTime);
		tm date;
		localtime_s(&date, &currentTime);

		//std::cout << 1900 + date.tm_year << "-" << date.tm_mon + 1 << "-" << date.tm_mday << "@" << date.tm_hour << ":" << date.tm_min << ":" << date.tm_sec << std::endl;
		Message message("username", ip, port, date, buffer);

		std::cout << message;

		std::string messageString = message.messageToString();
		char * emitBuffer = &messageString[0u];

		socketManager->broadcast(emitBuffer);
		//send(*(SOCKET*)socket, message, 150, 0);
	}
}

void authentication(void* sd) {
    SOCKET socket = (SOCKET)sd;
	char* username = "";
	char* password = "";
	int userId = -1;
	Ptr_UserManager userManager = UserManager::getInstance();
	Ptr_MessageManager messageManager = MessageManager::getInstance();

	send(socket, "user", 4, 0);
	recv(socket, username, 10, 0);
	userId = userManager->findUserId(username);
	if (userId != -1) {// user exist
		send(*(SOCKET*)socket, "oldUser", 4, 0);
		recv(*(SOCKET*)socket, password, 4, 0);
		// verify password
		User user = userManager->getUser(userId);
		std::string realPassword = user.getPassword();
		if (password != realPassword) {
			send(*(SOCKET*)socket, "badpw", 4, 0);
			//exit(1);
		}
	}
	else {
		send(*(SOCKET*)socket, "newUser", 4, 0);
		recv(*(SOCKET*)socket, password, 4, 0);
		//create new User
		User* user = new User(username, password);
		userManager->addUser(*user);
	}
	//send(*(SOCKET*)socket, "messages", 4, 0);

}


DWORD WINAPI socketHandler(LPVOID threadData) {
	//authentication(socket);
	receiveMessage(threadData);
	return 0;
}

