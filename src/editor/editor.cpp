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
}

void Editor::moveCursor(int input) {
  int initRow, initCol, cRow, cCol;
  getsyx(initRow, initCol);
  
  cRow = initRow;
  cCol = initCol;

  // TODO: Make more readable
  switch (input) {
    case KEY_DOWN:
      if (cRow < lines.size() - 1) {
        cRow++;

        string& line = lines.at(cRow);
        if (cCol > line.length()) cCol = line.length();
      }
      break;
    case KEY_UP:
      if (cRow > 0) cRow--;
      break;
    case KEY_LEFT:
      if (cCol > 0) cCol--;
      else {
        // NOTE: Case of reaching zero position of line
        if (cRow == 0) break;
        cRow--;

        const string& line = lines.at(cRow);
        cCol = line.length();
      };
      break;
    case KEY_RIGHT:
      if (cRow >= lines.size()) break;

      string& line = lines.at(cRow);
      
      if (cCol < line.length()) cCol++;
      else if (cRow < lines.size() - 1) {
        // NOTE: Case of reaching end of line
        cCol = 0;
        cRow++;
      };
      break;
  }
  
  move(cRow, cCol);
}

void Editor::run() {
  while(true) {
    int input = getch();
    
    if (input >= KEY_DOWN && input <= KEY_RIGHT) {
      moveCursor(input);
    }
    
    refresh();
  }
}