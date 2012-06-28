#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>
#include <unordered_map>

class HttpHeader {
	std::unordered_map<std::string, std::string> headers;
	std::string responseCode;
	public:
	HttpHeader(const std::string& responseCode = "200 OK", const std::string& contentType = "text/html");
	void SetHeader(const std::string& key, const std::string& value);
	std::string ToString (size_t bodyLength) const;
};

#endif
