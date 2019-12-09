
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 

unsigned int inet_addr(char *str)
{
    int a, b, c, d;
    char arr[4];
    sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
    arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d;
    return *(unsigned int *)arr;
}

int main(int ac, char **av) {    

    if (ac != 2) {
        printf("usage: ./a.out [192.168.190.111]\n");
        exit(EXIT_SUCCESS);
    }

    initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);

    int res;                    // temporary variable for checking the results of system calls
    int sock;                   // socket descriptor
    struct sockaddr_in addr;    // structure for address and port
    char *buf;                  // buffer and return value
    char *cry_mess;             // poiter for encrypt data
    /* Allocate space for the buffer */

    /* Request a socket from the kernel */
    

    /* Set the fields for the address structure */
    

    /* Set the parameters for the socket */
    while (1) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(3427);
        // addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        addr.sin_addr.s_addr = inet_addr(av[1]);
        int inp = getch();
        clear();
        res = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
        res = send(sock, &inp, 4, 0);
        printw("%input: d\nres: %d\n", inp, res);
        close(sock);
        refresh();
    }


    /* Get the answer */
    // res = recv(sock, buf, STDBUF, 0);

    /* Analyze the answer and depending on it:
    prepare a message about the status of the filter and send back
    or stop working with an error */



	endwin();

    return (0);
}