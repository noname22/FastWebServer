#include <flog.h>

#include "server.h"
#include "staticresource.h"
#include "dynamicresource.h"

class DynamicTest : public DynamicResource
{
	public:
	void Generate(std::stringstream& data, const Request& request){
		data << "query: " << request.GetQuery();
	}
};

int main()
{
	Flog_Init(SPANK_NAME);

	Flog_AddTargetStream(stdout, Flog_SDebug1 |Flog_SDebug2 | Flog_SDebug3 | Flog_SVerbose | Flog_SInfo | Flog_SWarning, 1);
	Flog_AddTargetStream(stderr, Flog_SError | Flog_SFatal, 1);

	FlogI("Welcome to " << SPANK_NAME << " " << SPANK_VERSION);

	Server server;

	server.AddRequestHandler("/", new StaticResource("data/index.html", "text/html"));
	server.AddRequestHandler("/heart.png", new StaticResource("data/heart.png", "image/png"));
	server.AddRequestHandler("/favicon.ico", new StaticResource("data/favicon.ico", "image/x-icon"));
	server.AddRequestHandler("/dynamic", new DynamicTest());

	server.ListenForever();

	return 0;
}
