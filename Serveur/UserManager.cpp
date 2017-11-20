#include "UserManager.h"

Ptr_UserManager UserManager::getInstance() {
	if (!thisInstance) {
		thisInstance = std::make_shared<UserManager>();
	}
	return thisInstance;
}

UserManager::UserManager() {
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
}

std::shared_ptr<UserManager> UserManager::thisInstance = std::shared_ptr<UserManager>();
