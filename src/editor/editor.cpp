#include <ncurses.h>
#include <string>
#include <cctype>
#include "editor.h"
#include "cursor.h"
#include "../file.h"

using std::string;

Editor::Editor(): cursor(*this) {
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
  cursor.syncFromScreen();
}

void Editor::moveCursor(wint_t input) {
  switch (input) {
    case KEY_DOWN:
      cursor.moveDown();
      break;
    case KEY_UP:
      cursor.moveUp();
      break;
    case KEY_LEFT:
      cursor.moveLeft();
      break;
    case KEY_RIGHT:
      cursor.moveRight();
      break;
  }
}

void Editor::insertCh(wint_t input) {
  int row = cursor.getRow();
  int col = cursor.getCol();
  string& line = lines.at(row);

  // TODO: Idea of replacing whole row is ok, but maybe there is another optimal way;
  line.insert(col, 1, input);
  mvprintw(row, 0, "%lc", line);

  cursor.moveTo(row, col + 1);
}

void Editor::removeCh() {
  int row = cursor.getRow();
  int col = cursor.getCol();
  string& line = lines.at(row);

  if (row == 0 && col == 0) return;

  // NOTE: Merging two lines if removing start of line
  if (col == 0) {
    string& prevLine = lines.at(row - 1);
    col = prevLine.length();
    prevLine += line;

    lines.erase(lines.begin() + row);
    displayLines(row - 1);
    cursor.moveTo(row - 1, col);

    return;
  }

  // NOTE: Default case, just removing char and moving cursor;
  line.erase(col-1, 1);
  
  cursor.moveToRowStart();
  clrtoeol();
  mvprintw(row, 0, line.c_str());

  cursor.moveTo(row, col - 1);
}

void Editor::removeForwardCh() {
  int row = cursor.getRow();
  int col = cursor.getCol();
  string& line = lines.at(row);

  if (row == lines.size() - 1 && col == line.length()) return;

  // NOTE: Merging two lines if removing end of line
  if (col == line.length()) {
    string& nextLine = lines.at(row + 1);
    line += nextLine;

    lines.erase(lines.begin() + row + 1);
    displayLines(row);
    cursor.sync();

    return;
  }

  // NOTE: Default case, just removing char and moving cursor;
  line.erase(col+1, 1);

  cursor.moveToRowStart();
  clrtoeol();
  mvprintw(row, 0, line.c_str());

  cursor.moveTo(row, col);
}

int Editor::lineSize(int line) {
  return lines.at(line).length();
}

int Editor::linesCount() {
  return lines.size();
}

void Editor::run() {
  wint_t input;
  
  while(true) {
    get_wch(&input);

    if (input >= KEY_DOWN && input <= KEY_RIGHT) moveCursor(input);
    else if (iswprint(input))
      // TODO: Not working with cirillic letters;
      insertCh(input);
    else if (input == KEY_BACKSPACE) removeCh();
    else if (input == KEY_DL || input == 330) removeForwardCh();

    refresh();
  }
}