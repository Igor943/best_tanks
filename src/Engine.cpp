
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
	Unit u1(STDIN_FILENO, LOC_USER_TANK, 0, 0);
	Field display;

											struct itimerspec new_value;

											new_value.it_interval.tv_sec = 0;
											new_value.it_interval.tv_nsec = 2147483647 / 20;
											new_value.it_value.tv_sec = 1;
											new_value.it_value.tv_nsec = 1;

											int tim = timerfd_create(CLOCK_MONOTONIC, 0);
											timerfd_settime(tim, 0, &new_value, NULL);

	Unit u2(tim, AI_TANK, 100, 30);

											struct itimerspec new_value2;

											new_value2.it_interval.tv_sec = 0;
											new_value2.it_interval.tv_nsec = 2147483647 / 10;
											new_value2.it_value.tv_sec = 1;
											new_value2.it_value.tv_nsec = 1;

											int tim2 = timerfd_create(CLOCK_MONOTONIC, 0);
											timerfd_settime(tim2, 0, &new_value2, NULL);

	Unit u3(tim2, AI_TANK, 25, 30);

	struct pollfd fds[3];
	fds[0].fd = u1.get_fd();
	fds[0].events = POLLIN;
	fds[1].fd = u2.get_fd();
	fds[1].events = POLLIN;
	fds[2].fd = u3.get_fd();
	fds[2].events = POLLIN;

	/* Main cycle */
	while(1)
	{
		res = poll(fds, 3, -1);
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
		}
		display.do_refresh();
	}
	endwin();
}