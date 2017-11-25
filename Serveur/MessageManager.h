#pragma once
#include "Message.h"
#include <vector>
#include <memory>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\vector.hpp>
#include "Message.h"
#define NUMBER_MESSAGES 15

class MessageManager;
typedef std::shared_ptr<MessageManager> Ptr_MessageManager;

class MessageManager
{
public:
	static Ptr_MessageManager getInstance();
	MessageManager();
	~MessageManager();
	std::string getRecentMessages();
	void addMessage(Message newMessage);
	void MessageManager::serialize();
	void MessageManager::deserialize();

private: 
	static Ptr_MessageManager thisInstance;
	std::vector<Message> messages;
	size_t index;
	
};
