#include "User.h"


User::User()
{
}


User::~User()
{
}

bool User::validateUser(User user)
{
	return ((userId == user.userId) && (password == user.password));
}

std::string User::getUserId()
{
	return userId;
}

std::string User::getPassword()
{
	return password;
}