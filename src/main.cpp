#include <iostream>
#include <string>
#include <locale.h>
#include "file.h"
#include "editor/editor.h"

using std::string;

int main(int arg_count, char** args ) {
  setlocale(LC_ALL, "");

  bool isNew = false;
  string path = "./NEW_FILE.txt";

  if (arg_count > 1) {
    path = args[1];
  } else {
    isNew = true;
  }

  File file(path, isNew);
  Editor& editor = Editor::getInstance();

  editor.displayFile(file);

  editor.run();

  file.save();
}