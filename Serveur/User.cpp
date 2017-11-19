#include "User.h"
#include <string>


User::User()
{
}

User::User(std::string newUsername , std::string newPassword )
{
	username = newUsername;
	password = newPassword;
}


User::~User()
{
}

std::string User::getUsername()
{
	return username;
}

std::string User::getPassword()
{
	return password;
}