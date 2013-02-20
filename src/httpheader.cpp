#include "httpheader.h"
#include "server.h"
#include <sstream>

HttpHeader::HttpHeader(const std::string& responseCode, const std::string& contentType)
{
	this->responseCode = responseCode;
	headers["Content-Type"] = contentType;
}

void HttpHeader::SetHeader(const std::string& key, const std::string& value)
{
	headers[key] = value;
}

std::string HttpHeader::ToString(size_t bodyLength) const
{
	std::stringstream header;

	header << "HTTP/1.0 " << responseCode << "\r\n";
	header << "Server: " SERVER_NAME "\r\n";
	header << "Content-Length: " << bodyLength << "\r\n";

	for(auto h : headers)
		header << h.first << ": " << h.second << "\r\n";

	header << "\r\n";

	return header.str();
}

