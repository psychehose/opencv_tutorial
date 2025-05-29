#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <sstream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Not enough parameters" << endl;
    return -1;
  }

  Mat I;
  if (argc == 4 && !strcmp(argv[3], "G"))
    I = imread(argv[1], IMREAD_GRAYSCALE);
  else
    I = imread(argv[1], IMREAD_COLOR);

  if (I.empty()) {
    cout << "The image" << argv[1] << " could not be loaded." << endl;
    return -1;
  }

  return 0;
}
