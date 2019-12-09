
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

int main() {    

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
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
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