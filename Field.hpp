#ifndef _FIELD_HPP_
#define _FIELD_HPP_

class Field
{
public:
    Field(int x, int  y);
    char get_point(int x, int y);
    int get_arena_width();
    int get_arena_height();
    ~Field();
private:
    char** _arena;
    int _arena_width;
    int _arena_height;
};

#endif // _FIELD_HPP_