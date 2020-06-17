/**
 * @file hand_detection.cpp
 * 
 * @brief 
 * @version 0.1
 * @date 2020-05-02
 *  * /// Code is inspired from the following github repo. Modifications are made based on our requirement.
 * @ref https://github.com/PierfrancescoSoffritti/Handy
 * @copyright Copyright (c) 2020
 * 
 */
#include"hand_detection.h"
#include"common.h"
#include<stdbool.h>


volatile bool start_hand_detection = false;
volatile bool start_sending = false;

void *DetectFingers(void*){

    int count = 0;
    static double execution_time;
    double start_time = 0,end_time = 0;
	
    LOG(INFO,"Running Hand Detection Thread\n");
    VideoCapture videoCapture(0);
	videoCapture.set(CV_CAP_PROP_SETTINGS, 1);

	if (!videoCapture.isOpened()) {
		LOG(ERROR, "Cant Find the Camera\n");
        run = false;
	}
	Mat frame, frameOut, handMask, foreground, fingerCountDebug, questionframe;

	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	FingerCount fingerCount;
	

	while (run) {
        sem_wait(&Semaphores[THREAD_HAND_GESTURE]);
		count++;
		#ifdef LOGGING
		LOG(INFO, "Hand Detection Task: Scheduled for %dth time\n",count);
		#endif
    #ifdef EXECUTION_TIME 
            start_time = getTimeMsec();
    #endif
		videoCapture >> frame;
		frameOut = frame.clone();
		skinDetector.drawSkinColorSampler(frameOut);
		foreground = backgroundRemover.getForeground(frame);
		faceDetector.removeFaces(frame, foreground);
		handMask = skinDetector.getSkinMask(foreground);
		fingerCountDebug = fingerCount.findFingersCount(handMask, frameOut);

	    #ifdef EXECUTION_TIME 
        end_time = getTimeMsec();
            if( execution_time < end_time - start_time )
                execution_time = end_time - start_time;
            if(count == 100){
                LOG(INFO,"WCET time for Hand Detection Thread is is %lfms\n\n",execution_time);   
        }
    #endif    
		questionframe = *question;
		imshow("output", frameOut);  
		imshow("Feedback",questionframe);
		//imshow("foreground", foreground);
		//imshow("handMask", handMask);
		//imshow("handDetection", fingerCountDebug);
	
		char key = cvWaitKey(1) & 0xFF;
		
		if (key == 27){ // esc
			start_hand_detection = false;
            run = false;
            break;
           
        }
		
		else if (key =='b'){ // b
		
			backgroundRemover.calibrate(frame);
        }
		else if (key == 's'){ // s
			skinDetector.calibrate(frame);
            start_hand_detection = true;
		}
		
		else if (key == 'o')
			start_sending = true;
		
	}



}