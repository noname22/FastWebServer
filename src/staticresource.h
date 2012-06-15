#ifndef STATICRESOURCE_H
#define STATICRESOURCE_H

#include "requesthandler.h"

class StaticResource: public RequestHandler
{
	private:
	std::string data;
	std::string contentType;
	bool detectMime;

	std::string path;
	time_t modified;

	void Load();

	public:
	StaticResource(std::string path, std::string contentType = "");
	void HandleRequest(Request& request);
};

#endif
