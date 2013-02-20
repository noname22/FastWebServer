#include <flog.h>
#include <sys/time.h>
#include <signal.h>

#include "server.h"
#include "staticresource.h"
#include "dynamicresource.h"
#include "cached.h"
#include "httpheader.h"

class DynamicTest : public DynamicResource
{
	public:
	void Generate(std::stringstream& data, const Request& request){
		data << "query " << request.GetQuery();
	}
};

// Cache:able dynamic resource test
// Returns the current server time in minutes. Output can be cached and is only refreshed
// when the value changes.

class ServerTime : public DynamicResource
{
	public:
	struct timeval t;	

	bool RequiresUpdate(Request& request){
		FlogD("checking if time page needs to be refrehsed");
		struct timeval ct;
		gettimeofday(&ct, NULL);
		if(ct.tv_sec / 60 > t.tv_sec / 60){
			FlogD("yep");
			return true;
		}

		FlogD("nope");
		return false;
	}

	void Generate(std::stringstream& data, const Request& request) {
		FlogD("refreshing time page");
		gettimeofday(&t, NULL);
		data << "server time: " << t.tv_sec / 60 << " minutes";
	}
};

void HandleSigHup(int signal)
{
	FlogD("HUP!");
}

int main()
{
	Flog_Init(SPANK_NAME);

	Flog_AddTargetStream(stdout, Flog_SDebug1 |Flog_SDebug2 | Flog_SDebug3 | Flog_SVerbose | Flog_SInfo | Flog_SWarning, 1);
	Flog_AddTargetStream(stderr, Flog_SError | Flog_SFatal, 1);

	FlogI("Welcome to " << SPANK_NAME << " " << SPANK_VERSION);

	Server server("0.0.0.0");

	// Memory cached static data
	server.AddRequestHandler("/", new Cached(new StaticResource("data/index.html")));
	server.AddRequestHandler("/favicon.ico", new Cached(new StaticResource("data/favicon.ico")));

	// Non-cached static data	
	server.AddRequestHandler("/heart.png", new StaticResource("data/heart.png"));

	// Non-cached dynamic page
	server.AddRequestHandler("/dynamic", new DynamicTest());

	// Cached dynamic page
	server.AddRequestHandler("/time", new Cached(new ServerTime()));
	
	FlogAssert( signal(SIGHUP, HandleSigHup) != SIG_ERR, "Could not set signal handler");

	server.ListenForever();

	return 0;
}
