#define _WIN32_WINNT 0x0A00

#include <iostream>
#include <string>

#include <boost/process.hpp>

#include "tools/filesystem/filesystem.hpp"
#include "codecrafter/codecrafter.hpp"

int main()
{
  std::string code =
R"code(#include <iostream>
#include <exception>

int main()
{
  std::cout << "asdfasdfasdfasdf\n";
  int a = 90, b = 10;
  std::cin >> a;
  std::cin >> b;
  std::cout << a + b;

  throw std::runtime_error("misha pidpr");

  return 0;
})code";

  std::string input =
R"input(190
23
)input";

  codecrafter_api::codecrafter cc(code, "cpp", input);

  std::cout << cc.get_res();
  return 0;
}