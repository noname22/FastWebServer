#ifndef SOCKETREQUEST_H
#define SOCKETREQUEST_H

#include "request.h"

class SocketRequest : public Request {
	friend class Server;
	int socket;

	void ParseRequest();

	public:
	SocketRequest(int socket) : socket(socket) {}
	~SocketRequest(){ close(socket); }

	void WriteResponse(std::string responseCode, std::string contentType, const std::string& body);
	void WriteRaw(const std::string& body);
};

#endif
