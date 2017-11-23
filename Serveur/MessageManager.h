#pragma once
#include "Message.h"
#include <vector>
#include <memory>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\vector.hpp>
#define NUMBER_MESSAGES 15

class MessageManager;
typedef std::shared_ptr<MessageManager> Ptr_MessageManager;

class MessageManager
{
public:
	static Ptr_MessageManager getInstance();
	MessageManager();
	~MessageManager();
	char* getRecentMessages();
	void addMessage(Message newMessage);
	//void MessageManager::serialize();
	//void MessageManager::deserialize();

private: 
	static Ptr_MessageManager thisInstance;
	Message messages[15];
	size_t index;
	
};
