#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main() {
    // 读取图像
    Mat img = imread("D:/视觉组招新考核题目/openCV/应用题（1）/苹果.png");
    if (img.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    Mat cimg,gimg,eimg,iimg,iimg1,iimg2;
    cvtColor(img, cimg,COLOR_BGR2HSV);
    inRange(cimg, Scalar(0, 50, 50), Scalar(10, 255, 255), iimg1);
    inRange(cimg, Scalar(170, 50, 50), Scalar(180, 255, 255), iimg2);
    bitwise_or(iimg1, iimg2, iimg);
    eimg = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(iimg, iimg, MORPH_CLOSE, eimg, Point(1, 1), 2);
    morphologyEx(iimg, iimg, MORPH_OPEN, eimg, Point(1, 1), 1);
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    findContours(iimg , contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {
        int mi = 0;
        double ma = contourArea(contours[0]);
        for (size_t i = 1; i < contours.size(); ++i) {
            double area = contourArea(contours[i]);
            if (area > ma) {
                ma = area;
                mi = i;

            }
        }
        drawContours(img, contours, mi, Scalar(0, 255, 0), 2);
        Rect kk = boundingRect(contours[mi]);
        rectangle(img, kk, Scalar(0, 0, 255), 2);


    }

    imshow("Result", iimg);
    imshow("RRsult", img);
    waitKey(0);

    return 0;
}