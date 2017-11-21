#include "Message.h"


std::string Message::timeToString(tm date) {
	std::string tempHour = std::to_string(date.tm_hour);
	std::string tempMin = std::to_string(date.tm_min);
	std::string tempSec = std::to_string(date.tm_sec);

	if (date.tm_hour < 10) {
		tempHour = "0" + tempHour;
	}
	if (date.tm_min < 10) {
		tempMin = "0" + tempMin;
	}
	if (date.tm_sec < 10) {
		tempSec = "0" + tempSec;
	}

	return  std::to_string(1900 + date.tm_year) + "-" + std::to_string(date.tm_mon + 1) + "-" +
			std::to_string(date.tm_mday) + "@" + tempHour + ":" + tempMin + ":" +  tempSec;
}

std::string Message::messageToString() {
	return  "[" + user_ + " - " + address_ + " - " + time_ + "]: " + message_;
};

Message::Message() {
	user_ = "";
	address_ = "";
	time_ = "";
	message_ = "";
}

Message::Message(std::string user, std::string adress, std::string port, tm time, std::string message) {
    user_ = user;
    address_ = adress + ":" + port;
	message_ = message;
	time_ = timeToString(time);
}

std::ostream & operator<<(std::ostream &os, Message message) {
    std::cout << "[" << message.user_ << " - " << message.address_ << " - " << message.time_ << "]: " << message.message_ << std::endl;
	return os;
}



// format :
// [Utilisateur 1 - 132.207.29.107:46202 - 2017-10-13@13:02:01]: Salut Utilisateur
