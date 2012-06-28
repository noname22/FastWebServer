#ifndef DYNAMICRESOURCE_H
#define DYNAMICRESOURCE_H

#include <sstream>

#include "requesthandler.h"
#include "request.h"

class DynamicResource: public RequestHandler
{
	private:
	void HandleRequest(Request& request);

	protected:
	HttpHeader header;

	public:
	virtual void Generate(std::stringstream& stream, const Request& request) = 0;
};

#endif

