#include "MessageManager.h"

Ptr_MessageManager MessageManager::getInstance(){
	if (!thisInstance) {
		thisInstance = std::make_shared<MessageManager>();
	}
	return thisInstance;
}

MessageManager::MessageManager() {
	index = 0;
}

MessageManager::~MessageManager(){
}

char* MessageManager::getRecentMessages(){
	for (size_t i = 0; i < NUMBER_MESSAGES; i++) 
	{
		//serialize(messages[i])
		//return 
	}
	return "aa";
}

void MessageManager::addMessage(Message newMessage){
	messages[index] = newMessage;
	index = ++index%NUMBER_MESSAGES;
}

void MessageManager::serialize() {
	std::ofstream ofs("user_file");

	{
		boost::archive::text_oarchive oa(ofs);
		oa << users;
	}
}

void MessageManager::deserialize() {
	std::ifstream ifs("user_file");
	boost::archive::text_iarchive ia(ifs);

	ia >> users;
}

std::shared_ptr<MessageManager> MessageManager::thisInstance = std::shared_ptr<MessageManager>();
