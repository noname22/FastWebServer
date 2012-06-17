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

	protected:
	std::string GetHeader(const std::string& reponseCode, const std::string& contentType, const std::string& body);
	bool closeSocket;

	public:
	const std::string& GetPath() const { return path; }
	const std::string& GetQuery() const { return query; }

	virtual Request(int socket) : socket(socket) { closeSocket = true; }
	virtual ~Request(){ if(closeSocket) close(socket); }

	virtual void WriteResponse(std::string responseCode, std::string contentType, const std::string& body);
	void WriteRawToSocket(std::string& body);
};

#endif
