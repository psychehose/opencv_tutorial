/**
 * @file AddingImages.cpp
 * @brief Simple linear blender ( dst = alpha*src1 + beta*src2 )
 * @author OpenCV team
 */
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <opencv2/core.hpp>

using namespace cv;

// we're NOT "using namespace std;" here, to avoid collisions between the beta
// variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;

/**
 * @function main
 * @brief Main function
 */
int main(void) {
  double alpha = 0.5;
  double beta;
  double input;

  Mat src1, src2, dst;

  /// Ask the user enter alpha
  cout << " Simple Linear Blender " << endl;
  cout << "-----------------------" << endl;
  cout << "* Enter alpha [0.0-1.0]: ";
  cin >> input;

  // We use the alpha provided by the user if it is between 0 and 1
  if (input >= 0 && input <= 1) {
    alpha = input;
  }

  //![load]
  /// Read images ( both have to be of the same size and type )
  src1 = imread("LinuxLogo.jpg");
  src2 = imread("WindowsLogo.jpg");
  //![load]

  if (src1.empty()) {
    cout << "Error loading src1" << endl;
    return EXIT_FAILURE;
  }
  if (src2.empty()) {
    cout << "Error loading src2" << endl;
    return EXIT_FAILURE;
  }

  //![blend_images]
  beta = (1.0 - alpha);
  addWeighted(src1, alpha, src2, beta, 0.0, dst);
  //![blend_images]

  //![display]
  imshow("Linear Blend", dst);
  waitKey(0);
  // ![display]

  //![fadein/out effect]
  // for (double i = 0.0; i <= 1.0; i += 0.05) {
  //   double a = i;
  //   double b = 1.0 - i;

  //   addWeighted(src1, a, src2, b, 0.0, dst);
  //   imshow("Linear Blend", dst);
  //   waitKey(100);
  // }

  //![watermark effect]

  return 0;
}