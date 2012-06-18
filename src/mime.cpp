#include <magic.h>
#include <flog.h>

#include "mime.h"
	
magic_t Mime::cookie = 0;

std::string Mime::GetType(std::string file)
{
	if(!cookie){
		FlogAssert( (cookie = magic_open(MAGIC_MIME_TYPE)) != NULL,
			"could not find libmagic library of mime types");

		FlogAssert( magic_load(cookie, NULL) == 0, 
			"could not load magic database");
	}
	
	const char* desc = magic_file(cookie, file.c_str());

	if(desc) return desc;

	FlogW("could not determine mime-type of: " << file);
	FlogV("libmagic error: " << magic_error(cookie));
	return "application/octet-stream";
}
