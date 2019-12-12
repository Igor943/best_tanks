
#include "Engine.hpp"

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

	Unit u1(LOC_USER_TANK, 0, 0);
	Unit u2(AI_TANK, 100, 30);
	Unit u3(AI_TANK, 25, 30);
	Unit u4(SOC_USER_TANK, 40, 0);
	Field display;

	struct pollfd fds[4];
	fds[0].fd = u1.get_fd();
	fds[0].events = POLLIN;
	fds[1].fd = u2.get_fd();
	fds[1].events = POLLIN;
	fds[2].fd = u3.get_fd();
	fds[2].events = POLLIN;
	fds[3].fd = u4.get_fd();
	fds[3].events = POLLIN;

	/* Main cycle */
	while(1)
	{
		res = poll(fds, 4, -1);
		if (res == -1)
		{
			perror("bad poll");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (fds[0].revents & POLLIN)
			{
				fds[0].revents = 0;
				display.do_action(u1);
			}
			if (fds[1].revents & POLLIN)
			{
				fds[1].revents = 0;
				display.do_action(u2);
			}
			if (fds[2].revents & POLLIN)
			{
				fds[2].revents = 0;
				display.do_action(u3);
			}
			if (fds[3].revents & POLLIN)
			{
				fds[3].revents = 0;
				display.do_action(u4);
			}
		}
		display.do_refresh();
	}
	endwin();
}