
#include <curses.h>
#include <string.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <thread>
#include "ServerSocket.hpp"

void null(char* kek) {}

void handle_conn(ClientSocket cs) {
  char buf[1024];
  while (1) {
    if (cs.recv(buf, 1024) <= 0) {
      cs.close();
      break;
    } else {
      cs.send("Hello", 5);
    }
  }
}

void accept_connections() {
  ServerSocket s;
  s.bind("1234");
  while (true) {
    ClientSocket cs = s.accept();
    if (cs.valid()) {
      std::thread conn_handler(handle_conn, cs);
      conn_handler.detach();
    }
  }
}

int main(void) {
    initscr();

    int termwidth = getmaxx(stdscr);
    int termheight = getmaxy(stdscr);


    WINDOW *messages = newwin(termheight - 1, termwidth, 0, 0);
    box(messages, 0, 0);
    wrefresh(messages);
    scrollok(messages, TRUE);

    WINDOW *input = newwin(1, termwidth, termheight - 1, 0);
    scrollok(input, TRUE);
    keypad(input, TRUE);

    std::thread acceptor(accept_connections);
    acceptor.detach();

    rl_callback_handler_install("", null);
    rl_variable_bind("editing-mode", "vi");

    int BUF_SIZE = 140;
    char str[BUF_SIZE];
    do {
        strncpy(str, rl_line_buffer, BUF_SIZE);

        werase(input);
        mvwprintw(input, 0, 0, "%s", str);
        mvwchgat(input, 0, rl_point, 1, A_REVERSE, 0, NULL);
        wrefresh(input);
        
        rl_callback_read_char();
        if (rl_point == 0) {
            wprintw(messages, str);
            wprintw(messages, "\n");
            wrefresh(messages);
        }
        
    } while (str[0] != 'q');

    endwin();

    return 0;
}
