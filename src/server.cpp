#include <stdexcept>
#include <flog.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "server.h"
#include "request.h"
#include "tools.h"

class Handle404 : public RequestHandler {
	void HandleRequest(Request& request){
		std::string str = Str("404, File Not Found: " << request.GetPath());
		request.WriteResponse("404 Not Found", "text/html", str);
	}
};
	
Server::Server(std::string addr, uint16_t port)
{
	this->port = port;
	this->addr = addr;

	handle404 = std::shared_ptr<RequestHandler>(new Handle404());
}

void Server::AddRequestHandler(std::string route, RequestHandler* rh)
{
	requestHandlers[route] = std::shared_ptr<RequestHandler>(rh);
}

void Server::DispatchRequest(int socket)
{
	Request request(socket);

	try {
		request.ParseRequest();

		auto handler = requestHandlers.find(request.GetPath());
		if(handler != requestHandlers.end()){
			handler->second->HandleRequest(request);
		} else {
			FlogI("404: " << request.GetPath());
			handle404->HandleRequest(request);
		}
	}

	catch (const std::runtime_error e){
		FlogW("Could not parse request: " << e.what());
	}
}

void Server::ListenForever()
{
	int sockfd, newsockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	FlogAssert(sockfd >= 0, "couldn't open socket");

	struct sockaddr_in serv_addr, cli_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(addr.c_str());
	serv_addr.sin_port = htons(port);

	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

	FlogAssert( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) >= 0, 
		"could not bind socket")

	FlogI(SERVER_NAME << " listening on " << addr << ":" << port);

	listen(sockfd, 5);

	socklen_t clilen = sizeof(cli_addr);

	while(1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		FlogAssert(newsockfd >= 0, "ERROR on accept");

		// handle new connection
		DispatchRequest(newsockfd);
	}

	close(sockfd);
	
}
