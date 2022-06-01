#ifndef COLOR_MAPPING_H
#define COLOR_MAPPING_H

#include <cmath>
#include <iostream>

namespace ns_cm {
  using uchar = unsigned char;

  struct Crgb {
  public:
    uchar r; // [0, 255]
    uchar g; // [0, 255]
    uchar b; // [0, 255]

  public:
    Crgb(uchar r, uchar g, uchar b)
        : r(r), g(g), b(b) {}
  };

  /**
   * @brief override operator '<<' for type 'Crgb'
   */
  std::ostream &operator<<(std::ostream &os, const Crgb &obj) {
    os << '{';
    os << "'r': " << (int)obj.r << ", 'g': " << (int)obj.g << ", 'b': " << (int)obj.b;
    os << '}';
    return os;
  }

  struct Chsv {
  public:
    float h; // [0.0f, 360.0f]
    float s; // [0.0f, 1.0f]
    float v; // [0.0f, 1.0f]

  public:
    Chsv(float h, float s, float v)
        : h(h), s(s), v(v) {}
  };

  /**
   * @brief override operator '<<' for type 'Chsv'
   */
  std::ostream &operator<<(std::ostream &os, const Chsv &obj) {
    os << '{';
    os << "'h': " << obj.h << ", 's': " << obj.s << ", 'v': " << obj.v;
    os << '}';
    return os;
  }

  // translate hsv color to rgb color
  static Crgb hsv2rgb(const Chsv &hsv) {
    float H = hsv.h, S = hsv.s, V = hsv.v;
    float flag = H / 60.0f;
    int temp = int(flag / 2.0f);

    float C = V * S;
    float X = C * (1.0f - std::abs(flag - 2.0f * (float)temp - 1));
    float m = V - C;

    float r, g, b;
    switch (int(flag)) {
    case 0:
      r = C, g = X, b = 0.0f;
      break;
    case 1:
      r = X, g = C, b = 0.0f;
      break;
    case 2:
      r = 0.0f, g = C, b = X;
      break;
    case 3:
      r = 0.0f, g = X, b = C;
      break;
    case 4:
      r = X, g = 0.0f, b = C;
      break;
      // case [5] and [6] are same
    case 5:
    case 6:
      r = C, g = 0.0f, b = X;
      break;
    default:
      r = g = b = 0.0f;
      break;
    }

    return Crgb((r + m) * 255.0f, (g + m) * 255.0f, (b + m) * 255.0f);
  }

  struct HSVMapping {
  protected:
    mutable float mapValue;

    union {
      // mapValue to hue
      struct {
        float startHue;
        float endHue;
        float sat;
        float val;
      } hueMapping;
      // mapValue to sat
      struct {
        float hue;
        float startSat;
        float endSat;
        float val;
      } satMapping;
      // mapValue to val
      struct {
        float hue;
        float sat;
        float startVal;
        float endVal;
      } valMapping;
    };
    HSVMapping() = default;

  public:
    const HSVMapping &setMap(float mapValue) const {
      this->mapValue = mapValue;
      return *this;
    }
    virtual float getStart() const = 0;
    virtual float getEnd() const = 0;
    virtual Chsv construct() const = 0;
  };

  // mapValue value to hue dime
  struct HueMapping : public HSVMapping {
    HueMapping(float startHue, float endHue, float sat, float val) noexcept : HSVMapping() {
      this->hueMapping.startHue = startHue;
      this->hueMapping.endHue = endHue;
      this->hueMapping.sat = sat;
      this->hueMapping.val = val;
    }

    float getStart() const override {
      return this->hueMapping.startHue;
    }
    float getEnd() const override {
      return this->hueMapping.endHue;
    }
    Chsv construct() const override {
      return {this->mapValue, this->hueMapping.sat, this->hueMapping.val};
    }
  };

  // mapValue value to sat dime
  struct SatMapping : public HSVMapping {
    SatMapping(float startSat, float endSat, float hue, float val) noexcept : HSVMapping() {
      this->satMapping.hue = hue;
      this->satMapping.startSat = startSat;
      this->satMapping.endSat = endSat;
      this->satMapping.val = val;
    }

    float getStart() const override {
      return this->satMapping.startSat;
    }
    float getEnd() const override {
      return this->satMapping.endSat;
    }
    Chsv construct() const override {
      return {this->satMapping.hue, this->mapValue, this->satMapping.val};
    }
  };

