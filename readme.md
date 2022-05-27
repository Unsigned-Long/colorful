# Colorful Console

**Author: shlChen**

**E-Mail: 3079625093@qq.com**

[TOC]

## 1. Overview

Modify the output characters of the terminal control window under Linux system, including color, font format and so on.

## 2. Usage

code

<img src="./img/code.png">

output

<img src="./img/console.png" width=83%>

## 3. Apis

```cpp
/**
 * @brief Convert an object to a string and decorate it
 *
 * @tparam Type the type of this object
 * @param obj the object
 * @param flags the ornaments
 * @return std::string the result string
 */
template <typename Type>
std::string decorate(const Type &obj, const std::string &flags);
```

```cpp
#define BACK_COLOR(r, g, b)
```

```cpp
#define FORE_COLOR(r, g, b)
```

```cpp
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
```

```cpp
static constexpr const char *BOLD = FONT_PROP(1);
static constexpr const char *DARKEN = FONT_PROP(2);
static constexpr const char *ITALIC = FONT_PROP(3);
static constexpr const char *UNDERLINE = FONT_PROP(4);
static constexpr const char *TWINKLE = FONT_PROP(5);
static constexpr const char *FLASH = FONT_PROP(6);
static constexpr const char *REVERSE = FONT_PROP(7);
static constexpr const char *INVISABLE = FONT_PROP(8);
static constexpr const char *CROSS = FONT_PROP(9);
```

