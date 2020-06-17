/**
 * @file BackgroundRemover.cpp
 * @
 * @brief 
 * @version 0.1
 * @date 2020-05-02
 *  * /// Code is inspired from the following github repo. Modifications are made based on our requirement.
 * @ref https://github.com/PierfrancescoSoffritti/Handy
 * @copyright Copyright (c) 2020
 * 
 */
#include "BackgroundRemover.h"
#include"opencv2/opencv.hpp"



BackgroundRemover::BackgroundRemover(void) {
	background;
	calibrated = false;
}

void BackgroundRemover::calibrate(Mat input) {
	cvtColor(input, background, CV_BGR2GRAY);
	calibrated = true;
}

Mat BackgroundRemover::getForeground(Mat input) {
	Mat foregroundMask = getForegroundMask(input);

	//imshow("foregroundMask", foregroundMask);

	Mat foreground;
	input.copyTo(foreground, foregroundMask);

	return foreground;
}

Mat BackgroundRemover::getForegroundMask(Mat input) {
	Mat foregroundMask;

	if (!calibrated) {
		foregroundMask = Mat::zeros(input.size(), CV_8UC1);
		return foregroundMask;
	}

	cvtColor(input, foregroundMask, CV_BGR2GRAY);

	removeBackground(foregroundMask, background);
	
	return foregroundMask;
}

void BackgroundRemover::removeBackground(Mat input, Mat background) {
	int thresholdOffset = 10;

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			uchar framePixel = input.at<uchar>(i, j);
			uchar bgPixel = background.at<uchar>(i, j);

			if (framePixel >= bgPixel - thresholdOffset && framePixel <= bgPixel + thresholdOffset)
				input.at<uchar>(i, j) = 0;
			else
				input.at<uchar>(i, j) = 255;
		}
	}
}