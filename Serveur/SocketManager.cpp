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
	/*
	char host[INET_ADDRSTRLEN];
	cout << "Entrez l'adresse IP du serveur" << endl;
	gets_s(host);

	sockaddr_in thisAddr;
	thisAddr.sin_addr

	getnameinfo(host, )

	inet_ntop(AF_INET, (struct in_addr*)*thisHost->h_addr_list, ip, INET_ADDRSTRLEN);
	service.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	*/
	// Get the local host information
	//thisHost = gethostbyname("");
	//ip = inet_ntoa(*(struct in_addr *)*thisHost->h_addr_list);
	
	printf("Saisir l'adresse IP du serveur: ");
	char host[INET6_ADDRSTRLEN];
	gets_s(host);

	//check
	if (inet_pton(AF_INET, host, &ip) <= 0) {
		printf("Adresse IP invalide.\n");
		system("pause");
	}

	char port_string[10];
	printf("Saisir le port du serveur: ");
	gets_s(port_string);
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
	service.sin_addr = ip;
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
		std::cout << "Listening on address : " << ip.s_addr << ":" << port << std::endl;
	}
}

void SocketManager::broadcast(char* message) {
	for (size_t i = sockets.size() - 1; i >= 0; i--) {
		int status = send(*sockets[i], message, 150, 0);
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
