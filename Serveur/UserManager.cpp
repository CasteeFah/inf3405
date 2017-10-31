#include "UserManager.h"

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
