
#ifndef _FIELD_HPP_
#define _FIELD_HPP_

#include "Engine.hpp"

class User;

class Field
{
public:
    Field(void);
    void do_action(User &user);
    void do_refresh(void);
    ~Field(void);
private:
    char** _arena;
    int _arena_width;
    int _arena_height;
};

#endif /* _FIELD_HPP_ */