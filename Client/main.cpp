#undef UNICODE
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Socket.h"

// Link avec ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


//extern function : send message
//					receive messages
//					user + 
//					pw >> new pw / current pw /new user/old user/ 
//					validation msg


int __cdecl main(int argc, char **argv)
{
	socket->connectToServer();
}