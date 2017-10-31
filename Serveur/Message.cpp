Message::Message(std::string user, std::string adress, std::string time, char message[200]) {
    user_ = user;
    address_ = adress;
    time_ = time;
    message_ = message;
}

std::ostream & operator<<(std::ostream &os, Message message) {
    std::cout << "[" << user_ << " - " << adress_ << " - " << time_ << "]: " << message_ << std::endl;
}


[Utilisateur 1 - 132.207.29.107:46202 - 2017-10-13@13:02:01]: Salut Utilisateur
