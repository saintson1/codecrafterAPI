#include <iostream>
#include <filesystem>
#include <fstream>
#include <ios>

#include "../filesystem/filesystem.hpp"

int main(int argc, char *argv[])
{
  std::string filename = argv[1];
  std::filesystem::path path(argv[1]);
  std::cout << path;

  codecrafter_api::filesystem new_tmp_file(path.generic_string());
  // new_tmp_file.create_file();



  // codecrafter_api::filesystem new_tmp_file("tmp/cpp/test.cpp");

  // new_tmp_file.create_file();

  // std::cout << argc << "\n";
  // for (int beg = 1; beg <= argc; ++beg)
  //   new_tmp_file.add_content(argv[beg]);

  return 0;
}