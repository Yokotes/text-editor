#include <ncurses.h>
#include "editor.h"
#include "../file.h"

Editor::Editor() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}

Editor::~Editor() {
  endwin();
}

Editor& Editor::getInstance() {
  static Editor instance{};
  return instance;
}

void Editor::displayFile(File file) {
  for (int i = 0; i < file.size(); i++) {
    mvprintw(i, 0, file.lineAt(i).c_str());
  }
}

void Editor::run() {
  getch();
}