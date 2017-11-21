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

//extern function : send message
//					receive messages
//					user + 
//					pw >> new pw / current pw /new user/old user/ 
//					validation msg


int __cdecl main(int argc, char **argv)
{
	Ptr_SocketHandler socketHandler = SocketHandler::getInstance();
	socketHandler->connectToServer();

	DWORD nThreadID;
	CreateThread(0, 0, receiveMessage, (void*) socketHandler->thisSocket, 0, &nThreadID);
	//bool status = true;

	while (true) {
		char message[150];
		std::cout << ">";
		gets_s(message);

		//-----------------------------
		// Envoyer le mot au serveur
		int Result = send(socketHandler->thisSocket, message, 150, 0);
		if (Result == SOCKET_ERROR) {
			printf("Erreur du send: %d\n", WSAGetLastError());
			closesocket(socketHandler->thisSocket);
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
