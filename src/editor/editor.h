#pragma once

#include <vector>
#include <string>
#include "../file.h"

using std::string, std::vector;

class Editor {  
  vector<string> lines;

  Editor();
  void moveCursor(int);

  public:  
  Editor(const Editor&) = delete;
  Editor& operator=(const Editor&) = delete;
  ~Editor();
  
  static Editor& getInstance();

  void displayFile(File&);
  void run();
};