#define _WIN32_WINNT 0x0601

#include <iostream>
#include <string>
#include <boost/process.hpp>

#include "tools/filesystem/filesystem.hpp"

int main()
{
  codecrafter_api::filesystem new_tmp_file("tmp/cpp/test.cpp");

  new_tmp_file.create_file();
  for (int beg = 1; beg <= 10    - 1; ++beg)
  {
    std::cout << new_tmp_file.add_content("new_line\n") << "\n";
  }

  // boost::process::child child_proc("E:/visual_studio/subprocess/src/subprocess/build/Debug/subprocess.exe");

  // int cnt = 0;
  // while (child_proc.running())
  //   std::cout << cnt++ << "subprocess work!\n\n";

  // while(1)
  //   ;


  // child_proc.wait();

  // int result = child_proc.exit_code();
  // std::cout << result;
  // while(1)
  //   ;

  return 0;
}