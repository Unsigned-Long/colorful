#include "color_terminal.hpp"

using namespace ns_ct;

int main(int argc, char const *argv[]) {
  std::cout << decorate("Hello, world!", {FontProp::CROSS, FORE_COLOR(255, 0, 0)}) << std::endl;
  std::cout << decorate("Hello, world!", {FontProp::UNDERLINE}) << std::endl;
  std::cout << decorate("Hello, world!", {FontProp::FLASH}) << std::endl;
  std::cout << decorate("Hello, world!", {FontProp::ITALIC}) << std::endl;
  std::cout << decorate("Hello, world!", {FontProp::BOLD}) << std::endl;
  std::cout << decorate("Hello, world!", {BackColor::ORANGE}) << std::endl;
  std::cout << decorate("Hello, world!", {BackColor::CYAN, FontProp::BOLD, FontProp::ITALIC, FontProp::CROSS}) << std::endl;

  return 0;
}
