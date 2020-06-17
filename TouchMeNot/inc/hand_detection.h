/**
 * @file hand_detection.h
 * @author Deepesh
 *         Madhumitha
 * @brief 
 * @version 0.1
 * @date 2020-04-30
 *  * /// Code is inspired from the following github repo. Modifications are made based on our requirement.
 * @ref https://github.com/PierfrancescoSoffritti/Handy
 * @copyright Copyright (c) 2020
 * 
 */



#ifndef HAND_DETECT
#define HAND_DETECT

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"
#include "common.h"

void *DetectFingers(void*);

#endif