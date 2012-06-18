#include "cached.h"

class CachingRequest: Request {
	public:
	std::string* str;
	
	CachingRequest(){ closeSocket = false; }
	
	void WriteResponse(std::string responseCode, std::string contentType, const std::string& body) {
		*str = GetHeader(responseCode, contentType, body);
		*str += body;
	}
};


Cached::Cached(RequestHandler* rh)
{
	this->rh = std::shared_ptr<RequestHandler>(rh);
	firstRun = true;
}

void Cached::HandleRequest(Request& request)
{
	if(firstRun || rh->NeedsUpdate()){
		firstRun = false;
		data.clear();

		CachingRequest cr = request;
		cr.str = &data;

		rh->handleRequest(cr);
	}

	request.WriteRawToSocket(data);
}
