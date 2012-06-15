#include <sstream>
#include <string>
#include <stdexcept>

#include "server.h"
#include "request.h"
#include "tools.h"
	
void Request::ParseRequest()
{
	char buffer[8192];
	long ret = read(socket, buffer, sizeof(buffer) - 1);

	if(ret > 0 && ret < (long)sizeof(buffer) - 1)
		buffer[ret] = 0;
	else
		buffer[0] = 0;	

	std::stringstream parse(buffer);
	std::string str;

	parse >> str;

	if(str == "GET"){
		method = HM_Get;
		parse >> str;

		size_t pos = str.find("?");

		if(pos != std::string::npos){
			path = str.substr(0, pos);
			query = str.substr(pos + 1);
		}

		else path = str;
	}else{
		throw std::runtime_error(Str("Unknown request '" << str << "'"));
	}
}

void Request::WriteResponse(std::string responseCode, std::string contentType, const std::string& body)
{
	std::stringstream header;
	
	header << "HTTP/1.0 " << responseCode << "\r\n";
	header << "Server: " SERVER_NAME "\r\n";
	header << "Content-Type: " << contentType << "\r\n";
	header << "Content-Length: " << body.size() << "\r\n";
	header << "\r\n";

	write(socket, header.str().c_str(), header.str().size());
	write(socket, body.c_str(), body.size());
}
