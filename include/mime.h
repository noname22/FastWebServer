#ifndef MIME_H
#define MIME_H

#include <string>
#include <magic.h>

class Mime
{
	public:
	static std::string GetType(std::string file);

	private:
	static magic_t cookie;
};

#endif
