#include <string>
#include <iostream>
#include <Winsock2.h>

int main() {
	//saisir adresse ip
	std::string adresseIP;
	std::cout << "Veuillez ins�rer votre adresse IP";
	std::cin >> adresseIP;
	// TODO validate ip adress + connect
	//saisir le user
	std::string userId, password;
	std::cout << "Veuillez ins�rer votre nom d'usager";
	std::cin >> userId;
	std::cout << "Veuillez ins�rer votre mot de passe";
	std::cin >> password;
}