/**
 * @file SkinDetector.h
 * 
 * @brief 
 * @version 0.1
 * @date 2020-05-02
 *  * /// Code is inspired from the following github repo. Modifications are made based on our requirement.
 * @ref https://github.com/PierfrancescoSoffritti/Handy
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include<opencv/cv.h>

/*
 Author: Pierfrancesco Soffritti https://github.com/PierfrancescoSoffritti
*/

using namespace cv;
using namespace std;

class SkinDetector {
	public:
		SkinDetector(void);

		void drawSkinColorSampler(Mat input);
		void calibrate(Mat input);
		Mat getSkinMask(Mat input);

	private:
		int hLowThreshold = 0;
		int hHighThreshold = 0;
		int sLowThreshold = 0;
		int sHighThreshold = 0;
		int vLowThreshold = 0;
		int vHighThreshold = 0;

		bool calibrated = false;

		Rect skinColorSamplerRectangle1, skinColorSamplerRectangle2;

		void calculateThresholds(Mat sample1, Mat sample2);
		void performOpening(Mat binaryImage, int structuralElementShapde, Point structuralElementSize);
};