#include "artwork/logger/logger.h"
#include "color_mapping.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char const *argv[]) {
  auto depth = cv::imread("../img/depth.png", cv::IMREAD_UNCHANGED);
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
      auto rgb = ns_cm::mapping(depthPtr[j] / 1000.0f, 0.5f, 2.0f, ns_cm::style::red);
      colorPtr[3 * j + 0] = rgb.b;
      colorPtr[3 * j + 1] = rgb.g;
      colorPtr[3 * j + 2] = rgb.r;
    }
  }

  cv::imshow("depth", depth);
  cv::imshow("color", color);
  cv::waitKey(0);
  cv::imwrite("../img/red.png", color);
  return 0;
}
