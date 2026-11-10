#include <ncurses.h>
#include <string>
#include "editor.h"
#include "../file.h"

using std::string;

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

void Editor::displayFile(File& file) {
  for (int i = 0; i < file.size(); i++) {
    const string& line = file.lineAt(i);
    mvprintw(i, 0, line.c_str());
    lines.push_back(line);
  }
  refresh();
  getsyx(cRow, cCol);
}

void Editor::moveCursor(int input) {
  int row = cRow, col = cCol;

  // TODO: Make more readable
  switch (input) {
    case KEY_DOWN:
      if (row < lines.size() - 1) {
        row++;

        string& line = lines.at(row);
        if (col > line.length()) col = line.length();
      }
      break;
    case KEY_UP:
      if (row > 0) row--;
      break;
    case KEY_LEFT:
      if (col > 0) col--;
      else {
        // NOTE: Case of reaching zero position of line
        if (row == 0) break;
        row--;

        const string& line = lines.at(row);
        col = line.length();
      };
      break;
    case KEY_RIGHT:
      if (row >= lines.size()) break;

      string& line = lines.at(row);
      
      if (col < line.length()) col++;
      else if (row < lines.size() - 1) {
        // NOTE: Case of reaching end of line
        col = 0;
        row++;
      };
      break;
  }
  
  move(row, col);
  cRow = row;
  cCol = col;
}

void Editor::run() {
  while(true) {
    int input = getch();
    
    if (input >= KEY_DOWN && input <= KEY_RIGHT) {
      moveCursor(input);
    }
    else {
      // Testing innstr;
      // char buff[64];
      // innstr(buff, sizeof(buff));
      // mvprintw(10, 10, buff);
    }

    refresh();
  }
}