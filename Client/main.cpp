#undef UNICODE
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "SocketHandler.h"

// Link avec ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

const int MESSAGE_LENGTH = 201;
const int ALL_MESSAGES_LENGTH = 4081;
const int BROADCAST_LENGTH = 271;

extern DWORD WINAPI receiveMessage(void* sd);
DWORD WINAPI authentication();

//extern function : send message
//					receive messages
//					user + 
//					pw >> new pw / current pw /new user/old user/ 
//					validation msg


int __cdecl main(int argc, char **argv)
{
	Ptr_SocketHandler socketHandler = SocketHandler::getInstance();
	socketHandler->connectToServer();
	if (!authentication()) {
		return -1;
	}
	DWORD nThreadID;
	CreateThread(0, 0, receiveMessage, 0, 0, &nThreadID);

	while (true) {
		char message[MESSAGE_LENGTH];
		std::cout << ">";
		std::cin.getline(message, MESSAGE_LENGTH);
		std::cin.clear();
		//while (cin) {
			//std::cin.ignore();
		//}
		//-----------------------------
		// Envoyer le mot au serveur
		int Result = send(*(socketHandler->getSocket()), message, MESSAGE_LENGTH, 0);
		if (Result == SOCKET_ERROR) {
			printf("Erreur du send: %d\n", WSAGetLastError());
			closesocket(*(socketHandler->getSocket()));
			WSACleanup();
			printf("Appuyez une touche pour finir\n");
			getchar();
			return 1;
		}
	}

	

}

DWORD WINAPI receiveMessage(void* sd) {
	SOCKET* socket = SocketHandler::getInstance()->getSocket();
	while (true) {
		char buffer[BROADCAST_LENGTH];
		int status = recv(*socket, buffer, BROADCAST_LENGTH, 0);
		if (status == SOCKET_ERROR) {
			return 0;
		}
		std::cout << buffer << std::endl << ">";
	}
}

DWORD WINAPI authentication() {
	SOCKET* socket = SocketHandler::getInstance()->getSocket();
	char buffer[10];
	char messages[ALL_MESSAGES_LENGTH]; //TODO redefine

	int status = recv(*socket, buffer, 10, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	char username[20];
	char password[20];
	std::cout << std::endl << "Veuillez entrer votre nom d'utilisateur(longueur max: 20 caractères): ";
	std::cin.getline(username, 20);
	std::cin.clear();
	send(*socket, username, 20, 0);
	status = recv(*socket, buffer, 10, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	if ((std::string) buffer == "oldUser") {
		std::cout << std::endl << "Entrez votre mot de passe: ";
	}
	else {
		std::cout << std::endl << "Entrez un mot de passe pour votre nouveau compte((longueur max: 20 caractères): ";
	}
	std::cin.getline(password, 20);
	std::cin.clear();
	send(*socket, password, 20, 0);
	status = recv(*socket, buffer, 10, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	if ((std::string)buffer == "badpw") {
		std::cout << std::endl << "Le mot de passe entré est invalide" << std::endl;
		system("pause");
		return 0;
	}
	//std::cout << buffer << std::endl;
	status = recv(*socket, messages, ALL_MESSAGES_LENGTH, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	std::cout << messages << std::endl;
	return 1;
}
