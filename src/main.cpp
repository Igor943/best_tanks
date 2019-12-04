
#include "Engine.hpp"

#ifdef DEBUG_ON
std::ofstream log;
#endif

int main(void)
{
#ifdef DEBUG_ON
	log.open("./log.txt", std::ios::app);
	log << "---=== START ===---\n";
#endif
	Engine::engine_init();
	Engine::engine_run();
	//Engine::engine_stop();
	return (0);
}