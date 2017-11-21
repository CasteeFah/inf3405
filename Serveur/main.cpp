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
int authentication(LPVOID threadData);

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

	int validUser = 0;
	validUser = authentication(threadData);

	//while (validUser == 0) {}

	//if (validUser == -1) {
	//	return;
	//}
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


int authentication(LPVOID threadData) {
	ThreadData *data = (ThreadData*)threadData;
	char username[20];
	char password[20];
	int userId = -1;
	Ptr_UserManager userManager = UserManager::getInstance();
	Ptr_MessageManager messageManager = MessageManager::getInstance();

	send(data->socket_, "user", 10, 0);
	int status = recv(data->socket_, username, 20, 0);
	if (status == SOCKET_ERROR) {
		std::cout << "disconected" << std::endl;
		int info = WSAGetLastError();
		exit(info);
	}
	userId = userManager->findUserId(username);
	if (userId != -1) {// user exist
		send(data->socket_, "oldUser", 10, 0);
		status = recv(data->socket_, password, 20, 0);
		if (status == SOCKET_ERROR) {
			std::cout << "disconected" << std::endl;
			int info = WSAGetLastError();
			exit(info);
		}
		// verify password
		User user = userManager->getUser(userId);
		std::string realPassword = user.getPassword();
		if (password != realPassword) {
			send(data->socket_, "badpw", 10, 0);
			return -1;
		}
		else {
			send(data->socket_, "ok", 10, 0);
		}
	}
	else {
		send(data->socket_, "newUser", 10, 0);
		status = recv(data->socket_, password, 4, 0);
		if (status == SOCKET_ERROR) {
			std::cout << "disconected" << std::endl;
			int info = WSAGetLastError();
			exit(info);
		}
		//create new User
		User user = User(username, password);
		userManager->addUser(user);
		send(data->socket_, "ok", 10, 0);
	}
	send(data->socket_, "messages", 10, 0);
	return 1;
}



DWORD WINAPI socketHandler(LPVOID threadData) {
	receiveMessage(threadData);
	return 0;
}

