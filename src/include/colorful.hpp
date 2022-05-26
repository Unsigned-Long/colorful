#ifndef COLORFUL_H
#define COLORFUL_H
#ifdef __linux__

#include <iostream>
#include <sstream>
#include <string>

namespace ns_cf {
  namespace ns_priv {
    static const std::string prefix = "\033[";
    static const std::string suffix = "m";
    // clean previous settings
    static const std::string none = "\033[0m";
  } // namespace ns_priv

  using ushort = unsigned short;

  /**
   * @brief foreground color for content
   */
  namespace ForeColor {
    /**
     * @brief create the foreground color from [r, g, b]
     *
     * @param r the  red channel value
     * @param g the greent channel value
     * @param b the blue channel value
     */
    static std::string create(ushort r, ushort g, ushort b) {
      std::stringstream stream;
      stream << ";38;2;" << r << ';' << g << ';' << b;
      return stream.str();
    }

#define FORE_COLOR_DEFINE(r, g, b) \
  std::string(";38;2;") + #r + ';' + #g + ';' + #b

    // predefined colors
    static const std::string RED = FORE_COLOR_DEFINE(255, 0, 0);
    static const std::string GREEN = FORE_COLOR_DEFINE(0, 255, 0);
    static const std::string BLUE = FORE_COLOR_DEFINE(0, 0, 255);
    static const std::string BLACK = FORE_COLOR_DEFINE(0, 0, 0);
    static const std::string WHITE = FORE_COLOR_DEFINE(255, 255, 255);
    static const std::string GRAY = FORE_COLOR_DEFINE(192, 192, 192);
    static const std::string YELLOW = FORE_COLOR_DEFINE(255, 255, 0);
    static const std::string ORANGE = FORE_COLOR_DEFINE(255, 97, 0);
    static const std::string PURPLE = FORE_COLOR_DEFINE(255, 0, 255);
    static const std::string CYAN = FORE_COLOR_DEFINE(0, 255, 255);

#undef FORE_COLOR_DEFINE
  };

  namespace BackColor {
    /**
     * @brief create the background color from [r, g, b]
     *
     * @param r the  red channel value
     * @param g the greent channel value
     * @param b the blue channel value
     */
    static std::string create(ushort r, ushort g, ushort b) {
      std::stringstream stream;
      stream << ";48;2;" << r << ';' << g << ';' << b;
      return stream.str();
    }

#define BACK_COLOR_DEFINE(r, g, b) \
  std::string(";48;2;") + #r + ';' + #g + ';' + #b
    // predefined colors
    static const std::string RED = BACK_COLOR_DEFINE(255, 0, 0);
    static const std::string GREEN = BACK_COLOR_DEFINE(0, 255, 0);
    static const std::string BLUE = BACK_COLOR_DEFINE(0, 0, 255);
    static const std::string BLACK = BACK_COLOR_DEFINE(0, 0, 0);
    static const std::string WHITE = BACK_COLOR_DEFINE(255, 255, 255);
    static const std::string GRAY = BACK_COLOR_DEFINE(192, 192, 192);
    static const std::string YELLOW = BACK_COLOR_DEFINE(255, 255, 0);
    static const std::string ORANGE = BACK_COLOR_DEFINE(255, 97, 0);
    static const std::string PURPLE = BACK_COLOR_DEFINE(255, 0, 255);
    static const std::string CYAN = BACK_COLOR_DEFINE(0, 255, 255);

#undef BACK_COLOR_DEFINE
  };

  namespace FontProp {
#define FONT_PROP_DEFINE(code) \
  std::string(";") + #code
    static const std::string BOLD = FONT_PROP_DEFINE(1);
    static const std::string DARKEN = FONT_PROP_DEFINE(2);
    static const std::string ITALIC = FONT_PROP_DEFINE(3);
    static const std::string UNDERLINE = FONT_PROP_DEFINE(4);
    static const std::string TWINKLE = FONT_PROP_DEFINE(5);
    static const std::string FLASH = FONT_PROP_DEFINE(6);
    static const std::string REVERSE = FONT_PROP_DEFINE(7);
    static const std::string INVISABLE = FONT_PROP_DEFINE(8);
    static const std::string CROSS = FONT_PROP_DEFINE(9);
  } // namespace FontProp

  /**
   * @brief Convert an object to a string and decorate it
   *
   * @tparam Type the type of this object
   * @param obj the object
   * @param flags the ornaments
   * @return std::string the result string
   */
  template <typename Type>
  std::string decorate(const Type &obj, const std::string &flags) {
    std::stringstream stream;
    stream << ns_priv::prefix << flags << ns_priv::suffix << obj << ns_priv::none;
    return stream.str();
  }

} // namespace ns_cf

#endif
#endif