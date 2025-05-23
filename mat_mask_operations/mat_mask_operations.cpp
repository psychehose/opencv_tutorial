#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

static void help(char *progName) {
  cout << endl
       << "This program shows how to filter images with mask: the write it "
          "yourself and the"
       << "filter2d way. " << endl
       << "Usage:" << endl
       << progName << " [image_path -- default lena.jpg] [G -- grayscale] "
       << endl
       << endl;
}

void Sharpen(const Mat &myImage, Mat &Result);
void OnlyBlueSharpen(const Mat &src, Mat &dst);

int main(int argc, char *argv[]) {
  help(argv[0]);
  const char *filename = argc >= 2 ? argv[1] : "lena.jpg";

  Mat src, dst0, dst1, dst2;

  if (argc >= 3 && !strcmp("G", argv[2]))
    src = imread(samples::findFile(filename), IMREAD_GRAYSCALE);
  else
    src = imread(samples::findFile(filename), IMREAD_COLOR);

  if (src.empty()) {
    cerr << "Can't open image [" << filename << "]" << endl;
    return EXIT_FAILURE;
  }

  namedWindow("Input", WINDOW_AUTOSIZE);
  namedWindow("Output", WINDOW_AUTOSIZE);

  imshow("Input", src);
  double t = (double)getTickCount();

  Sharpen(src, dst0);

  t = ((double)getTickCount() - t) / getTickFrequency();
  cout << "Hand written function time passed in seconds: " << t << endl;

  imshow("Output", dst0);
  waitKey(1000);

  //![kern]
  Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  //![kern]

  t = (double)getTickCount();

  //![filter2D]
  filter2D(src, dst1, src.depth(), kernel);
  //![filter2D]
  t = ((double)getTickCount() - t) / getTickFrequency();
  cout << "Built-in filter2D time passed in seconds:     " << t << endl;

  imshow("Output", dst1);

  waitKey(1000);

  t = (double)getTickCount();
  //![only b filter2D]
  OnlyBlueSharpen(src, dst2);
  //![only b filter2D]

  t = ((double)getTickCount() - t) / getTickFrequency();
  cout << "Built-in only bfilter2D time passed in seconds:     " << t << endl;

  imshow("Output", dst2);

  waitKey();
  return EXIT_SUCCESS;
}
//! [basic_method]
void Sharpen(const Mat &myImage, Mat &Result) {
  //! [8_bit]
  CV_Assert(myImage.depth() == CV_8U); // accept only uchar images
                                       //! [8_bit]

  //! [create_channels]
  const int nChannels = myImage.channels();
  Result.create(myImage.size(), myImage.type());
  //! [create_channels]

  //! [basic_method_loop]
  for (int j = 1; j < myImage.rows - 1; ++j) {
    const uchar *previous = myImage.ptr<uchar>(j - 1);
    const uchar *current = myImage.ptr<uchar>(j);
    const uchar *next = myImage.ptr<uchar>(j + 1);

    uchar *output = Result.ptr<uchar>(j);

    for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) {
      output[i] =
          saturate_cast<uchar>(5 * current[i] - current[i - nChannels] -
                               current[i + nChannels] - previous[i] - next[i]);
    }
  }
  //! [basic_method_loop]

  //! [borders]
  Result.row(0).setTo(Scalar(0));
  Result.row(Result.rows - 1).setTo(Scalar(0));
  Result.col(0).setTo(Scalar(0));
  Result.col(Result.cols - 1).setTo(Scalar(0));
  //! [borders]
}
//! [basic_method]

void OnlyBlueSharpen(const Mat &src, Mat &dst) {
  vector<Mat> bgrChannels;
  split(src, bgrChannels);

  Mat kern = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

  Mat blueChannel;
  filter2D(bgrChannels[0], blueChannel, bgrChannels[0].depth(), kern);

  bgrChannels[0] = blueChannel;

  merge(bgrChannels, dst);
}