  // mapValue value to val dime
  struct ValMapping : public HSVMapping {
    ValMapping(float startVal, float endVal, float hue, float sat) noexcept : HSVMapping() {
      this->valMapping.hue = hue;
      this->valMapping.sat = sat;
      this->valMapping.startVal = startVal;
      this->valMapping.endVal = endVal;
    }

    float getStart() const override {
      return this->valMapping.startVal;
    }
    float getEnd() const override {
      return this->valMapping.endVal;
    }
    Chsv construct() const override {
      return {this->valMapping.hue, this->valMapping.sat, this->mapValue};
    }
  };

  namespace style {
    [[maybe_unused]] const static HueMapping red_yellow{0.0, 60.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping yellow_green{45.0, 130.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping green_cyan{100.0, 190.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping cyan_blue{180.0, 240.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping blue_purple{220.0, 300.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping purple_red{290.0, 360.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping panchromatic{0.0, 360.0, 1.0, 1.0};

    [[maybe_unused]] const static SatMapping red{0.0, 1.0, 360.0, 1.0};
    [[maybe_unused]] const static SatMapping pink{0.0, 1.0, 340.0, 1.0};
    [[maybe_unused]] const static SatMapping purple{0.0, 1.0, 310.0, 1.0};
    [[maybe_unused]] const static SatMapping blue{0.0, 1.0, 240.0, 1.0};
    [[maybe_unused]] const static SatMapping cyan{0.0, 1.0, 190.0, 1.0};
    [[maybe_unused]] const static SatMapping green{0.0, 1.0, 120.0, 1.0};
    [[maybe_unused]] const static SatMapping yellow{0.0, 1.0, 60.0, 1.0};
    [[maybe_unused]] const static SatMapping orange{0.0, 1.0, 20.0, 1.0};

    [[maybe_unused]] const static HueMapping red_yellow_green{0.0, 150.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping yellow_green_cyan{50.0, 180.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping green_cyan_blue{50.0, 250.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping cyan_blue_purple{180.0, 300.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping blue_purple_red{240.0, 360.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping cold{180.0, 360.0, 1.0, 1.0};
    [[maybe_unused]] const static HueMapping worm{0.0, 180.0, 1.0, 1.0};

    [[maybe_unused]] const static ValMapping gray{0.0, 1.0, 0.0, 0.0};
    [[maybe_unused]] const static ValMapping black_red{0.0, 1.0, 0.0, 1.0};
    [[maybe_unused]] const static ValMapping black_green{0.0, 1.0, 120.0, 1.0};
    [[maybe_unused]] const static ValMapping black_blue{0.0, 1.0, 240.0, 1.0};

  } // namespace ns_style

  // Continuous mapping
  static Crgb mapping(float value, float srcMin, float srcMax,
                      const HSVMapping &map = style::panchromatic, bool reversal = false) {
    // check range
    value < srcMin ? value = srcMin : float{};
    value > srcMax ? value = srcMax : float{};
    // linner mapping
    if (reversal) {
      value = srcMax - (value - srcMin);
    }
    float start = map.getStart(), end = map.getEnd();
    float mapVal = (value - srcMin) / (srcMax - srcMin) * (end - start) + start;

    // color mapping
    return hsv2rgb(map.setMap(mapVal).construct());
  }

  // Discrete mapping
  static Crgb mapping(float value, float srcMin, float srcMax, ushort classes,
                      const HSVMapping &map = style::panchromatic, bool reversal = false) {
    // check range
    value < srcMin ? value = srcMin : float{};
    value > srcMax ? value = srcMax : float{};
    // liner mapping
    if (reversal) {
      value = srcMax - (value - srcMin);
    }
    float start = map.getStart(), end = map.getEnd();
    float mapVal = (value - srcMin) / (srcMax - srcMin) * (end - start);
    if (classes == 0) {
      classes = 1;
    }
    float pieceSize = (end - start) / (float)classes;
    mapVal = int(mapVal / pieceSize) * pieceSize + 0.5f * pieceSize + start;
    if (mapVal > end) {
      mapVal = end - 0.5f * pieceSize;
    }
    // color mapping
    return hsv2rgb(map.setMap(mapVal).construct());
  }

} // namespace ns_cm

#endif
