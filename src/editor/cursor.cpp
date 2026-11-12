#include <ncurses.h>
#include "cursor.h"
#include "editor.h"

Cursor::Cursor(Editor& editor): editor(editor) {}

void Cursor::sync() {
  move(row, col);
}

void Cursor::syncFromScreen() {
  getsyx(row, col);
}

void Cursor::moveUp() {
  if (row == 0) return;
  
  int lineSize = editor.lineSize(--row);
  if (col > lineSize) col = lineSize;
  
  sync();
}

void Cursor::moveDown() {
  int size = editor.linesCount();
  if (row == size - 1) return;

  int lineSize = editor.lineSize(++row);
  if (col > lineSize) col = lineSize;

  sync();
}

void Cursor::moveLeft() {
  if (row == 0 && col == 0) return;

  if (col > 0) {
    col--;
  } else {
    int lineSize = editor.lineSize(--row);
    col = lineSize;
  }

  sync();
}

void Cursor::moveRight() {
  int size = editor.linesCount();
  int currentLineSize = editor.lineSize(row);
  if (row == size - 1 && col == currentLineSize) return;

  if (col < currentLineSize) {
    col++;
  } else {
    row++;
    col = 0;
  }

  sync();
}

void Cursor::moveToRowStart() {
  col = 0;
  sync();
}

void Cursor::moveTo(int newRow, int newCol) {
  row = newRow;
  col = newCol;

  sync();
}

int Cursor::getRow() {
  return row;
}

int Cursor::getCol() {
  return col;
}