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

const int MESSAGE_LENGTH = 500;

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
	CreateThread(0, 0, receiveMessage, (void*) socketHandler->getSocket(), 0, &nThreadID);
	//bool status = true;

	while (true) {
		char message[150];
		std::cout << ">";
		gets_s(message);

		//-----------------------------
		// Envoyer le mot au serveur
		int Result = send(*(socketHandler->getSocket()), message, 150, 0);
		if (Result == SOCKET_ERROR) {
			printf("Erreur du send: %d\n", WSAGetLastError());
			closesocket(*(socketHandler->getSocket()));
			WSACleanup();
			printf("Appuyez une touche pour finir\n");
			getchar();
			exit(1);
		}
	}

	

}

DWORD WINAPI receiveMessage(void* sd) {
	SOCKET socket = (SOCKET)sd;
	while (true) {
		char buffer[MESSAGE_LENGTH];
		int status = recv(socket, buffer, MESSAGE_LENGTH, 0);
		if (status == SOCKET_ERROR) {
			return 0;
		}
		std::cout << buffer << std::endl << ">";
	}
}

DWORD WINAPI authentication() {
	SOCKET* socket = SocketHandler::getInstance()->getSocket();
	char buffer[10];
	int status = recv(*socket, buffer, 10, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	std::cout << buffer;
	char username[20];
	char password[20];
	std::cout << std::endl << "Veuillez entrer votre nom d'utilisateur: ";
	gets_s(username);
	send(*socket, username, 20, 0);
	status = recv(*socket, buffer, 10, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	if (buffer == "oldUser") {
		std::cout << std::endl << "Entrez votre mot de passe: ";
	}
	else {
		std::cout << std::endl << "Entrez un mot de passe pour votre nouveau compte: ";
	}
	gets_s(password);
	send(*socket, password, 20, 0);
	status = recv(*socket, buffer, 10, 0);
	if (status == SOCKET_ERROR) {
		return 0;
	}
	if (buffer == "badpw") {
		std::cout << std::endl << "Le mot de passe entré est invalide";
		return 0;
	}
	return 1;
}
