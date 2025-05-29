#include <cstddef>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <sys/wait.h>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Not enough parameters" << endl;
    return -1;
  }

  Mat img;
  if (argc == 3 && !strcmp(argv[2], "G"))
    img = imread(argv[1], IMREAD_GRAYSCALE);
  else
    img = imread(argv[1], IMREAD_COLOR);

  if (img.empty()) {
    cout << "The image" << argv[1] << " could not be loaded." << endl;
    return -1;
  }

  Scalar intensity = img.at<uchar>(100, 100);
  Vec3b bgr_intensity = img.at<Vec3b>(100, 100);
  Vec3f bgr_intensity_float =
      img.at<Vec3f>(100, 100); // 쓰레기 값 (타입이 안맞으면 쓰레기값 줌)

  cout << "intensity of pixel (100, 100): " << intensity << endl;
  cout << "bgr intensity of pixel (100, 100): " << bgr_intensity << endl;
  cout << "bgr intensity float of pixel (100, 100): " << bgr_intensity_float
       << endl;

  // Point vector ->  Mat
  vector<Point2f> points2D;

  points2D.push_back(Point2f(0.0f, 0.0f));
  points2D.push_back(Point2f(1.0f, 0.0f));
  points2D.push_back(Point2f(2.0f, 1.0f));

  Mat points2Dmat = Mat(points2D);

  cout << "points2Dmat = " << points2Dmat << endl;

  vector<Point3f> points3D;

  points3D.push_back(Point3f(0.0f, 0.0f, 0.0f));
  points3D.push_back(Point3f(1.0f, 0.0f, 0.0f));
  points3D.push_back(Point3f(2.0f, 1.0f, 0.0f));

  Mat points3Dmat = Mat(points3D);

  cout << "points3Dmat = " << points3Dmat << endl;

  // Mat 접근
  // Mat.at()은 생성을 어떻게 했는지에 따라 다르게 생각해야함. 이름은 같지만
  // 내부적으로 다르게 접근함 이미지를 읽으면 Mat<uchar> or Mat<Vec3b>이고
  // vec<Point> 로 생성하면 Mat<Point2f> or Mat<Point3f>이다.
  // 따라서 Mat.at()을 사용할 때는 생성한 방법에 따라 다르게 접근해야함
  // Mat.at<uchar, Vec3b>(row, col)임
  // Mat.at<Point>(row, offset)임

  Point2f p2f_0 = points2Dmat.at<Point2f>(0, 0);
  cout << "p2f_0 = " << p2f_0 << endl;

  Point2f p2f_0_1 = points2Dmat.at<Point2f>(0, 1);
  cout << "p2f_0_1 = " << p2f_0_1 << endl;

  Point2f p2f_1_1 = points2Dmat.at<Point2f>(1, 1);
  cout << "p2f_1_1 = " << p2f_1_1 << endl;

  Point2f p2f_0_2 = points2Dmat.at<Point2f>(0, 2);
  cout << "p2f_0_2 = " << p2f_0_2 << endl;

  vector<Point3f> points;
  points.push_back(Point3f(1.0f, 2.0f, 3.0f));
  points.push_back(Point3f(4.0f, 5.0f, 6.0f));

  Mat pointsmat = Mat(points).reshape(1);

  // points = vector<Point3f>(); 이 경우에 p3f_0_0의 값이 어떻게 나올까?
  // points.clear(); 이 경우에 p3f_0_0의 값이 어떻게 나올까?

  cout << "pointsmat = " << pointsmat << endl;
  float p3f_0_0 = pointsmat.at<float>(0, 0);
  cout << "p3f_0_0 = " << p3f_0_0 << endl;

  // img = Scalar(0); // img의 모든 픽셀을 0으로 초기화

  // Rect r(10, 10, 100, 100);
  // Mat roi = img(r);
  // imshow("roi", roi);

  Mat grayImage;
  cvtColor(img, grayImage, COLOR_BGR2GRAY);

  Mat sobelx;
  Sobel(grayImage, sobelx, CV_32F, 1, 0);
  double minVal, maxVal;
  minMaxLoc(sobelx, &minVal, &maxVal); // find minimum and maximum intensities
  Mat draw;
  sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal),
                   -minVal * 255.0 / (maxVal - minVal));

  namedWindow("image", WINDOW_AUTOSIZE);
  imshow("image", draw);

  waitKey();

  return 0;
}
