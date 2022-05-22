// palette.cpp : 定义静态库的函数。
//

#include "pch.h"
using namespace std;
using namespace cv;
vector<Vec3b> palette(Mat img, int max_color) {
	vector<Vec3b> res{};
	if (img.empty()) return res;

	PixCounter pix = PixCounter();
	Vbox vbox = Vbox();
	init(img, pix, vbox);

	//优先队列存储切割出的box
	priority_queue<Vbox> PQueue{};
	PQueue.push(vbox);

	//进行中位切分
	const int max = 32;
	for (int times = 0; PQueue.size() < max_color && times < max; times++) {
		if (!median_cut(PQueue, pix)) break;
	}

	//输出结果
	while (!PQueue.empty()) {
		Vbox temp = PQueue.top();
		Vec3b color = avg_color(temp, pix);
		res.push_back(color);
		PQueue.pop();
	}
	return res;
}
vector<Vec3b> palette(string file, int max_color) {
	//file为输入文件名
	//max_color为想要得到的颜色数目

	//读入文件
	Mat img = imread(file);
	return palette(img, max_color);
}


void init(Mat& img, PixCounter& pixCounter, Vbox& vbox) {
	for (auto it = img.begin<Vec3b>(), end = img.end<Vec3b>(); it != end; it++) {
		int b, g, r;
		b = (*it)[0] >> ignore_bits;
		g = (*it)[1] >> ignore_bits;
		r = (*it)[2] >> ignore_bits;
		int pix_index[3] = { b, g, r };
		vbox.update_vbox(pix_index);
		pixCounter.update_pix(pix_index);
	}
	pixCounter.update_pix_sum();
}

bool median_cut(priority_queue<Vbox>& PQ, PixCounter& pixCounter) {
	//中位切分法:
	//对VBox进行操作,每次取最长的边
	//尽量使切割后两块Vbox中包含的像素数目相同
	Vbox vbox = PQ.top();
	int axis = vbox.longest_side();

	//最长边长度为0就不切分了
	if (vbox.max_index[axis] - vbox.min_index[axis]) {
		//切分操作
		int mid = cut_index(vbox, pixCounter, axis);
		int mid_max_index[3], mid_min_index[3];
		copy(begin(vbox.max_index), end(vbox.max_index), begin(mid_max_index));
		copy(begin(vbox.min_index), end(vbox.min_index), begin(mid_min_index));
		mid_max_index[axis] = mid, mid_min_index[axis] = mid + 1;
		Vbox vbox_a = Vbox(vbox.min_index, mid_max_index);
		Vbox vbox_b = Vbox(mid_min_index, vbox.max_index);

		PQ.pop();
		PQ.push(vbox_a), PQ.push(vbox_b);
		return true;
	}
	return false;
}

int cut_index(Vbox& vbox, PixCounter& pixCounter, int axis) {


	int middle_index[3];
	copy(begin(vbox.max_index), end(vbox.max_index), begin(middle_index));
	unsigned int count = pixCounter.sum(vbox.min_index, vbox.max_index),
		half_count = pixCounter.sum(vbox.min_index, middle_index);

	while (middle_index[axis] > vbox.min_index[axis] && half_count > count / 2) {
		middle_index[axis] = middle_index[axis] - 1;
		half_count = pixCounter.sum(vbox.min_index, middle_index);
	}
	return middle_index[axis];
}


Vec3b avg_color(Vbox& vbox, PixCounter& pixCounter) {
	//计算Vbox中所有像素点的 "重心" , 可用前缀和算法优化
	unsigned int count = pixCounter.sum(vbox.min_index, vbox.max_index);
	int b_sum = 0, g_sum = 0, r_sum = 0;
	for (int b = vbox.min_index[0]; b <= vbox.max_index[0]; b++) {
		for (int g = vbox.min_index[1]; g <= vbox.max_index[1]; g++) {
			for (int r = vbox.min_index[2]; r <= vbox.max_index[2]; r++)
			{
				b_sum += pixCounter.pix[b][g][r] * (b << ignore_bits);
				g_sum += pixCounter.pix[b][g][r] * (g << ignore_bits);
				r_sum += pixCounter.pix[b][g][r] * (r << ignore_bits);
			}
		}
	}

	Vec3b res = Vec3b((unsigned char)(b_sum / count), (unsigned char)(g_sum / count), (unsigned char)(r_sum / count));
	return res;
}