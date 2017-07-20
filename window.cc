#include "window.h"


void beginGUI() {
  int ch, row, col;
  initscr();
  raw();
  keypad(stdscr, FALSE);
  nodelay(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_WHITE, COLOR_RED);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);
  init_pair(5, COLOR_WHITE, COLOR_WHITE);
  init_pair(6, COLOR_BLACK, COLOR_WHITE);
  while (true) {
    clear();
    bkgd(COLOR_PAIR(1));
    getmaxyx(stdscr,row,col);
//Draw Exit
    attron(A_BOLD);
    mvprintw(0, col - 6, "%s", "(esc)");
    attroff(A_BOLD);
//Draw Lines
    attron(COLOR_PAIR(5));
    move(0, 15);
    vline(' ', row);
    move(row - 1, 15);
    hline(' ', col - 15);
    attroff(COLOR_PAIR(5));
//Draw Controls
    move(row, col);
    attron(A_UNDERLINE);
    mvprintw(0, 4, "%s", "Controls");
    attroff(A_UNDERLINE);
    mvprintw(1, 1, "%s", "Lo");
//Draw Commands
    attron(COLOR_PAIR(6));
    move(row - 1, 16);
    attron(A_BLINK);
    printw("%s", "_");
    attroff(A_BLINK);
    move(row - 1, 16);
    attroff(COLOR_PAIR(6));




    refresh();
    usleep(5000);
  }

}
