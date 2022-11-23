#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
float const PI = 3.14;

static void on_trackbar(int, void*) {

}

int main(int argc, char** argv) {
	Mat img_frame, img_frame_gray;
	Mat img_edge, img_result;
	Mat tri;
	int start_x = 360;
	int start_y = 376;
	int end_x = 1642;
	int end_y = 1078;
	VideoCapture cap(argv[1]);
	if (!cap.isOpened()) {
		cout << "영상 없음" << endl;
		return -1;
	}
	namedWindow("color");

	//createTrackbar("threshold", "color", 0, 100, on_trackbar);
	//createTrackbar("min line length", "color", 0, 100, on_trackbar);
	//createTrackbar("max line gap", "color", 0, 100, on_trackbar);

	//setTrackbarPos("threshold", "color", 50);
	//setTrackbarPos("min line length", "color", 50);
	//setTrackbarPos("max line gap", "color", 20);



	while (1) {
		bool ret = cap.read(img_frame);
		if (!ret) {
			cout << "동영상파일 읽기 완료" << endl;
			break;
		}

		//int thres = getTrackbarPos("threshold", "color");
		//int linelen = getTrackbarPos("min line length", "color");
		//int linegap = getTrackbarPos("max line gap", "color");

		Mat roi;
		//1280x720

		roi = img_frame(Rect(Point(250, 420), Point(1000, 720)));
		
		cvtColor(roi, img_frame_gray, COLOR_BGR2GRAY);
		Canny(img_frame_gray, img_edge, 50, 150);

		cvtColor(img_edge, img_result, COLOR_GRAY2BGR);
		vector<Vec4i>linesP;
		HoughLinesP(img_edge, linesP, 1, CV_PI / 180, 50, 50, 5);
		

		for (size_t i = 0; i < linesP.size(); i++) {
			Vec4i l = linesP[i];
			line(roi, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 5,16,0);
		}
		roi.copyTo(img_frame(Rect(Point(250, 420), Point(1000, 720))));
		imshow("color", img_frame);





		int fps = (int)cap.get(CAP_PROP_FPS);
		int delay = cvRound(1000 / fps);
		int key = waitKey(delay - 13); 
		//int key = waitKey(delay);
		if (key == 27) break;

	}
	cap.release();
	return 0;
}