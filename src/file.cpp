#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cerrno>
#include "file.h"

using std::vector, std::string, std::ifstream, std::ofstream, std::runtime_error;

File::File(string path): path(path) {
  loadFile(path);
}

File::File(string path, bool isNew = false): path(path) {
  if (isNew) {
    lines.push_back("");
    return;
  }

  loadFile(path);
}

void File::loadFile(string path) {
  ifstream file(path);

  if (!file.is_open()) {
    throw runtime_error("Cannot open file: " + path + "\nReason: " + std::strerror(errno));
  }

  string line;
  while(getline(file, line)) {
    lines.push_back(line);
  }

  file.close();
}

const string& File::lineAt(size_t index) {
  return lines.at(index);
}

const int File::size() {
  return lines.size();
}

void File::save() {
  ofstream file(path, std::fstream::out | std::fstream::trunc);

  if (!file.is_open()) {
    throw runtime_error("Cannot open file: " + path + "\nReason: " + std::strerror(errno));
  }

  for(string& line: lines) {
    file << line << '\n';
  }

  file.close();
}