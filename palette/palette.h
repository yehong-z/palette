#pragma once
#include "pch.h"
#include "PixCounter.h"
#include "Vbox.h"

using namespace cv;
using namespace std;
vector<Vec3b> palette(Mat img, int max_color);
vector<Vec3b> palette(string file, int max_color);
void init(Mat& img, PixCounter& pixCounter, Vbox& vbox);
bool median_cut(priority_queue<Vbox>& PQ, PixCounter& pixCounter);
int cut_index(Vbox& vbox, PixCounter& pixCounter, int axis);
Vec3b avg_color(Vbox& vbox, PixCounter& pixCounter);
