#pragma once
#include <string>
#include "User.h"
#include <vector>

class UserManager
{
public:
	UserManager();
	~UserManager();
	User getUser(int userId);
	int findUserId(std::string username);
	void addUser(User user);

private:
	std::vector<User> users;
};

