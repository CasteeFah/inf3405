#pragma once
#include <memory>

class SocketHandler;
typedef std::shared_ptr<SocketHandler> Ptr_SocketHandler;

class SocketHandler
{
public:
	static Ptr_SocketHandler getInstance();
	SocketHandler();
	~SocketHandler();
	void connectToServer();
private: 
	static Ptr_SocketHandler thisInstance;
};
