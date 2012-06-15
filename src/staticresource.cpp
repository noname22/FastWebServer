#include "staticresource.h"
#include "request.h"

#include <flog.h>

#include <fstream>

StaticResource::StaticResource(std::string path, std::string contentType)
{
	this->contentType = contentType;

	std::ifstream f(path);

	if(!f.good()){
		FlogW("could not read file: " << path);
		return;
	}

	f.seekg(0, std::ios_base::end);
	size_t size = f.tellg();
	f.seekg(0);

	data.resize(size);
	f.read(&data[0], size);

	f.close();
}

void StaticResource::HandleRequest(Request& request)
{
	request.WriteResponse("200 OK", contentType, data);
}
