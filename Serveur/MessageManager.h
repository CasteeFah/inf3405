#pragma once
#include "Message.h"
#include <vector>
#include <memory>
#define NUMBER_MESSAGES 15

class MessageManager
{
public:
	static Ptr_MessageManager getInstance();
	~MessageManager();
	char* getRecentMessages();
	void addMessage(Message newMessage);
private: 
	MessageManager();
	static Ptr_MessageManager thisInstance;
	Message messages[15];
	size_t index;
	
};

typedef std::shared_ptr<MessageManager> Ptr_MessageManager;