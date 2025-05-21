#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

  cv::Mat M(2, 2, CV_8UC4, cv::Scalar(0, 0, 255, 255));
  cout << "M = " << endl << M << endl << endl;

  // 3차원 행렬 - 차원과 깊이를 헷갈리지말것.
  // 3차원이라는 것은 깊이를 사용한다는 거고, 깊이는 n일수도 있음.
  int sz[3] = {3, 2, 2};
  cv::Mat L(3, sz, CV_8UC(1), cv::Scalar::all(0));
  // cout << "L = " << endl << L << endl << endl; --> 3차원 이상은 불가능

  // 수동으로 3차원 행렬의 각 요소를 출력
  cout << "L (3D Matrix) manually = " << endl;
  for (int i = 0; i < sz[0]; i++) {
    cout << "Dimension " << i << ":" << endl;
    for (int j = 0; j < sz[1]; j++) {
      for (int k = 0; k < sz[2]; k++) {
        cout << (int)L.at<uchar>(i, j, k) << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  M.create(4, 4, CV_8UC(2));
  cout << "M = " << endl << " " << M << endl << endl;

  cv::Mat E = cv::Mat::eye(4, 4, CV_64F);
  cout << "E = " << endl << " " << E << endl << endl;
  cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
  cout << "O = " << endl << " " << O << endl << endl;
  cv::Mat Z = cv::Mat::zeros(3, 3, CV_8UC1);
  cout << "Z = " << endl << " " << Z << endl << endl;

  cv::Mat C = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  cout << "C = " << endl << " " << C << endl << endl;

  C = (cv::Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
  cout << "C = " << endl << " " << C << endl << endl;

  cv::Mat RowClone = C.row(1).clone();
  cout << "RowClone = " << endl << " " << RowClone << endl << endl;

  // randu를 이용해서 3x2의 행렬을 생성하고, 0~255 사이의 값을 가지도록 함.
  cv::Mat R = cv::Mat(3, 2, CV_8UC3);
  cv::randu(R, cv::Scalar::all(0), cv::Scalar::all(255));
  cout << "R = " << endl << " " << R << endl << endl;

  return 0;
}
