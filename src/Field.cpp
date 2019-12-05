
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
    log << "--- width screen: " << _arena_width << '\n';
    log << "--- height screen: " << _arena_height << '\n';
#endif
}

void Field::do_action(User &user)
{
#ifdef DEBUG_ON
    log << "--- Field::do_action() call\n";
#endif
    uint64_t input;
    int r = read(user.get_fd(), &input, 8);
    Point const *cur_pos = user.get_cur_pos();
    // input = getch();
#ifdef DEBUG_ON
    log << "--- User's fd is " << user.get_fd() << '\n';
    log << "--- User input is " << input << '\n';
    // log << "--- User sayed " << input << '\n';
#endif
    if (input == 'q')
    {
        endwin();
        exit(EXIT_SUCCESS);
    }
    else if (input == KEY_RIGHT)
    {
#ifdef DEBUG_ON
        log << "--- User KEY_RIGHT call\n";
#endif
        for (int i = 0; i < user.get_tank_height(); ++i)
        {
            _arena[cur_pos->x][cur_pos->y + i] = 0;
        }
        for (int i = 0; i < user.get_tank_height(); ++i)
        {
            _arena[cur_pos->x + user.get_tank_width()][cur_pos->y + i] = 'T';
        }
        user.set_cur_point(cur_pos->x + 1, cur_pos->y);
    }
        else if (input == KEY_LEFT)
    {
#ifdef DEBUG_ON
        log << "--- User KEY_LEFT call\n";
#endif
        for (int i = 0; i < user.get_tank_height(); ++i)
        {
            _arena[cur_pos->x + user.get_tank_width() - 1][cur_pos->y + i] = 0;
        }
        for (int i = 0; i < user.get_tank_height(); ++i)
        {
            _arena[cur_pos->x - 1][cur_pos->y + i] = 'T';
        }
        user.set_cur_point(cur_pos->x - 1, cur_pos->y);
    }
    else if (input == KEY_UP)
    {
#ifdef DEBUG_ON
        log << "--- User KEY_UP call\n";
#endif
        for (int i = 0; i < user.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y + user.get_tank_height() - 1] = 0;
        }
        for (int i = 0; i < user.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y - 1] = 'T';
        }
        user.set_cur_point(cur_pos->x, cur_pos->y - 1);
    }
    else if (input == KEY_DOWN)
    {
#ifdef DEBUG_ON
        log << "--- User KEY_DOWN call\n";
#endif
        for (int i = 0; i < user.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y] = 0;
        }
        for (int i = 0; i < user.get_tank_width(); ++i)
        {
            _arena[cur_pos->x + i][cur_pos->y + user.get_tank_height()] = 'T';
        }
        user.set_cur_point(cur_pos->x, cur_pos->y + 1);
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

Field::~Field(void)
{
	for (int i = 0; i < _arena_width; ++i) {
		free(_arena[i]);
	}
    free(_arena);
}