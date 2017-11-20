#include "Message.h"

Message::Message() {
	user_ = "";
	address_ = "";
	time_ = "";
	message_ = "";
}

Message::Message(std::string user, std::string adress, std::string time, std::string message) {
    user_ = user;
    address_ = adress;
    time_ = time;
	message_ = message;
}

std::ostream & operator<<(std::ostream &os, Message message) {
    std::cout << "[" << message.user_ << " - " << message.address_ << " - " << message.time_ << "]: " << message.message_ << std::endl;
	return os;
}



// format :
// [Utilisateur 1 - 132.207.29.107:46202 - 2017-10-13@13:02:01]: Salut Utilisateur
