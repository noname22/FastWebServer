#include <flog.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fstream>
#include <stdexcept>

#include "staticresource.h"
#include "request.h"
#include "mime.h"
#include "tools.h"

bool StaticResource::RequiresUpdate(Request& request)
{
	try {
		return (modified != GetModified());
	} catch(const std::runtime_error e){
		FlogW(e.what());
	}

	return false;
}

StaticResource::StaticResource(std::string path, std::string contentType)
{
	this->contentType = contentType;
	detectMime = (contentType == "");

	this->path = path;
	modified = 0;
}

time_t StaticResource::GetModified()
{
	struct stat fileInfo;
	if(stat(path.c_str(), &fileInfo) != 0)
		throw std::runtime_error(Str("could not stat file: " << path));

	return fileInfo.st_mtime;
}

void StaticResource::HandleRequest(Request& request)
{
	try {
		modified = GetModified();
	} catch (const std::runtime_error e) {
		FlogW(e.what());
		return;
	} 

	if(detectMime) contentType = Mime::GetType(path);

	FlogV("(re)loading file: " << path << " | " << contentType);

	std::ifstream f(path);

	if(!f.good()){
		FlogW("could not read file: " << path);
		return;
	}

	const size_t blockSize = 4096;

	f.seekg(0, std::ios_base::end);
	size_t size = f.tellg();
	f.seekg(0);

	std::string responseCode = "200 OK";
	request.WriteRaw(request.GetHeader(responseCode, contentType, size));

	std::streampos pos = 0;
	std::string data;

	while((pos = f.tellg()) >= 0 && (size_t)pos < size - 1){ 
		data.resize(size - (size_t)pos < blockSize ? size - (size_t)pos : blockSize);
		f.read(&data[0], data.size());
		request.WriteRaw(data);
	}

	f.close();
}
