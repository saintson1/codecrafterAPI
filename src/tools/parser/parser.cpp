#include <iostream>
#include <fstream>
#include <ios>

int main(int argc, char *argv[])
{
  const std::string path = "";
  std::fstream file("test.txt", std::ios_base::in);

  file.open();

  for (int beg = 1; beg <= argc; ++beg)
    std::cout << argv[beg] << " parser_ans\n";

 file.close();

  return 0;
}