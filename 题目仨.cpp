#include<iostream>

#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Point  ag(-1, -1), en(-1, -1);
Mat temp;
static void shubiao(int event, int x, int y, int flags, void* userdata) {
	Mat& capture = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {//��¼��ʼλ��
		ag.x = x;
		ag.y = y;

	}

	else if (event == EVENT_LBUTTONUP) {//��¼ĩλ��
		en.x = x;
		en.y = y;
		int dx = abs(en.x - ag.x);
		int dy = abs(en.y - ag.y);//ȡ����ֵ����ֹ�����ƶ�ʱ����
		int zs_x = min(ag.x, en.x);
		int zs_y = min(ag.y, en.y);//�������ϱߵĵ�
		Rect box(zs_x, zs_y, dx, dy);//�������ο�
		//��ȡroi����
		Mat roi2 = capture(box);
		
		//���ο�
		temp.copyTo(capture);

		rectangle(capture, box, Scalar(0, 0, 255), 5, LINE_AA);//��ɫ��
		namedWindow("roi",WINDOW_AUTOSIZE );
		
		imshow("window", capture);

		

		int X = (dx)/2;
		int Y = (dy)/2;
		Point centerpoint( abs(X), abs(Y));//��ȡ���ĵ������
		
		
		
		Point endpoint(dx - 1,dy - 1);//��ȡ���µ������
        Vec3b RGB = roi2.at<Vec3b>(endpoint.y, endpoint.x); 
		uchar B = RGB[0];
		uchar G = RGB[1];
		uchar R = RGB[2];//��ȡRGBֵ
		
        string mousetext = "endpiont(" + to_string(dx - 1) + "," + to_string(dy - 1) + ")  BGR  B="
			+ to_string(B) + "R=" + to_string(R) + "G=" + to_string(G);
		putText(roi2, mousetext, Point(dx - 550, dy - 10), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 0), 1);
		
		circle(roi2, Point(dx - 2, dy - 2), 4, Scalar(255, 0,0), -1);//���µ�


		string centerpointtext = "centerpoint(" + to_string(X) + "," + to_string(Y)+")";
		putText(roi2, centerpointtext, Point(X + 10, Y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);
		circle(roi2, Point(X, Y), 4, Scalar(0, 0, 255), -1);//���ĵ�

        imshow("roi", roi2);
		cout << centerpointtext << endl;
		
	}

}
int main() {
	Mat xiaomao = imread("D:/�Ӿ������¿�����Ŀ/openCV/��Ŀ��3��/Сè.jpg");
	if (xiaomao.empty()) {
		cerr << "�����޷���ȡͼ������·���Ƿ���ȷ��" << endl;
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
