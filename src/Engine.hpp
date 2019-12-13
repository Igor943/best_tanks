
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

/* C includes */
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

/* C++ includes */
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

/* Proj includes */
#include "Field.hpp"
#include "Unit.hpp"
#include "Bullet.hpp"

#define LOC_USER_TANK   48
#define SOC_USER_TANK   49
#define AI_TANK         50

class Engine
{
public:
    Engine(void);
    ~Engine(void);
    int run(void);
    void do_action(Unit *unit);
    void move_unit(Unit *unit, int direction);
    int get_rand_move(void);
    void do_refresh(void);
private:
    int _arena_width;
    int _arena_height;
    char **_arena;
};

struct Point
{
    int x;
    int y;
};

#ifdef DEBUG_ON
extern std::ofstream _t_log;
#endif

#endif /* _ENGINE_HPP_ */