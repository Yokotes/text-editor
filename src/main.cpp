#include <iostream>
#include <string>
#include "../includes/file.h"

int main(int arg_count, char** args ) {
  std::cout << "Hello World, Cmake!\n";

  File file(std::string(PROJECT_ROOT)+"/test.txt");

  std::cout << file.lineAt(0) + '\n';
}