#include"pch.h"
#include "palette.h"

using namespace std;
using namespace cv;


void generate_code(char* movie, char* code_path) {
	
	//������Ƶ�ļ�
	VideoCapture inputVideo(movie);
	//������Ƶ��Ϣ���Ƿ��д���
	// 
	// 
	
	//���ò���
	const unsigned int CODE_WIDTH = 200;
	const unsigned int CODE_HEIGHT = 150;
	unsigned int VIDEO_COUNTS = inputVideo.get(CAP_PROP_FRAME_COUNT);

	//��ȡÿ��ͼƬ����ɫ,������������ͼƬ
	Mat bar_code = Mat(CODE_HEIGHT, 3*CODE_WIDTH, CV_8UC3);


	for (int i = 0; i < CODE_WIDTH; i++) {
		int frames = i * VIDEO_COUNTS / CODE_WIDTH;
		inputVideo.set(CAP_PROP_POS_FRAMES, frames);
		Mat src;
		inputVideo >> src;

		//�ĳ������㷨
		size_t r = 0, g = 0, b = 0;
		size_t total_pix = src.total();
		for (auto i = src.begin<Vec3b>(), j = src.end<Vec3b>(); i != j; ++i) {
			r += (*i)[0];
			g += (*i)[1];
			b += (*i)[2];
		}
		
		r /= total_pix, g /= total_pix, b /= total_pix;
		Vec3b res = Vec3b((char)b, (char)g, (char)r);
		for (int j = 0; j < CODE_HEIGHT; ++j) {
			bar_code.at<Vec3b>(j, 3*i) = res;
			bar_code.at<Vec3b>(j, 3*i+1) = res;
			bar_code.at<Vec3b>(j, 3*i+2) = res;
		}
		

	}
	imwrite(code_path, bar_code);

}