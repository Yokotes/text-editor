#include <fstream>
#include <vector>
#include <string>

using std::vector, std::string, std::ifstream;

class File {
  vector<string> lines;
  string path;

  public:
  File(string path);
  string& lineAt(size_t index);
};