
#pragma once

#include <QDebug>

void myAugmentation0(
	uchar in_out_y[],
	int x_size,
    int y_size,
    int hue_increase //[-10, 10]
);

void myAugmentation1(
	uchar in_out_rgb[],
	int x_size,
	int y_size,
    int h, // [1, 10]
    int w,// [1, 10]
    int percentage //[0, 70]
);


void myAugmentation2(
    uchar in_out_rgb[],
    int x_size,
    int y_size,
    double angle // [0, 360]

);

void myAugmentation3(
    uchar in_out_rgb[],
    int x_size,
    int y_size,
    int N, // [0, 360]
    int B,
    float lambda
);
