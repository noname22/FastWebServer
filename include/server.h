#ifndef SERVER_H
#define SERVER_H

#define SERVER_NAME SPANK_NAME " " SPANK_VERSION

#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>

#include "requesthandler.h"

class Server
{
	private:
	uint16_t port;
	std::string addr;
	std::unordered_map<std::string, std::shared_ptr<RequestHandler>> requestHandlers;

	std::shared_ptr<RequestHandler> handle404;

	void DispatchRequest(int socket);

	public:
	Server(std::string addr = "127.0.0.1", uint16_t port = 8080);

	void AddRequestHandler(std::string route, RequestHandler* rh);
	void ListenForever();
};

#endif
