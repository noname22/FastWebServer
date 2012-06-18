#ifndef CACHED_H
#define CACHED_H

#include "requesthandler.h"

#include <memory>

class Cached: public RequestHandler
{
	private:
	std::string data;
	std::string contentType;
	std::string data;
	
	time_t lastUpdated;
	bool firstRun;

	std::shared_ptr<RequestHandler> rh;

	public:
	Cached(RequestHandler* rh);
	time_t GetLastUpdated(){ return lastUpdated; }
	void HandleRequest(Request& request);
};

#endif
