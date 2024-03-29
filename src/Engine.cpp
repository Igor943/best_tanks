
#include "Engine.hpp"

const int __VOL = 4;

Engine::Engine(void)
{   
    initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
	int x, y;
    getmaxyx(stdscr, y, x);
    _arena = (char **)malloc(sizeof(char *) * x);
	for (int i = 0; i < x; ++i) {
		_arena[i] = (char *)malloc(sizeof(char) * y);
        memset(_arena[i], 0, y);
	}
    _arena_width = x;
    _arena_height = y;
}

Engine::~Engine(void)
{
	endwin();
	for (int i = 0; i < _arena_width; ++i) {
		free(_arena[i]);
	}
	free(_arena);
	//free vectors <------------------
}

int Engine::run(void)
{
	int res;

	std::vector<Unit *> vec_units;
	vec_units.push_back(new Unit(LOC_USER_TANK, 0, 0));
	vec_units.push_back(new Unit(SOC_USER_TANK, 40, 0));
	vec_units.push_back(new Unit(AI_TANK, 100, 30));
	vec_units.push_back(new Unit(AI_TANK, 25, 30));

	// Field display;

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
					do_action(vec_units[i]);
				}
			}
		}
		do_refresh();
	}
	return (EXIT_SUCCESS);
}

void Engine::do_action(Unit *unit)
{
#ifdef DEBUG_ON
    _t_log << "--- Field::do_action() call\n";
#endif
    uint64_t input_64;
    int input;
    if (unit->get_type() == LOC_USER_TANK)
    {
        read(unit->get_fd(), &input_64, 8);
        input = getch();
        if (input == -1) {
            return;
        }
        while (1) {
            // skip = getch();
            int ch;
            int skip = read(STDIN_FILENO, &ch, 1);
#ifdef DEBUG_ON
        _t_log << "--- Clearing stdin " << skip << '\n';
        _t_log.flush();
#endif
            if (skip == -1) {
                break;
            }
        }
    }
    else if (unit->get_type() == AI_TANK)
    {
        read(unit->get_fd(), &input_64, 8);
        input = get_rand_move(); 
    }
    else if (unit->get_type() == SOC_USER_TANK)
    {
        int buf = 0;
        int sock;
        sock = accept(unit->get_fd(), NULL, NULL);
        recv(sock, &buf, 4, 0);
#ifdef DEBUG_ON
        _t_log << "--- Socket get " << buf << '\n';
#endif
        close(sock);
        input = buf;
    }
#ifdef DEBUG_ON
    _t_log << "--- Unit's fd is " << unit->get_fd() << '\n';
    _t_log << "--- Unit input is " << input << '\n';
#endif
    if (input == 'q')
    {
        endwin();
        exit(EXIT_SUCCESS);
    }
    else {
        move_unit(unit, input);
    }
    // for (Bullet *cur : _vec_bullets) {
    //     Point const *pos = cur->get_cur_pos();
    //     if (cur->get_direction() == KEY_RIGHT) {
    //         _arena[pos->x][pos->y] = 0;
    //         _arena[pos->x + 2][pos->y] = '+';
    //         cur->set_cur_pos(pos->x + 2, pos->y);
    //     }
    // }
}

void Engine::move_unit(Unit *unit, int direction)
{
    Point const *cur_pos = unit->get_cur_pos(); 
    int tank_height = unit->get_tank_height();
    int tank_width = unit->get_tank_width();
    char pic = unit->get_type();
    if (direction == KEY_RIGHT)
    {
        for (int i = 0; i < tank_height; ++i)
        {
            _arena[cur_pos->x][cur_pos->y + i] = 0;
            _arena[cur_pos->x + 1][cur_pos->y + i] = 0;
            _arena[cur_pos->x + tank_width][cur_pos->y + i] = pic;
            _arena[cur_pos->x + tank_width + 1][cur_pos->y + i] = pic;
        }
        unit->set_cur_point(cur_pos->x + 2, cur_pos->y);
    }
    if (direction == KEY_LEFT)
    {
        for (int i = 0; i < tank_height; ++i)
        {
            _arena[cur_pos->x + tank_width - 1][cur_pos->y + i] = 0;
            _arena[cur_pos->x + tank_width - 2][cur_pos->y + i] = 0;
            _arena[cur_pos->x - 1][cur_pos->y + i] = pic;
            _arena[cur_pos->x - 2][cur_pos->y + i] = pic;
        }
        unit->set_cur_point(cur_pos->x - 2, cur_pos->y);
    }
    if (direction == KEY_DOWN)
    {
        for (int i = 0; i < tank_width; ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y] = 0;
            _arena[cur_pos->x + i][cur_pos->y + tank_height] = pic;
        }
        unit->set_cur_point(cur_pos->x, cur_pos->y + 1);
    }
    if (direction == KEY_UP)
    {
        for (int i = 0; i < tank_width; ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y + tank_height - 1] = 0;
            _arena[cur_pos->x + i][cur_pos->y - 1] = pic;
        }
        unit->set_cur_point(cur_pos->x, cur_pos->y - 1);
    }
}

int Engine::get_rand_move(void)
{
    int arr[4];
    arr[0] = KEY_RIGHT;
    arr[1] = KEY_LEFT;
    arr[2] = KEY_DOWN;
    arr[3] = KEY_UP;
    std::random_device device;  
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0,3);
    return (arr[distribution(generator)]);
}

void Engine::do_refresh(void)
{
    clear();
    for (int i = 0; i < _arena_width; ++i) {
        for (int j = 0; j < _arena_height; ++j) {
            if (_arena[i][j] == 0)
            {
                continue;
            }
            else
            {
                move(j, i);
                printw("%c", _arena[i][j]);
            }
        }
    }
    refresh();
}