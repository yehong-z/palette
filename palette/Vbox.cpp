#include "pch.h"


using namespace std;

Vbox::Vbox() :
	max_index(), min_index{ 0xff, 0xff, 0xff }{}

Vbox::Vbox(const int* min, const int* max) :
	max_index(), min_index() {
	for (int i = 0; i < 3; i++) {
		max_index[i] = max[i];
		min_index[i] = min[i];
	}
}

void Vbox::update_vbox(int* pix_index) {
	for (int i = 0; i < 3; i++) {
		max_index[i] = max(max_index[i], pix_index[i]);
		min_index[i] = min(min_index[i], pix_index[i]);
	}
}

int Vbox::longest_side() {
	int b = max_index[0] - min_index[0],
		g = max_index[1] - min_index[1],
		r = max_index[2] - min_index[2];
	int max_width;
	max_width = max(b, g);
	max_width = max(r, max_width);
	if (max_width == b) return 0;
	else if (max_width == g) return 1;
	else return 2;
}

unsigned int Vbox::volume() {
	unsigned int volume = 1;
	for (int i = 0; i < 3; i++)
		volume = volume * (max_index[i] - min_index[i]);
	return volume;
}


bool operator < (Vbox a, Vbox b) {
	return priority(a) < priority(b);
}

unsigned int priority(Vbox& a) {
	//计算box的切分优先级
	//感觉应该要和像素空间大小和像素数目都相关较好
	return a.volume();
}