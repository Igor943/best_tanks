
#include "Engine.hpp"

void Engine::engine_init(void)
{   
    initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
}

void Engine::engine_run(void)
{
	int res;
	User u1(STDIN_FILENO, 0, 0);
	Field display;

	struct pollfd fds[2];
	fds[0].fd = u1.get_fd();
	fds[0].events = POLLIN;
	fds[1].fd = 99; /* socket conection will be here */
	fds[1].events = POLLIN;

	/* Main cycle */
	while(1)
	{
		res = poll(fds, 1, -1);
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
		}
		display.do_refresh();
	}
	endwin();
}