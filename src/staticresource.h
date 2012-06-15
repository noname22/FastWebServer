#ifndef STATICRESOURCE_H
#define STATICRESOURCE_H

#include "requesthandler.h"

class StaticResource: public RequestHandler
{
	private:
	std::string data;
	std::string contentType;

	public:
	StaticResource(std::string path, std::string contentType);
	void HandleRequest(Request& request);
};

#endif
