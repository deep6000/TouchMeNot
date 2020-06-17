/**
 * @file sequencer.cpp
 * @author Deepesh 
 *         Madhumitha 
 * @brief 
 * @version 0.1
 * @date 2020-04-30
 * @ref  Professor Sam Siewert's seqgen.c 
 * @copyright Copyright (c) 2020
 * 
 */
#include"common.h"
#include"sequencer.h"

void *Sequencer(void*){
 
    LOG(INFO,"Running Sequencer Thread \n");
    struct timeval current_time_val;
    struct timespec delay_time = {0,100000000}; // delay for 100msec, 10 Hz
    struct timespec remaining_time;
    double current_time;
    double residual;
    double start_time, end_time, wcet = 0;
    int rc, delay_cnt=0;
    unsigned long long seqCnt=0;

    gettimeofday(&current_time_val, (struct timezone *)0);

     do
    {
        delay_cnt=0; residual=0.0;

        do
        {
            rc=nanosleep(&delay_time, &remaining_time);

            if(rc == EINTR)
            { 
                residual = remaining_time.tv_sec + ((double)remaining_time.tv_nsec / (double)NANOSEC_PER_SEC);

                if(residual > 0.0) 
                  LOG(DEBUG,"residual=%lf, sec=%d, nsec=%d\n", residual, (int)remaining_time.tv_sec, (int)remaining_time.tv_nsec);
 
                delay_cnt++;
            }
            else if(rc < 0)
            {
                LOG(ERROR," Error Sequencer nanosleep");
                exit(-1);
            }
           
        } while((residual > 0.0) && (delay_cnt < 100));
  
        seqCnt++;
        #ifdef LOGGING
        LOG(INFO, "Sequencer Task : Scheduled for %dth time\n",seqCnt);
        #endif
        start_time = getTimeMsec();

        if((seqCnt % 1) == 0) 
          sem_post(&Semaphores[THREAD_HAND_GESTURE]);
        if((seqCnt % 5) == 0)
           sem_post(&Semaphores[THREAD_QT]);

           
        end_time  = getTimeMsec();
        #ifdef EXECUTION_TIME 
          if(wcet < (end_time - start_time))
            wcet = end_time - start_time;
          if(seqCnt == 50)
          LOG(INFO,"WCET of Sequencer Task : %lfms\n\n\n",wcet);
          #endif
        
}while(run);

  sem_post(&Semaphores[THREAD_HAND_GESTURE]);
  sem_post(&Semaphores[THREAD_QT]);
  


}