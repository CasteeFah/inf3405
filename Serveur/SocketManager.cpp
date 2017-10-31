#include "SocketManager.h"

using namespace std;

SocketManager::SocketManager() {
	init();
}

SocketManager::~SocketManager() {
}

void SocketManager::init() {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR) {
		cerr << "Error at startup" << endl;
		exit(1);
	}
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		cerr << "Error at socket" << endl;
		exit(2);
	}
	char* option = "1";
	setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, option, sizeof(option));
	char host[16];
	cout << "Entrez l'adresse IP du serveur" << endl;
	gets_s(host);
	thisHost = gethostbyname(host);
	ip = inet_ntoa(*(struct in_addr*) *thisHost->h_addr_list);
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(ip);
	service.sin_port = htons(port);


    if (bind(ServerSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
        cerr << "bind() failed." << endl;
        closesocket(ServerSocket);
        WSACleanup();
        exit(3);
    }

    //----------------------
    // Listen for incoming connection requests.
    // on the created socket
    if (listen(ServerSocket, 30) == SOCKET_ERROR) {
        cerr << "Error listening on socket." << endl;
        closesocket(ServerSocket);
        WSACleanup();
        exit(4);
    }
}

SOCKET SocketManager::getServerSocket() {
	return ServerSocket;
}
