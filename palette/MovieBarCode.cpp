#include"pch.h"

using namespace std;
using namespace cv;

void generate_code(string video, string code_path) {
	
	//输入视频文件
	VideoCapture inputVideo(video);
	//生成视频信息看是否有错误
	// 
	// 
	
	//设置参数
	const unsigned int CODE_WIDTH = 500;
	const unsigned int CODE_HEIGHT = 150;
	unsigned int VIDEO_COUNTS = inputVideo.get(CAP_PROP_FRAME_COUNT);
	const unsigned int rows_color_num = 1;


	//提取每张图片的主色,并存入条形码图片
	Mat bar_code = Mat(CODE_HEIGHT, CODE_WIDTH, CV_8UC3);
	for (int i = 0; i < CODE_WIDTH; i++) {
		int frames = i * VIDEO_COUNTS / CODE_WIDTH;
		inputVideo.set(CAP_PROP_POS_FRAMES, frames);
		Mat src;
		inputVideo >> src;

		vector<Vec3b> cp = palette(src, rows_color_num);
		int p_len = cp.size();
		for (int j = 0; j < CODE_HEIGHT; ++j) {
			int k = j / (CODE_HEIGHT / p_len);
			Vec3b color = cp[k];
			bar_code.at<Vec3b>(j, i) = color;
		}

	}
	imwrite(code_path, bar_code);

}