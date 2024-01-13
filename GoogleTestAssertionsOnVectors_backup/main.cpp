#include "LibraryCode.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  std::cout << "Do something with your library code\n";
  std::vector<int> vec = generateNumbers(10, 8);
  for (auto &i : vec) {
    std::cout << i << " ";
  }
  return 0;
}
