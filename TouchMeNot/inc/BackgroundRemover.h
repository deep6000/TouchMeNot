/**
 * @file BackgroundRemover.h
 * @brief 
 * @version 0.1
 * @date 2020-05-02
 * /// Code is inspired from the following github repo. Modifications are made based on our requirement.
 * @ref https://github.com/PierfrancescoSoffritti/Handy
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include<opencv/cv.h>


using namespace cv;
using namespace std;

class BackgroundRemover {
	public:
		BackgroundRemover(void);
		void calibrate(Mat input);
		Mat getForeground(Mat input);

	private:
		Mat background;
		bool calibrated = false;

		Mat getForegroundMask(Mat input);
		void removeBackground(Mat input, Mat background);
};