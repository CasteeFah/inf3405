#include "MessageManager.h"

Ptr_MessageManager MessageManager::getInstance(){
	if (!thisInstance) {
		thisInstance = std::make_shared<MessageManager>();
	}
	return thisInstance;
}

MessageManager::MessageManager() {
	deserialize();
}

MessageManager::~MessageManager(){
}

std::string MessageManager::getRecentMessages(){
	size_t i = 0;
	std::string messagesTmp = "";
	if (!(messages.size() < NUMBER_MESSAGES)) {
		i = messages.size() - NUMBER_MESSAGES;
	}

	for (i; i < messages.size(); i++)
	{
		messagesTmp += messages[i].messageToString() + "\n";
	}
	return messagesTmp;
}

void MessageManager::addMessage(Message newMessage){
	messages.push_back(newMessage);
	serialize();
}

void MessageManager::serialize() {
	std::ofstream ofs("message_file");

	{
		boost::archive::text_oarchive oa(ofs);
		oa << messages;
	}
}

void MessageManager::deserialize() {
	std::ifstream ifs("message_file");
	if (!ifs) {
		return;
	}
	boost::archive::text_iarchive ia(ifs);

	ia >> messages;
} 

std::shared_ptr<MessageManager> MessageManager::thisInstance = std::shared_ptr<MessageManager>();
