#include "dynamicresource.h"
#include "request.h"

void DynamicResource::HandleRequest(Request& request)
{
	std::stringstream stream;
	Generate(stream, request);
	request.WriteResponse(header, stream.str());
}
