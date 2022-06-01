#ifndef COLOR_TERMINAL_H
#define COLOR_TERMINAL_H
#ifdef __linux__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ns_ct {
  namespace ns_priv {
    static constexpr const char *prefix = "\033[";
    static constexpr const char *suffix = "m";
    // clean previous settings
    static constexpr const char *none = "\033[0m";
  } // namespace ns_priv

  /**
   * @brief foreground color for content
   */
  namespace ForeColor {

#define FORE_COLOR(r, g, b) \
  ";38;2;" #r ";" #g ";" #b

    // predefined colors
    static constexpr const char *RED = FORE_COLOR(255, 0, 0);
    static constexpr const char *GREEN = FORE_COLOR(0, 255, 0);
    static constexpr const char *BLUE = FORE_COLOR(0, 0, 255);
    static constexpr const char *BLACK = FORE_COLOR(0, 0, 0);
    static constexpr const char *WHITE = FORE_COLOR(255, 255, 255);
    static constexpr const char *GRAY = FORE_COLOR(192, 192, 192);
    static constexpr const char *YELLOW = FORE_COLOR(255, 255, 0);
    static constexpr const char *ORANGE = FORE_COLOR(255, 97, 0);
    static constexpr const char *PURPLE = FORE_COLOR(255, 0, 255);
    static constexpr const char *CYAN = FORE_COLOR(0, 255, 255);

  };

  /**
   * @brief background color for content
   */
  namespace BackColor {

#define BACK_COLOR(r, g, b) \
  ";48;2;" #r ";" #g ";" #b

    // predefined colors
    static constexpr const char *RED = BACK_COLOR(255, 0, 0);
    static constexpr const char *GREEN = BACK_COLOR(0, 255, 0);
    static constexpr const char *BLUE = BACK_COLOR(0, 0, 255);
    static constexpr const char *BLACK = BACK_COLOR(0, 0, 0);
    static constexpr const char *WHITE = BACK_COLOR(255, 255, 255);
    static constexpr const char *GRAY = BACK_COLOR(192, 192, 192);
    static constexpr const char *YELLOW = BACK_COLOR(255, 255, 0);
    static constexpr const char *ORANGE = BACK_COLOR(255, 97, 0);
    static constexpr const char *PURPLE = BACK_COLOR(255, 0, 255);
    static constexpr const char *CYAN = BACK_COLOR(0, 255, 255);

  };

  namespace FontProp {
#define FONT_PROP(code) \
  ";" #code

    static constexpr const char *BOLD = FONT_PROP(1);
    static constexpr const char *DARKEN = FONT_PROP(2);
    static constexpr const char *ITALIC = FONT_PROP(3);
    static constexpr const char *UNDERLINE = FONT_PROP(4);
    static constexpr const char *TWINKLE = FONT_PROP(5);
    static constexpr const char *FLASH = FONT_PROP(6);
    static constexpr const char *REVERSE = FONT_PROP(7);
    static constexpr const char *INVISABLE = FONT_PROP(8);
    static constexpr const char *CROSS = FONT_PROP(9);

#undef FONT_PROP
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
  std::string decorate(const Type &obj, const std::vector<const char *> &flags) {
    std::stringstream stream;
    stream << ns_priv::prefix;
    for (const auto &elem : flags) {
      stream << elem;
    }
    stream << ns_priv::suffix << obj << ns_priv::none;
    return stream.str();
  }

} // namespace ns_cf

#endif
#endif