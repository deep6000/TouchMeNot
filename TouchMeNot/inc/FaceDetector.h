/**
 * @file FaceDetector.h
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

class FaceDetector {
	public:
		FaceDetector(void);
		void removeFaces(Mat input, Mat output);
};