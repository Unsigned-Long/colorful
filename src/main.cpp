
#include "colorful.hpp"

using namespace ns_cf;

#define TESTING(context, flags) \
  std::cout << "[" << decorate(context, flags) << "]-[" << #flags << "]" << std::endl;

int main(int argc, char const *argv[]) {
  std::string str("Hello, world!");
  TESTING(str, FontProp::CROSS + ForeColor::RED);
  TESTING(str, FontProp::UNDERLINE);
  TESTING(str, FontProp::FLASH);
  TESTING(str, FontProp::ITALIC);
  TESTING(str, FontProp::BOLD);
  TESTING(str, BackColor::ORANGE);
  TESTING(str, BackColor::CYAN + FontProp::BOLD + FontProp::ITALIC + FontProp::CROSS);
  return 0;
}
