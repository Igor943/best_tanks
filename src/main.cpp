
#include "Engine.hpp"

#ifdef DEBUG_ON
std::ofstream _t_log;
#endif

int main(void)
{
#ifdef DEBUG_ON
	_t_log.open("./log.txt", std::ios::app);
	_t_log << "---=== START ===---\n";
#endif
	Engine eng;
	eng.run();
	return (0);
}

