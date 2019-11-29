
#ifndef _FIELD_HPP_
#define _FIELD_HPP_

class User;

class Field
{
public:
    Field(int width, int  height);
    char get_point(int x, int y);
    int get_arena_width(void);
    int get_arena_height(void);
    void do_action(User &user);
    ~Field(void);
private:
    char** _arena;
    int _arena_width;
    int _arena_height;
};

#endif /* _FIELD_HPP_ */