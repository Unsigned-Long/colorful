#include "artwork/logger/logger.h"
#include "artwork/timer/timer.h"
#include "color_mapping.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

const ns_cm::HSVMapping &mapStyle = ns_cm::style::orange;
bool reversal = false;

void test1() {
  auto depth = cv::imread("../img/color_mapping/depth.png", cv::IMREAD_UNCHANGED);
  ns_timer::Timer timer;
  timer.re_start();
  int rows = depth.rows, cols = depth.cols;
  LOG_VAR(rows, cols);
  cv::Mat color(cv::Size(cols, rows), CV_8UC3, cv::Scalar(255, 255, 255));
  for (int i = 0; i != rows; ++i) {
    auto depthPtr = depth.ptr<ushort>(i);
    auto colorPtr = color.ptr<uchar>(i);
    for (int j = 0; j != cols; ++j) {
      if (depthPtr[j] == 0) {
        continue;
      }
      auto rgb = ns_cm::mapping(depthPtr[j] / 1000.0f, 0.5f, 2.0f, mapStyle, reversal);
      colorPtr[3 * j + 0] = rgb.b;
      colorPtr[3 * j + 1] = rgb.g;
      colorPtr[3 * j + 2] = rgb.r;
    }
  }
  LOG_INFO(timer.last_elapsed("method in test1"));
  cv::imshow("test1", color);
  cv::waitKey(0);
}

void test2() {
  auto depth = cv::imread("../img/color_mapping/depth.png", cv::IMREAD_UNCHANGED);
  ns_timer::Timer timer;
  timer.re_start();
  cv::Mat dst = ns_cm::mapping(depth, 500.0f, 2000.0f, mapStyle, reversal);
  LOG_INFO(timer.last_elapsed("method in test2"));
  cv::imshow("test2", dst);
  cv::waitKey(0);
}

int main(int argc, char const *argv[]) {
  test1();
  test2();
  return 0;
}
