#define _WIN32_WINNT 0x0601

#include <iostream>
#include <boost/process.hpp>

#include "tools/filesystem/filesystem.hpp"

int main()
{

  codecrafter_api::filesystem new_fs5("test/test.file");
  new_fs5.create_file();
  new_fs5.add_content("hw");
  new_fs5.add_content("\nhw");
  new_fs5.add_content("\nhw");

  codecrafter_api::filesystem new_fs1("test/test2.file");
  new_fs1.create_file();
  new_fs1.add_content("hw\n");
  new_fs1.reset_content("reset\nwwwwwww\nwwwwww\nwwwww\n");
  // new_fs1.add_content("pupu\n");

  // codecrafter_api::filesystem new_fs2("test/test3.file");
  // new_fs2.create_file();
  // new_fs2.add_content();
  // new_fs2.reset_content();




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