#pragma once

#include <vector>
#include <string>
#include "cursor.h"
#include "../file.h"

using std::string, std::vector;

class Editor {
  int cRow = 0, cCol = 0;
  vector<string> lines;
  Cursor cursor;

  Editor();
  void moveCursor(int);
  void insertCh(int);
  void removeCh();
  void displayLines(int);

  public:  
  Editor(const Editor&) = delete;
  Editor& operator=(const Editor&) = delete;
  ~Editor();
  
  static Editor& getInstance();

  void displayFile(File&);
  void run();
  int lineSize(int);
  int linesCount();
};