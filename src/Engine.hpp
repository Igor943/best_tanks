
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

/* C++ includes */
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

/* Proj includes */
#include "Field.hpp"
#include "Unit.hpp"

#define LOC_USER_TANK   1
#define SOC_USER_TANK   2
#define AI_TANK         3

class Engine
{
public:
    static void engine_init(void);
    static void engine_run(void);
private:
    void do_action();
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