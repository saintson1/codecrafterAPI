#define _WIN32_WINNT 0x0A00

#include "codecrafter.hpp"

#include <string>
#include <filesystem>
#include <exception>

#include <boost/process.hpp>

#include "../tools/filesystem/filesystem.hpp"


#include <iostream>
#include <vector>


namespace codecrafter_api
{
  codecrafter::codecrafter( std::string src_code, std::string lang, std::string input )
  {
    if (lang == "cpp")
      lang_ = LANG_T::CPP_LANG;
    else if (lang == "js")
      lang_ = LANG_T::JS_LANG;
    else if (lang == "py")
      lang_ = LANG_T::PYTHON_LANG;
    else if (lang == "java")
      lang_ = LANG_T::JAVA_LANG;

    codecrafter_api::filesystem fs_input(path_ + "input");
    fs_input.reset_content(input);

    std::string extention;

    switch(lang_)
    {
    case LANG_T::CPP_LANG:
      extention = "cpp";
      break;
    case LANG_T::JS_LANG:
      extention = "js";
      break;
    case LANG_T::PYTHON_LANG:
      extention = "py";
      break;
    case LANG_T::JAVA_LANG:
      extention = "java";
      break;
    }

    codecrafter_api::filesystem fs_src(path_ + "src." + extention);
    fs_src.create_file();
    fs_src.reset_content(src_code);


    fs_input.create_file();
    fs_input.reset_content(input);

    try
    {
      boost::process::child compl_prog;
      switch(lang_)
      {
      case LANG_T::CPP_LANG:
        std::vector<std::string> args = {"-mconsole", "-o", path_ + "bin", fs_src.get_raw_full_name()};
        compl_prog = boost::process::child(boost::process::search_path("g++"), boost::process::args(args), boost::process::std_err > path_ + "res");
      // case LANG_T::JS_LANG:
      //   codecrafter_api::filesystem fs_src(path_ + "src.js");
      // case LANG_T::PYTHON_LANG:
      //   codecrafter_api::filesystem fs_src(path_ + "src.py");
      // case LANG_T::JAVA_LANG:
      //   codecrafter_api::filesystem fs_src(path_ + "src.java");
      }

      compl_prog.wait();
    }
    catch(...)
    {
      std::cout << "codecrafter_api log:::: " << "comp exception\n";
    }

    try
    {
      boost::process::child exe_proc(path_ + "bin.exe", boost::process::std_in < path_ + "input", boost::process::std_out > path_ + "res", boost::process::std_err > path_ + "res");

      exe_proc.wait();
    }
    catch (const boost::process::process_error& e)
    {
      std::cout << "Process error: " << e.what() << std::endl;
    }
    catch (const std::system_error& e)
    {
      std::cout << "System error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
      std::cout << "Exception: " << e.what() << std::endl;
    }
    catch(...)
    {
      std::cout << "codecrafter_api log:::: " << "runtime exception\n";
    }
  };

  codecrafter::~codecrafter()
  {
    codecrafter_api::filesystem fs_remove(path_);
    fs_remove.remove_all();
  };

    std::string codecrafter::get_res()
    {
      codecrafter_api::filesystem fs_res(path_ + "res");

      return fs_res.get_content();
    };

};