#define _WIN32_WINNT 0x0601

#include <iostream>
#include <boost/process.hpp>

#include "tools/filesystem/filesystem.hpp"

int main()
{
  // codecrafter_api::filesystem new_fs("");
  // new_fs.create_dir();

  // codecrafter_api::filesystem new_fs2("new_dir2");
  // new_fs2.create_dir();

  // codecrafter_api::filesystem new_fs3("new_dir");
  // new_fs3.create_dir();

  // codecrafter_api::filesystem new_fs4("./new_dir/new_subdir");
  // new_fs4.create_dir();

  codecrafter_api::filesystem new_fs5(".////new");
  new_fs5.create_dir();


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

  // return 0;
}