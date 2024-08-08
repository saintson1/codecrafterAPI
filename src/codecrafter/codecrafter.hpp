#ifndef _codecrafter_hpp_
#define _codecrafter_hpp_

#include <string>

namespace codecrafter_api
{
  enum class LANG_T
  {
    JS_LANG,
    CPP_LANG,
    PYTHON_LANG,
    JAVA_LANG
  };

  class codecrafter
  {
  private:
    LANG_T lang_;
    const std::string path_ = "tmp/";
  public:
    codecrafter( std::string src_code, std::string lang, std::string input );
    ~codecrafter();
  public:
    std::string get_res();
  };
};

#endif _codecrafter_hpp_