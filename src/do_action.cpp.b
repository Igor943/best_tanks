//     else if (input == KEY_RIGHT)
//     {

//         for (int i = 0; i < unit.get_tank_height(); ++i)
//         {
//             _arena[cur_pos->x][cur_pos->y + i] = 0;
//             _arena[cur_pos->x + 1][cur_pos->y + i] = 0;
//         }
//         for (int i = 0; i < unit.get_tank_height(); ++i)
//         {
//             _arena[cur_pos->x + unit.get_tank_width()][cur_pos->y + i] = pic;
//             _arena[cur_pos->x + unit.get_tank_width() + 1][cur_pos->y + i] = pic;
//         }
//         unit.set_cur_point(cur_pos->x + 2, cur_pos->y);
//     }
//         else if (input == KEY_LEFT)
//     {
// #ifdef DEBUG_ON
//         _t_log << "--- Unit KEY_LEFT call\n";
// #endif
//         for (int i = 0; i < unit.get_tank_height(); ++i)
//         {
//             _arena[cur_pos->x + unit.get_tank_width() - 1][cur_pos->y + i] = 0;
//             _arena[cur_pos->x + unit.get_tank_width() - 2][cur_pos->y + i] = 0;
//         }
//         for (int i = 0; i < unit.get_tank_height(); ++i)
//         {
//             _arena[cur_pos->x - 1][cur_pos->y + i] = pic;
//             _arena[cur_pos->x - 2][cur_pos->y + i] = pic;
//         }
//         unit.set_cur_point(cur_pos->x - 2, cur_pos->y);
//     }
//     else if (input == KEY_UP)
//     {
// #ifdef DEBUG_ON
//         _t_log << "--- Unit KEY_UP call\n";
// #endif
//         for (int i = 0; i < unit.get_tank_width(); ++i)
//         {
//             _arena[cur_pos->x + i][cur_pos->y + unit.get_tank_height() - 1] = 0;
//         }
//         for (int i = 0; i < unit.get_tank_width(); ++i)
//         {
//             _arena[cur_pos->x + i][cur_pos->y - 1] = pic;
//         }
//         unit.set_cur_point(cur_pos->x, cur_pos->y - 1);
//     }
//     else if (input == KEY_DOWN)
//     {
// #ifdef DEBUG_ON
//         _t_log << "--- Unit KEY_DOWN call\n";
// #endif
//         for (int i = 0; i < unit.get_tank_width(); ++i)
//         {
//             _arena[cur_pos->x + i][cur_pos->y] = 0;
//         }
//         for (int i = 0; i < unit.get_tank_width(); ++i)
//         {
//             _arena[cur_pos->x + i][cur_pos->y + unit.get_tank_height()] = pic;
//         }
//         unit.set_cur_point(cur_pos->x, cur_pos->y + 1);
//     }