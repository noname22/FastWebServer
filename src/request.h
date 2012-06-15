#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
	friend class Server;

	private:
	enum HttpMethod { HM_Get, HM_Post } method;
	std::string path;
	std::string query;

	int socket;

	void ParseRequest();

	public:
	const std::string& GetPath() const { return path; }
	const std::string& GetQuery() const { return query; }

	Request(int socket) : socket(socket) {}
	~Request(){ close(socket); }

	void WriteResponse(std::string responseCode, std::string contentType, const std::string& body);
};

#endif
