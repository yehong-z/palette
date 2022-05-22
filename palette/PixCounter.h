#pragma once


using array_three = unsigned int(*)[bin_length + 1][bin_length + 1];

struct PixCounter {
	array_three pix;
	array_three pix_sum;
	PixCounter();
	void update_pix(int* pix);
	void update_pix_sum();
	unsigned int sum(int* index_min, int* index_max);

};
