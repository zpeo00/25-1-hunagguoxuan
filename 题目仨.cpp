#include<iostream>

#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Point  ag(-1, -1), en(-1, -1);
Mat temp;
static void shubiao(int event, int x, int y, int flags, void* userdata) {
	Mat& capture = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {//记录起始位置
		ag.x = x;
		ag.y = y;

	}

	else if (event == EVENT_LBUTTONUP) {//记录末位置
		en.x = x;
		en.y = y;
		int dx = abs(en.x - ag.x);
		int dy = abs(en.y - ag.y);//取绝对值，防止向左移动时报错
		int zs_x = min(ag.x, en.x);
		int zs_y = min(ag.y, en.y);//找最左上边的点
		Rect box(zs_x, zs_y, dx, dy);//建立矩形框
		//提取roi区域
		Mat roi2 = capture(box);
		
		//矩形框
		temp.copyTo(capture);

		rectangle(capture, box, Scalar(0, 0, 255), 5, LINE_AA);//红色框
		namedWindow("roi",WINDOW_AUTOSIZE );
		
		imshow("window", capture);

		

		int X = (dx)/2;
		int Y = (dy)/2;
		Point centerpoint( abs(X), abs(Y));//提取中心点的坐标
		
		
		
		Point endpoint(dx - 1,dy - 1);//提取右下点的坐标
        Vec3b RGB = roi2.at<Vec3b>(endpoint.y, endpoint.x); 
		uchar B = RGB[0];
		uchar G = RGB[1];
		uchar R = RGB[2];//提取RGB值
		
        string mousetext = "endpiont(" + to_string(dx - 1) + "," + to_string(dy - 1) + ")  BGR  B="
			+ to_string(B) + "R=" + to_string(R) + "G=" + to_string(G);
		putText(roi2, mousetext, Point(dx - 550, dy - 10), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 0), 1);
		
		circle(roi2, Point(dx - 2, dy - 2), 4, Scalar(255, 0,0), -1);//右下点


		string centerpointtext = "centerpoint(" + to_string(X) + "," + to_string(Y)+")";
		putText(roi2, centerpointtext, Point(X + 10, Y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);
		circle(roi2, Point(X, Y), 4, Scalar(0, 0, 255), -1);//中心点

        imshow("roi", roi2);
		cout << centerpointtext << endl;
		
	}

}
int main() {
	Mat xiaomao = imread("D:/视觉组招新考核题目/openCV/题目（3）/小猫.jpg");
	if (xiaomao.empty()) {
		cerr << "错误：无法读取图像，请检查路径是否正确！" << endl;
		return -1;
	}
	temp = xiaomao.clone();
	namedWindow("window",WINDOW_NORMAL);
	setMouseCallback("window", shubiao, &xiaomao);
	imshow("window", xiaomao);
	while (waitKey(1) != 'q') {
	}

	destroyAllWindows();
	return 0;


}
