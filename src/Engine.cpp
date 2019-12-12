
#include "Engine.hpp"

const int __VOL = 4;

void Engine::engine_init(void)
{   
    initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

void Engine::engine_run(void)
{
	int res;

	std::vector<Unit *> vec_units;
	vec_units.push_back(new Unit(LOC_USER_TANK, 0, 0));
	vec_units.push_back(new Unit(SOC_USER_TANK, 40, 0));
	vec_units.push_back(new Unit(AI_TANK, 100, 30));
	vec_units.push_back(new Unit(AI_TANK, 25, 30));

	Field display;

	struct pollfd fds[__VOL];
	for (int i = 0; i < __VOL; ++i)
	{
		fds[i].fd = vec_units[i]->get_fd();
		fds[i].events = POLLIN;
	}

	/* Main cycle */
	while (1)
	{
		res = poll(fds, __VOL, -1);
		if (res == -1)
		{
			perror("bad poll");
			exit(EXIT_FAILURE);
		}
		else
		{
			for (int i = 0; i < __VOL; ++i)
			{
				if (fds[i].revents & POLLIN)
				{
					fds[i].revents = 0;
					display.do_action(vec_units[i]);
				}
			}
		}
		display.do_refresh();
	}
	endwin();
}