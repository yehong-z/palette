#pragma once


struct Vbox {
	// max��min��ʾrgb�ռ��г�������������ϽǺ����½�[B, G, R]����
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

