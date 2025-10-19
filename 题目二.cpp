#include <opencv2/opencv.hpp>
#include<iostream>
#include<chrono>
using namespace std::chrono;
using namespace cv;
using namespace std;

int main()
{
    VideoCapture camera(0, CAP_MSMF);
    if (!camera.isOpened()) {
        cout << "摄像头未打开" << endl;
        return -1;
    }
    namedWindow("摄像头", WINDOW_AUTOSIZE);

    camera.set(CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CAP_PROP_FRAME_HEIGHT, 480);
    double width = camera.get(CAP_PROP_FRAME_WIDTH);
    double height = camera.get(CAP_PROP_FRAME_HEIGHT);

    int baoguang = 50;
    createTrackbar("曝光", "摄像头", &baoguang, 100);
    int liangdu = 50;
    createTrackbar("亮度", "摄像头", &liangdu, 100);

    auto stime = steady_clock::now();
    int c_f = 0;
    double fps = 0.0;

    bool recording = false;
    VideoWriter videowriter;
    const string desktop_path = getenv("USERPROFILE") ? string(getenv("USERPROFILE")) + "/Desktop/" : "./";
    const string filename = desktop_path + "camera_recording.avi";
    const int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
    const double record_fps = 30.0;




    Mat frame;
    while (true) {
        camera >> frame;
        if (frame.empty()) {
            break;
        };
        camera.set(CAP_PROP_EXPOSURE, baoguang - 50);
        camera.set(CAP_PROP_BRIGHTNESS, (liangdu - 50.0) / 50.0);
        string WH = "分辨率：" + to_string(width) + "*" + to_string(height);
        putText(frame, WH, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(255, 0, 0), 2);
        c_f++;
        auto ctime = steady_clock::now();
        auto etime = duration_cast<microseconds>(ctime - stime).count();
        if (etime >= 1e6) {
            fps = c_f * 1e6 / etime;
            c_f = 0;
            stime = ctime;
        }
        string FPS = "FPS:" + to_string(fps).substr(0, 4);
        putText(frame, FPS, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(255, 0, 0), 2);



        string lz = recording ? "录制中" : "待机（按r开始/停止）";
        putText(frame, lz, Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.9,
            recording ? Scalar(0, 0, 255) : Scalar(0, 255, 0), 2);


        char key = waitKey(1);
        if (key == 'q') {
            break;
        }
        else if (key == 'r') {
            recording = !recording;
            if (recording) {

                videowriter.open(filename, codec, record_fps, Size(width, height));
                if (!videowriter.isOpened()) {
                    cerr << "错误：无法创建视频文件！" << endl;
                    recording = false;
                }
                else {
                    cout << "开始录制，视频保存路径：" << filename << endl;
                }
            }
            else {

                if (videowriter.isOpened()) {
                    videowriter.release();
                    cout << "停止录制，视频已保存" << endl;
                }
            }
        }


        if (recording && videowriter.isOpened()) {
            videowriter.write(frame);
            circle(frame, Point(frame.cols - 20, 20), 10, Scalar(0, 0, 255), -1);
        }
        imshow("摄像头", frame);

    };
    if (videowriter.isOpened()) {
        videowriter.release();
    }
    camera.release();
    destroyAllWindows();
    return 0;
}