#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>

class Request;
class RequestHandler
{
	public:
	virtual void RequiresUpdate(){ return false; }
	virtual void HandleRequest(Request& request){}
};

#endif
