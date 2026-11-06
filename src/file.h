#pragma once

#include <fstream>
#include <vector>
#include <string>

using std::vector, std::string, std::ifstream;

class File {
  vector<string> lines;
  string path;

  void loadFile(string path);

  public:
  File(string path);
  File(string path, bool isNew);
  const string& lineAt(size_t index);
  const int size();
  void save();
};