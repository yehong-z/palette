#pragma once


struct Vbox {
	// max和min表示rgb空间中长方体区域的右上角和左下角[B, G, R]坐标
	int max_index[3];
	int min_index[3];
	Vbox();
	Vbox(const int* min, const int* max);
	void update_vbox(int* pix_index);
	int longest_side();
	unsigned int volume();
};

bool operator < (Vbox a, Vbox b);
unsigned int priority(Vbox& a);

