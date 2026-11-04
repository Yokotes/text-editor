#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cerrno>
#include "../includes/file.h"

using std::vector, std::string, std::ifstream, std::runtime_error;

File::File(string path): path(path) {
  ifstream file(path);

  if (!file.is_open()) {
    throw runtime_error("Не удалось открыть файл: " + path + "\nПричина: " + std::strerror(errno));
  }

  string line;
  while(getline(file, line)) {
    lines.push_back(line);
  }

  file.close();
}

string& File::lineAt(size_t index) {
  return lines.at(index);
}