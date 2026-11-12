#pragma once

class Editor;

class Cursor {
  int row = 0, col = 0;
  
  Editor& editor;

  public:
  explicit Cursor(Editor& editor);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void moveToRowStart();
  void moveTo(int, int);
  void sync();
  void syncFromScreen();
  int getRow();
  int getCol();
};