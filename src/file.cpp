#include <vector>
#include <string>
#include <fstream>

class File {
  std::vector<std::string> lines;

  public:
  File(std::string path);
};

File::File(std::string path){
  std::ifstream file(path);

  if (file) {
    while(!file.eof()) {
      std::string line;
      getline(file, line);
      lines.push_back(line);
    }
  }

  file.close();
}