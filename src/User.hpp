
#ifndef _USER_HPP_
#define _USER_HPP_

class User
{
public:
    User(int fd);
    int get_fd(void);
    int get_tank_width(void);
    int get_tank_height(void);
    ~User(void);

private:
    int _fd;
    int _tank_width;
    int _tank_height;
};

#endif /* _USER_HPP_ */