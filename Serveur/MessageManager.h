#pragma once
#include "Message.h"
#include <vector>

class MessageManager
{
public:
	MessageManager();
	~MessageManager();
	char* getRecentMessages(); 
};

