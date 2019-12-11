
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

											struct itimerspec new_value3;

											new_value3.it_interval.tv_sec = 0;
											new_value3.it_interval.tv_nsec = 150000000;
											new_value3.it_value.tv_sec = 1;
											new_value3.it_value.tv_nsec = 1;

											int tim3 = timerfd_create(CLOCK_MONOTONIC, 0);
											timerfd_settime(tim3, 0, &new_value3, NULL);

			fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);

	Unit u1(tim3, LOC_USER_TANK, 0, 0);
	Field display;

											struct itimerspec new_value;

											new_value.it_interval.tv_sec = 0;
											new_value.it_interval.tv_nsec = 250000000;
											new_value.it_value.tv_sec = 1;
											new_value.it_value.tv_nsec = 1;

											int tim = timerfd_create(CLOCK_MONOTONIC, 0);
											timerfd_settime(tim, 0, &new_value, NULL);

	Unit u2(tim, AI_TANK, 100, 30);

											struct itimerspec new_value2;

											new_value2.it_interval.tv_sec = 0;
											new_value2.it_interval.tv_nsec = 250000000;
											new_value2.it_value.tv_sec = 1;
											new_value2.it_value.tv_nsec = 1;

											int tim2 = timerfd_create(CLOCK_MONOTONIC, 0);
											timerfd_settime(tim2, 0, &new_value2, NULL);

	Unit u3(tim2, AI_TANK, 25, 30);



    int listener;
    struct sockaddr_in addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3427);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

 	bind(listener, (struct sockaddr *)&addr, sizeof(addr));
    listen(listener, 10);

	Unit u4(listener, SOC_USER_TANK, 40, 0);






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