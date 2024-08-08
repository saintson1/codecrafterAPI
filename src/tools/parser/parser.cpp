#include <iostream>
#include <fstream>
#include <ios>

#include "../filesystem/filesystem.hpp"

int main(int argc, char *argv[])
{

  const std::string path = "";

  codecrafter_api::filesystem new_tmp_file("tmp/cpp/test.cpp");

  new_tmp_file.create_file();

  std::cout << argc << "\n";
  for (int beg = 1; beg <= argc - 1; ++beg)
    new_tmp_file.add_content(argv[beg]);

  return 0;
}