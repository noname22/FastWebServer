#ifndef STATICRESOURCE_H
#define STATICRESOURCE_H

#include "requesthandler.h"

class StaticResource: public RequestHandler
{
	private:
	bool detectMime;
	std::string contentType;
	std::string path;

	time_t modified;
	time_t GetModified();

	public:
	StaticResource(std::string path, std::string contentType = "");
	bool RequiresUpdate(Request& request);
	void HandleRequest(Request& request);
};

#endif
