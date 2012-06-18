#include "cached.h"
#include "request.h"

#include <flog.h>

class CachingRequest: public Request {
	public:
	std::string* str;

	CachingRequest(HttpMethod method, const std::string& path, const std::string& query) : Request(method, path, query){}
	
	void WriteResponse(std::string responseCode, std::string contentType, const std::string& body) {
		*str = GetHeader(responseCode, contentType, body.size());
		*str += body;
	}

	void WriteRaw(const std::string& body){ *str += body; }
};


Cached::Cached(RequestHandler* rh)
{
	this->rh = std::shared_ptr<RequestHandler>(rh);
	firstRun = true;
}

void Cached::HandleRequest(Request& request)
{
	if(firstRun || rh->RequiresUpdate(request)){
		firstRun = false;
		data.clear();

		CachingRequest cr(request.GetMethod(), request.GetPath(), request.GetQuery());
		cr.str = &data;

		rh->HandleRequest(cr);
	}

	request.WriteRaw(data);
}
