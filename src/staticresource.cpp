#include "staticresource.h"
#include "request.h"

#include <flog.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fstream>

void StaticResource::Load()
{
	struct stat fileInfo;
	stat(path.c_str(), &fileInfo);

	if(access(path.c_str(), F_OK) == -1){
		FlogW("could not stat file: " << path);
		return;
	}

	if(modified == fileInfo.st_mtime){
		return;
	}

	FlogV("(re)loading file: " << path);

	modified = fileInfo.st_mtime;

	data.clear();

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

StaticResource::StaticResource(std::string path, std::string contentType)
{
	this->contentType = contentType;
	this->path = path;
	modified = 0;

	Load();
}

void StaticResource::HandleRequest(Request& request)
{
	Load();
	request.WriteResponse("200 OK", contentType, data);
}
