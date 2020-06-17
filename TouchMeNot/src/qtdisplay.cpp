#include"qtdisplay.h"

using namespace cv;
using namespace std;
volatile bool LookingforOption = false;

const unsigned int OptionXCordinates[6] = {113,202,294,384,474};
const unsigned int OptionYCordinate = 328;
const unsigned int Radius  = 43;
Mat current_question;
Mat * question = &current_question;


void
*executeQT(void*){
    int count = 0;
    double start_time, end_time;
    double wcet;
    Scalar color_red = Scalar(0, 0, 255);
    LOG(INFO,"Running UI Display Thread\n");
    Option OptionSelected;
    option_e displayOption;

    char frameName[15];
    uint8_t question_number = 1;
    Point centre;
    snprintf(frameName,15,"question%d.jpg",question_number);
    current_question = imread(frameName,CV_LOAD_IMAGE_COLOR);
      if(! current_question.data )                              // Check for invalid input
        LOG(ERROR, "Could not open Image");
    
    while(run){
    
        sem_wait(&Semaphores[THREAD_QT]);
            count++;
            #ifdef LOGGING
            LOG(INFO, "Display UI Task : Scheduled for %dth time\n",count);
            #endif
            LookingforOption = true;
        #ifdef EXECUTION_TIME 
            start_time = getTimeMsec();
            count++;
        #endif
        if(RECEIVE_OPTION(QueueOption,OptionSelected)!= -1){
        
           
            displayOption = OptionSelected.option;
            #ifdef LOGGING
            LOG(INFO,"Display UI Task : Message Received Option Selected %d\n",displayOption);
            #endif
            LookingforOption = false;
            centre.x = OptionXCordinates[displayOption - 1];
            centre.y = OptionYCordinate;
            circle(current_question,centre,Radius,color_red,3, 8, 0); 
            question_number &= 3;
            question_number++;
            memset(&frameName,0,15);
            snprintf(frameName,15,"question%d.jpg",question_number);
            sleep(2);
            current_question = imread(frameName,CV_LOAD_IMAGE_COLOR);
            sleep(2);
            LookingforOption = true;
            // for user to read so that it can read the question 
           
        }
        #ifdef EXECUTION_TIME 
            end_time = getTimeMsec();
            if(wcet < (end_time-start_time))    
                wcet = end_time - start_time ;
            if(count ==  5)
                LOG(INFO,"Worst Case Execution Time UI Task is : %lfms\n\n\n\n", wcet);       
        #endif
    }




}
