#pragma once

#include "../file.h"

class Editor {  
  Editor();

  public:  
  Editor(const Editor&) = delete;
  Editor& operator=(const Editor&) = delete;
  ~Editor();
  
  static Editor& getInstance();

  void displayFile(File);
  void run();
};