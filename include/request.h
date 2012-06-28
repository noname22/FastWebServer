#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#include "httpheader.h"

class Request {
	friend class Server;

	protected:
	enum HttpMethod { HM_Get, HM_Post } method;
	std::string path;
	std::string query;

	public:
	const std::string& GetPath() const { return path; }
	const std::string& GetQuery() const { return query; }
	const HttpMethod GetMethod(){ return method; }
	
	std::string GetHeader(const std::string& reponseCode, const std::string& contentType, size_t bodySize);

	Request(){ method = HM_Get; }
	Request(HttpMethod method, const std::string& path, const std::string& query);

	virtual ~Request(){}

	virtual void WriteResponse(const HttpHeader& header, const std::string& body) = 0;
	virtual void WriteRaw(const std::string& body) = 0;
};

#endif
