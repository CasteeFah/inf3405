#include "UserManager.h"

Ptr_UserManager UserManager::getInstance() {
	if (!thisInstance) {
		thisInstance = std::make_shared<UserManager>();
	}
	return thisInstance;
}

UserManager::UserManager() {
	deserialize();
}

UserManager::~UserManager() {
}

User UserManager::getUser(int userId) {
	return users[userId];
}

int UserManager::findUserId(std::string username) {
	for (int i = 0; i < users.size(); i++) {
		if (username == users[i].getUsername()) {
			return i;
		}
	}
	return -1;
}

void UserManager::addUser(User user) {
	users.push_back(user);
	serialize();
}

void UserManager::serialize() {
	std::ofstream ofs("user_file");

	{
		boost::archive::text_oarchive oa(ofs);
		oa << users;
	}
}

void UserManager::deserialize() {
	std::ifstream ifs("user_file");
	if (!ifs) {
		return;
	}
	boost::archive::text_iarchive ia(ifs);

	ia >> users;
}

std::shared_ptr<UserManager> UserManager::thisInstance = std::shared_ptr<UserManager>();
