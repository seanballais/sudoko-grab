#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
    const int IMG_GRAYSCALE = 0;
    cv::Mat sudoku = cv::imread("bin/sudoku.jpg", IMG_GRAYSCALE);
    cv::Mat outerBox = cv::Mat(sudoku.size(), CV_8UC1);

    cv::GaussianBlur(sudoku, sudoku, cv::Size(11, 11), 0);
    cv::adaptiveThreshold(sudoku, outerBox, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 5, 2);
    cv::bitwise_not(outerBox, outerBox);

    cv::Mat kernel = (cv::Mat_<uchar>(3, 3) << 0, 1, 0, 1, 1, 1, 0, 1, 0);
    cv::dilate(outerBox, outerBox, kernel);

    // Detect the largest blob which is the puzzle
    int count = 0;
    int max = -1;

    cv::Point maxPt;

    for (int y = 0; y < outerBox.size().height; y++) {
        uchar *row = outerBox.ptr(y);
        for (int x = 0; x < outerBox.size().width; x++) {
            if (row[x] >= 128) { // Make sure we only fill the pixel that is white
                int area = cv::floodFill(outerBox, cv::Point(x, y), CV_RGB(0, 0, 64));
                if (area > max) {
                    maxPt = cv::Point(x, y);
                    max = area;
                }
            }
        }
    }

    // We got the biggest blob. Let's make it white.
    cv::floodFill(outerBox, maxPt, CV_RGB(255, 255, 255));

    // Turn the other blobs black
    for (int y = 0; y < outerBox.size().height; y++) {
        uchar *row = outerBox.ptr(y);
        for (int x = 0; x < outerBox.size().width; x++) {
            if (row[x] == 64 && x != maxPt.x && y != maxPt.y) {
                int area = cv::floodFill(outerBox, cv::Point(x, y), CV_RGB(0, 0, 0));
            }
        }
    }

    // Erode the "dilated" image
    cv::erode(outerBox, outerBox, kernel);
    cv::imshow("Sudoku Grab", outerBox);
    cv::waitKey(0);

    return 0;
}
