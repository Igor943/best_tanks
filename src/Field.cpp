
#include <stdlib.h>
#include "Field.hpp"

Field::Field(int width, int  height)
{
    _arena = (char **)malloc(sizeof(char *) * width);
	for (int i = 0; i < width; ++i) {
		_arena[i] = (char *)malloc(sizeof(char) * height);
	}
    _arena_width = width;
    _arena_height = height;
}

char Field::get_point(int x, int y)
{
    return (_arena[x][y]);
}

int Field::get_arena_width(void)
{
    return (_arena_width);
}

int Field::get_arena_height(void)
{
    return (_arena_height);
}

Field::~Field(void)
{
	for (int i = 0; i < _arena_width; ++i) {
		free(_arena[i]);
	}
    free(_arena);
}