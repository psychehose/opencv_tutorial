#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <sstream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Not enough parameters" << endl;
    return -1;
  }

  Mat img;
  if (argc == 4 && !strcmp(argv[3], "G"))
    img = imread(argv[1], IMREAD_GRAYSCALE);
  else
    img = imread(argv[1], IMREAD_COLOR);

  if (img.empty()) {
    cout << "The image" << argv[1] << " could not be loaded." << endl;
    return -1;
  }

  // Scalar intensity = img.at<uchar>(100, 100);
  Vec3b bgr_intensity = img.at<Vec3b>(100, 100);
  Vec3f bgr_intensity_float = img.at<Vec3f>(100, 100);

  // cout << "intensity of pixel (100, 100): " << intensity << endl;
  cout << "bgr intensity of pixel (100, 100): " << bgr_intensity << endl;
  cout << "bgr intensity float of pixel (100, 100): " << bgr_intensity_float
       << endl;

  return 0;
}
