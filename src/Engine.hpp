
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

/* C includes */
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>

/* C++ includes */
#include <vector>
#include <fstream>
#include <iostream>

/* Proj includes */
#include "Field.hpp"
#include "User.hpp"

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
extern std::ofstream log;
#endif

#endif /* _ENGINE_HPP_ */