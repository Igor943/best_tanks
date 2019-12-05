
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

	struct itimerspec new_value;

	new_value.it_interval.tv_sec = 1;
	new_value.it_interval.tv_nsec = 1;
	new_value.it_value.tv_sec = 1;
	new_value.it_value.tv_nsec = 1;

	int tim = timerfd_create(CLOCK_MONOTONIC, 0);
	timerfd_settime(tim, 0, &new_value, NULL);

	User u2(tim, 0, 15);

	struct pollfd fds[2];
	fds[0].fd = u1.get_fd();
	fds[0].events = POLLIN;
	fds[1].fd = u2.get_fd(); /* socket conection will be here */
	fds[1].events = POLLIN;

	/* Main cycle */
	while(1)
	{
		res = poll(fds, 2, -1);
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
		}
		display.do_refresh();
	}
	endwin();
}