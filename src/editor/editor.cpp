#include <ncurses.h>
#include <string>
#include <cctype>
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

void Editor::displayLines(int from = 0) {
  move(from, 0);
  clrtobot();

  if (from >= lines.size()) return;

  for (int i = from; i < lines.size(); i++) {
    const string& line = lines.at(i);
    mvprintw(i, 0, line.c_str());
  }

  refresh();
}

void Editor::displayFile(File& file) {
  for (int i = 0; i < file.size(); i++) {
    lines.push_back(file.lineAt(i));
  }
  displayLines();
  getsyx(cRow, cCol);
}

void Editor::moveCursor(int input) {
  int row = cRow, col = cCol;

  // TODO: Make more readable;
  switch (input) {
    case KEY_DOWN:
      if (row < lines.size() - 1) {
        row++;

        string& line = lines.at(row);
        if (col > line.length()) col = line.length();
      }
      break;
    case KEY_UP:
      if (row > 0) {
        row--;

        string& line = lines.at(row);
        if (col > line.length()) col = line.length();
      }
      break;
    case KEY_LEFT:
      if (col > 0) col--;
      else {
        // NOTE: Case of reaching zero position of line;
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
        // NOTE: Case of reaching end of line;
        col = 0;
        row++;
      };
      break;
  }
  
  move(row, col);
  cRow = row;
  cCol = col;
}

void Editor::insertCh(int input) {
  // TODO: Idea of replacing whole row is ok, but maybe there is another optimal way;
  string& line = lines.at(cRow);
  line.insert(cCol, sizeof(char), char(input));

  mvprintw(cRow, 0, line.c_str());
  move(cRow, ++cCol);
}


void Editor::removeCh() {
  // TODO: Add case of merging two lines;
  string& line = lines.at(cRow);

  if (line.length() > 0) {
    line.erase(cCol-1, 1);
    
    move(cRow, 0);
    clrtoeol();
    mvprintw(cRow, 0, line.c_str());
    
    cCol--;
  } else if (lines.size() > 1) {
    // NOTE: Case of removing empty line;
    lines.erase(lines.begin() + cRow);
    
    displayLines(cRow);

    if (cRow > 0) cRow--;

    if (cRow >= 0) cCol = lines.at(cRow).length();
    else cCol = 0;
  }
  move(cRow, cCol);
}

void Editor::run() {
  while(true) {
    int input = getch();
    
    if (input >= KEY_DOWN && input <= KEY_RIGHT) {
      moveCursor(input);
    }
    else if (isascii(input) && isprint(input)){
      // TODO: Not working with cirillic letters;
      insertCh(input);
    }
    else if (input == KEY_BACKSPACE) {
      removeCh();
    }

    refresh();
  }
}