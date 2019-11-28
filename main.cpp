
#include "main.hpp"
//try work hard2

int gx = 0, gy = 0;

struct User {

	int x;
	int y;
	User() {x = 0; y = 0;}
	~User() {}
};

void ft_print(std::vector<std::vector<char>> &arr) {

	clear();
	for (int i = 0; i < gx; ++i) {
		for (int j = 0; j < gy; ++j) {
			if (arr[i][j] == 'H') {
				move(i, j);
				printw("H");
			} else if (arr[i][j] == '-') {
				move(i, j);
				printw("-");
			} else if (arr[i][j] == '|') {
				move(i, j);
				printw("|");
			}
		}
	}
	refresh();
}

int main() {
	int* arr;
    arr=new int[4];

	int user_input;
	User u1;
	// char **arr;

    initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	getmaxyx(stdscr, gx, gy);


	// std::vector<std::vector<char>> arr(gx);
	// for (auto it = arr.begin(); it != arr.end(); ++it) {
	// 	std::vector<char> tmp(gy);
	// 	arr.push_back(tmp);
	// }	

	// arr = (char **)malloc(sizeof(char *) * gx);
	// for (int i = 0; i < gx; ++i) {
	// 	arr[i] = (char *)malloc(sizeof(char) * gy);
	// }

	for (int i = 0; i < gx; ++i) {
		for (int j = 0; j < gy; ++j) {
			arr[i][j] = 0;
		}
	}

	printw("START %d %d\n", gx, gy);
	refresh();

	while (1) {
		user_input = getch();
		if (user_input == 'q') {
			break;
		} else if (user_input == KEY_UP) {
			// arr[u1.x][u1.y] = '|';
			u1.x -= 1;
		} else if (user_input == KEY_DOWN) {
			arr[u1.x][u1.y] = '|';
			arr[u1.x][u1.y + 1] = ' ';
			arr[u1.x][u1.y + 2] = '|';
			arr[u1.x][u1.y + 3] = '|';
			arr[u1.x][u1.y + 4] = ' ';
			arr[u1.x][u1.y + 5] = '|';
			u1.x += 1;
		} else if (user_input == KEY_RIGHT) {
			arr[u1.x][u1.y] = '-';
			arr[u1.x][u1.y + 1] = '-';
			arr[u1.x + 1][u1.y] = '-';
			arr[u1.x + 1][u1.y + 1] = '-';
			arr[u1.x + 2][u1.y] = '-';
			arr[u1.x + 2][u1.y + 1] = '-';
			u1.y += 2;
		} else if (user_input == KEY_LEFT) {
			arr[u1.x + 2][u1.y + 5] = '-';
			arr[u1.x + 2][u1.y + 4] = '-';
			arr[u1.x + 1][u1.y + 5] = '-';
			arr[u1.x + 1][u1.y + 4] = '-';
			arr[u1.x][u1.y + 5] = '-';
			arr[u1.x][u1.y + 4] = '-';
			u1.y -= 2;
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 6; ++j) {
				arr[u1.x + i][u1.y + j] = 'H';
			}
		}
		// arr[u1.x][u1.y] = 'H';
		// arr[u1.x + 1][u1.y] = 'H';
		// arr[u1.x + 2][u1.y] = 'H';
		// arr[u1.x][u1.y + 1] = 'H';
		// arr[u1.x][u1.y + 2] = 'H';
		// arr[u1.x][u1.y + 3] = 'H';
		// arr[u1.x][u1.y + 4] = 'H';
		// arr[u1.x][u1.y + 5] = 'H';
		ft_print(arr);
	}
	endwin();

    return (0);
}
