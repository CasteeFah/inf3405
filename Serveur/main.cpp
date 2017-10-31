#include <string>
#include <iostream>
#include <Winsock2.h>
#include "SocketManager.h"

int main() {
	SocketManager socketManager;
	while (true) {
		sockaddr_in sinRemote;
		int nAddrSize = sizeof(sinRemote);
		SOCKET sd = accept(socketManager.getServerSocket(), (sockaddr*)&sinRemote, &nAddrSize);
	}
}