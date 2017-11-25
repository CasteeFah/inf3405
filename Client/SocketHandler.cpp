#include "SocketHandler.h"


Ptr_SocketHandler SocketHandler::getInstance() {
	if (!thisInstance) {
		thisInstance = std::make_shared<SocketHandler>();
	}
	return thisInstance;
}

SocketHandler::SocketHandler()
{
}

SocketHandler::~SocketHandler()
{
}

SOCKET* SocketHandler::getSocket() {
	return &thisSocket;
}

void SocketHandler::connectToServer() {
	WSADATA wsaData;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int iResult;

	//--------------------------------------------
	// InitialisATION de Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("Erreur de WSAStartup: %d\n", iResult);
		exit(1);
	}
	// On va creer le socket pour communiquer avec le serveur
	thisSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (thisSocket == INVALID_SOCKET) {
		printf("Erreur de socket(): %ld\n\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		printf("Appuyez une touche pour finir\n");
		getchar();
		exit(1);
	}
	//--------------------------------------------
	// On va chercher l'adresse du serveur en utilisant la fonction getaddrinfo.
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;        // Famille d'adresses
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;  // Protocole utilisé par le serveur


	char host[16];
	char port[6];

	//----------------------------
	// Demander à l'usager l'adresse du serveur auquel il veut envoyer le message
	printf("Saisir l'adresse IP du serveur: ");
	gets_s(host);

	//check
	in_addr temp;
	if (inet_pton(AF_INET, host, &temp) <= 0) {
		printf("Adresse IP invalide.\n");
		system("pause");
	}

	printf("Saisir le port du serveur: ");
	gets_s(port);
	int n = 0;
	while (port[n] != NULL) {
		if (isalpha(port[n])) {
			printf("Port invalide.\n");
			system("pause");
			exit(5);
		}
		n++;
	}
	int port_int = atoi(port);
	if (!(port_int >= 5000 && port_int <= 5050)) {
		printf("Port invalide.\n");
		system("pause");
		exit(4);
	}

	// getaddrinfo obtient l'adresse IP du host donné
	iResult = getaddrinfo(host, port, &hints, &result);
	if (iResult != 0) {
		printf("Erreur de getaddrinfo: %d\n", iResult);
		WSACleanup();
		exit(1);
	}
	//---------------------------------------------------------------------		
	//On parcours les adresses retournees jusqu'a trouver la premiere adresse IPV4
	while ((result != NULL) && (result->ai_family != AF_INET))
		result = result->ai_next;

	//	if ((result != NULL) &&(result->ai_family==AF_INET)) result = result->ai_next;  

	//-----------------------------------------
	if (((result == NULL) || (result->ai_family != AF_INET))) {
		freeaddrinfo(result);
		printf("Impossible de recuperer la bonne adresse\n\n");
		WSACleanup();
		printf("Appuyez une touche pour finir\n");
		getchar();
		exit(1);
	}

	sockaddr_in *adresse;
	adresse = (struct sockaddr_in *) result->ai_addr;
	//----------------------------------------------------

	char adr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(adresse->sin_addr), adr, INET_ADDRSTRLEN);
	printf("Adresse trouvee pour le serveur %s : %s\n\n", host, adr);
	printf("Tentative de connexion au serveur %s avec le port %s\n\n", adr, port);

	// On va se connecter au serveur en utilisant l'adresse qui se trouve dans
	// la variable result.
	iResult = connect(thisSocket, result->ai_addr, (int)(result->ai_addrlen));
	if (iResult == SOCKET_ERROR) {
		printf("Impossible de se connecter au serveur %s sur le port %s\n\n", adr, port);
		freeaddrinfo(result);
		WSACleanup();
		printf("Appuyez une touche pour finir\n");
		getchar();
		exit(1);
	}

	printf("Connecte au serveur %s:%s\n\n", host, port);
	freeaddrinfo(result);

}

std::shared_ptr<SocketHandler> SocketHandler::thisInstance = std::shared_ptr<SocketHandler>();
