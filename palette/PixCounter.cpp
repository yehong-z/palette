#include "pch.h"
#include "PixCounter.h"

PixCounter::PixCounter() {
	pix = new unsigned int[bin_length + 1][bin_length + 1][bin_length + 1]{};
	pix_sum = new unsigned int[bin_length + 1][bin_length + 1][bin_length + 1]{};
}

void PixCounter::update_pix(int* index) {
	pix[index[0] + 1][index[1] + 1][index[2] + 1] += 1;
}
void PixCounter::update_pix_sum() {
	//求前缀和数组
	for (int b = 1; b <= bin_length; ++b) {
		for (int g = 1; g <= bin_length; ++g) {
			for (int r = 1; r <= bin_length; ++r) {
				pix_sum[b][g][r] = pix[b][g][r] + pix_sum[b - 1][g - 1][r - 1]
					+ pix_sum[b - 1][g][r] + pix_sum[b][g - 1][r] + pix_sum[b][g][r - 1]
					- pix_sum[b][g - 1][r - 1] - pix_sum[b - 1][g][r - 1] - pix_sum[b - 1][g - 1][r];
			}
		}
	}
}
unsigned int PixCounter::sum(int* index_min, int* index_max) {
	int ub = index_max[0] + 1, ug = index_max[1] + 1, ur = index_max[2] + 1;
	int fb = index_min[0], fg = index_min[1], fr = index_min[2];

	unsigned int res = pix_sum[ub][ug][ur] - pix_sum[fb][fg][fr]
		- pix_sum[fb][ug][ur] - pix_sum[ub][fg][ur] - pix_sum[ub][ug][fr]
		+ pix_sum[ub][fg][fr] + pix_sum[fb][ug][fr] + pix_sum[fb][fg][ur];
	return res;
}

