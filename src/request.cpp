#include <string>
#include <stdexcept>

#include "server.h"
#include "request.h"
#include "tools.h"
	
std::string Request::GetHeader(const std::string& responseCode, const std::string& contentType, size_t bodySize)
{
	std::stringstream header;
	
	header << "HTTP/1.0 " << responseCode << "\r\n";
	header << "Server: " SERVER_NAME "\r\n";
	header << "Content-Type: " << contentType << "\r\n";
	header << "Content-Length: " << bodySize << "\r\n";
	header << "\r\n";

	return header.str();
}

Request::Request(const HttpMethod method, const std::string& path, const std::string& query)
{
	this->method = method;
	this->path = path;
	this->query = query;
}
