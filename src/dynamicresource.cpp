#include "dynamicresource.h"
#include "request.h"

DynamicResource::DynamicResource()
{
	contentType = "text/html";
	responseCode = "200 OK";
}

void DynamicResource::SetContentType(const std::string& contentType)
{
	this->contentType = contentType;
}

void DynamicResource::SetResponseCode(const std::string& responseCode)
{
	this->responseCode = responseCode;
}

void DynamicResource::HandleRequest(Request& request)
{
	std::stringstream stream;
	Generate(stream, request);
	request.WriteResponse(responseCode, contentType, stream.str());
}
