#pragma once
#include <string>
#include "User.h"
#include <vector>
#include <memory>


class UserManager
{
public:
	static Ptr_UserManager getInstance();
	~UserManager();
	User getUser(int userId);
	int findUserId(std::string username);
	void addUser(User user);

private:
	UserManager();

	std::vector<User> users;
	static Ptr_UserManager thisInstance;
};

typedef std::shared_ptr<UserManager> Ptr_UserManager;
