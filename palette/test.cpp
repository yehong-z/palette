#include "pch.h"
#include "palette.h"

using namespace std;

void cal_pale(std::string s, int m) {
	cout << "color:" << endl;
    vector<cv::Vec3b> res(palette(s, m));
	for (auto i : res)
	{
		cout << i << endl;;
	}
	
}