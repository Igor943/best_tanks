
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <vector>

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

#endif //_ENGINE_HPP_