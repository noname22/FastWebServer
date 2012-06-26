#ifndef DYNAMICRESOURCE_H
#define DYNAMICRESOURCE_H

#include <sstream>

#include "requesthandler.h"
#include "request.h"

class DynamicResource: public RequestHandler
{
	private:
	void HandleRequest(Request& request);
	std::string contentType;
	std::string responseCode;

	protected:
	void SetContentType(const std::string& contentType);
	void SetResponseCode(const std::string& responseCode);

	public:
	DynamicResource();
	virtual void Generate(std::stringstream& stream, const Request& request) = 0;
};

#endif

