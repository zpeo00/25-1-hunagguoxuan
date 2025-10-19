#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. 读取原图并调整大小为1280*720
    Mat img = imread("D:/视觉组招新考核题目/openCV/题目（1）/彩色图形.png");
    if (img.empty()) {
        cout << "无法读取图像，请检查路径！" << endl;
        return -1;
    }
    resize(img, img, Size(1280, 720));
    
    Mat bimg, eimg, dimg,cimg;
    inRange(img, Scalar(0, 0, 180), Scalar(80, 80, 255), bimg);//提取红色转为黑白
    
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//用RGB的方法提取红色，上次边缘提取一直有问题，试试用开运算
    erode(bimg, eimg, element, Point(1, 1), 1);//腐蚀
    dilate(eimg, dimg, element, Point(1, 1), 3);//膨胀

    Canny(dimg, cimg, 30., 100);

   
    vector<vector<Point>> contours;  
    vector<Vec4i> hierarchy;        
    findContours(cimg,contours,hierarchy, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
     Mat result;
    cvtColor(dimg, result, COLOR_GRAY2BGR);
    drawContours( result, contours, -1, Scalar(255, 255, 224),2);


    namedWindow("黑白", WINDOW_AUTOSIZE);
    imshow("黑白", result);
    imwrite("D:/视觉组招新考核题目/openCV/题目（1）/答案.png", result);
         
   
    waitKey(0);
    destroyAllWindows();

    return 0;
}