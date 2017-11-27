#include "SocketManager.h"

using namespace std;

Ptr_SocketManager SocketManager::getInstance() {
	if (!thisInstance) {
		thisInstance = std::make_shared<SocketManager>();
	}
	return thisInstance;
}

SocketManager::SocketManager() {}

SocketManager::~SocketManager() {
}

void SocketManager::init() {
	WSADATA wsaData;
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
	
	printf("Saisir l'adresse IP du serveur: ");
	std::cin.getline(ip, INET_ADDRSTRLEN);

	//check
	in_addr temp;
	if (inet_pton(AF_INET, ip, &temp) <= 0) {
		printf("Adresse IP invalide.\n");
		system("pause");
		exit(5);
	}

	char port_string[6];
	printf("Saisir le port du serveur: ");
	std::cin.getline(port_string, 6);
	int n = 0;
	while (port_string[n] != NULL) {
		if (isalpha(port_string[n])) {
			printf("Port invalide.\n");
			system("pause");
			exit(5);
		}
		n++;
	}
	port = atoi(port_string);
	if (!(port >= 5000 && port <= 5050)) {
		printf("Port invalide.\n");
		system("pause");
		exit(4);
	}
	// Set up the sockaddr structure
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
	else {
		std::cout << "Listening on address : " << ip << ":" << port << std::endl;
	}
}

void SocketManager::broadcast(char* message) {
	for (int i = sockets.size() - 1; i >= 0; i--) {
		int status = send(*sockets[i], message, 271, 0);
		if (status == SOCKET_ERROR) {
			sockets.erase(sockets.begin() + i);
			std::cout << "removed socket" << std::endl;
		}
	}
}


SOCKET SocketManager::getServerSocket() {
	return ServerSocket;
}

void SocketManager::add(SOCKET* sd) {
	sockets.push_back(sd);
}

std::shared_ptr<SocketManager> SocketManager::thisInstance = std::shared_ptr<SocketManager>();
