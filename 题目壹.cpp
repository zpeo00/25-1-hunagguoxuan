#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 1. ��ȡԭͼ��������СΪ1280*720
    Mat img = imread("D:/�Ӿ������¿�����Ŀ/openCV/��Ŀ��1��/��ɫͼ��.png");
    if (img.empty()) {
        cout << "�޷���ȡͼ������·����" << endl;
        return -1;
    }
    resize(img, img, Size(1280, 720));
    
    Mat bimg, eimg, dimg,cimg;
    inRange(img, Scalar(0, 0, 180), Scalar(80, 80, 255), bimg);//��ȡ��ɫתΪ�ڰ�
    
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));//��RGB�ķ�����ȡ��ɫ���ϴα�Ե��ȡһֱ�����⣬�����ÿ�����
    erode(bimg, eimg, element, Point(1, 1), 1);//��ʴ
    dilate(eimg, dimg, element, Point(1, 1), 3);//����

    Canny(dimg, cimg, 30., 100);

   
    vector<vector<Point>> contours;  
    vector<Vec4i> hierarchy;        
    findContours(cimg,contours,hierarchy, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
     Mat result;
    cvtColor(dimg, result, COLOR_GRAY2BGR);
    drawContours( result, contours, -1, Scalar(255, 255, 224),2);


    namedWindow("�ڰ�", WINDOW_AUTOSIZE);
    imshow("�ڰ�", result);
    imwrite("D:/�Ӿ������¿�����Ŀ/openCV/��Ŀ��1��/��.png", result);
         
   
    waitKey(0);
    destroyAllWindows();

    return 0;
}