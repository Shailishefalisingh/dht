
#include <curses.h>
#include <readline/readline.h>
#include <stdlib.h>

void null(char* kek) {}

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
