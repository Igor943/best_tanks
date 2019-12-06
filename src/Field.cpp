
#include "Field.hpp"

Field::Field(void)
{
    int x, y;
    getmaxyx(stdscr, y, x);
    _arena = (char **)malloc(sizeof(char *) * x);
	for (int i = 0; i < x; ++i) {
		_arena[i] = (char *)malloc(sizeof(char) * y);
        memset(_arena[i], 0, y);
	}
    _arena_width = x;
    _arena_height = y;
#ifdef DEBUG_ON
    _t_log << "--- width screen: " << _arena_width << '\n';
    _t_log << "--- height screen: " << _arena_height << '\n';
#endif
}

void Field::do_action(Unit &unit)
{
#ifdef DEBUG_ON
    _t_log << "--- Field::do_action() call\n";
#endif
    uint64_t input_64;
    int input;
    char pic = '0';
    if (unit.get_type() == LOC_USER_TANK)
    {
        input = getch();
        pic = 'F';
    }
    else if (unit.get_type() == AI_TANK)
    {
        read(unit.get_fd(), &input_64, 8);
        input = get_rand_move(); 
        pic = 'A';
    }
    else if (unit.get_type() == SOC_USER_TANK)
    {
        read(unit.get_fd(), &input_64, 8);
        // input = get_rand_move(); 
        input = KEY_RIGHT; 
        pic = 'B';
    }
#ifdef DEBUG_ON
    _t_log << "--- Unit's fd is " << unit.get_fd() << '\n';
    _t_log << "--- Unit input is " << input << '\n';
#endif
    Point const *cur_pos = unit.get_cur_pos(); 
    if (input == 'q')
    {
        endwin();
        exit(EXIT_SUCCESS);
    }
    else if (input == KEY_RIGHT)
    {
#ifdef DEBUG_ON
        _t_log << "--- Unit KEY_RIGHT call\n";
#endif
        for (int i = 0; i < unit.get_tank_height(); ++i)
        {
            _arena[cur_pos->x][cur_pos->y + i] = 0;
        }
        for (int i = 0; i < unit.get_tank_height(); ++i)
        {
            _arena[cur_pos->x + unit.get_tank_width()][cur_pos->y + i] = pic;
        }
        unit.set_cur_point(cur_pos->x + 1, cur_pos->y);
    }
        else if (input == KEY_LEFT)
    {
#ifdef DEBUG_ON
        _t_log << "--- Unit KEY_LEFT call\n";
#endif
        for (int i = 0; i < unit.get_tank_height(); ++i)
        {
            _arena[cur_pos->x + unit.get_tank_width() - 1][cur_pos->y + i] = 0;
        }
        for (int i = 0; i < unit.get_tank_height(); ++i)
        {
            _arena[cur_pos->x - 1][cur_pos->y + i] = pic;
        }
        unit.set_cur_point(cur_pos->x - 1, cur_pos->y);
    }
    else if (input == KEY_UP)
    {
#ifdef DEBUG_ON
        _t_log << "--- Unit KEY_UP call\n";
#endif
        for (int i = 0; i < unit.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y + unit.get_tank_height() - 1] = 0;
        }
        for (int i = 0; i < unit.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y - 1] = pic;
        }
        unit.set_cur_point(cur_pos->x, cur_pos->y - 1);
    }
    else if (input == KEY_DOWN)
    {
#ifdef DEBUG_ON
        _t_log << "--- Unit KEY_DOWN call\n";
#endif
        for (int i = 0; i < unit.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y] = 0;
        }
        for (int i = 0; i < unit.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y + unit.get_tank_height()] = pic;
        }
        unit.set_cur_point(cur_pos->x, cur_pos->y + 1);
    }
}

void Field::do_refresh(void)
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

int Field::get_rand_move(void)
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

Field::~Field(void)
{
	for (int i = 0; i < _arena_width; ++i) {
		free(_arena[i]);
	}
    free(_arena);
}