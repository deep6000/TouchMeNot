/**
 * @file main.c
 * @author Deepesh
 *         Madhumitha
 * @brief 
 * @version 0.1
 * @date 2020-04-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */



#include "common.h" 
#include "hand_detection.h"
#include "sequencer.h"
#include "qtdisplay.h"
#include "logging.h"

#define PRIORITY


bool run = true;
pthread_t Threads[NUM_OF_THREADS];
sem_t Semaphores[NUM_OF_THREADS];
mqd_t QueueOption;
pthread_mutex_t windowLock;
void* (*thread_func[ NUM_OF_THREADS ])( void* ) = {
    Sequencer,
    DetectFingers,
    executeQT};

void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
       case SCHED_FIFO:
           LOG(INFO,"Pthread Policy is SCHED_FIFO\n");
           break;
       case SCHED_OTHER:
           LOG(INFO,"Pthread Policy is SCHED_OTHER\n"); exit(-1);
         break;
       case SCHED_RR:
           LOG(INFO,"Pthread Policy is SCHED_RR\n"); exit(-1);
           break;
       default:
           LOG(INFO,"Pthread Policy is UNKNOWN\n"); exit(-1);
   }
}


void createThreads()
{
    
    ThreadParams thread_params[NUM_OF_THREADS];
    pthread_attr_t rt_sched_attr[NUM_OF_THREADS];
    int rt_max_prio, rt_min_prio, scope, rc;
    struct sched_param rt_param[NUM_OF_THREADS];
    struct sched_param main_param;
    pthread_attr_t main_attr;
    pid_t mainpid;
  
  #ifdef PRIORITY
    mainpid=getpid();
    rt_max_prio = sched_get_priority_max(SCHED_FIFO);
    rt_min_prio = sched_get_priority_min(SCHED_FIFO);

    rc=sched_getparam(mainpid, &main_param);
    main_param.sched_priority=rt_max_prio;
    rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
    if(rc < 0) LOG(ERROR,"main_param");
    print_scheduler();
    pthread_attr_getscope(&main_attr, &scope);
       
    for(int i=0; i < NUM_OF_THREADS; i++){

      rc=pthread_attr_init(&rt_sched_attr[i]);
      rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
      rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
      rt_param[i].sched_priority=rt_max_prio-i;
      pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
      thread_params[i].ThreadID=(thread_e)i;
    }
   #endif
    
    for(uint8_t tasks = 0  ; tasks< NUM_OF_THREADS; tasks++)
    pthread_create(&Threads[tasks],&rt_sched_attr[tasks],thread_func[tasks], (void*)&(thread_params[tasks]));



}

void
InitializeSemaphores(){

    for(int i =0 ; i < NUM_OF_THREADS; i++){      
        if(sem_init(&Semaphores[i],0,0))
            LOG(ERROR, "Semaphore Initialization Error\n");
    }
    
}

int QueueInit(){
    mqd_t ret_mq;
    struct mq_attr main_mqattr;
    main_mqattr.mq_msgsize = sizeof(Option);
    main_mqattr.mq_maxmsg = 128;
    main_mqattr.mq_flags = 0;

    mq_unlink(MQ_OPTION);
    ret_mq = mq_open(MQ_OPTION,O_CREAT | O_RDWR | O_NONBLOCK, 0666, &main_mqattr);

    return ret_mq; 
}

void InitializeLock(){
    pthread_mutex_init( &windowLock, NULL );
}



int main(int argc, char* argv[]){

  

    LOG(INFO,"Starting Hand Detection Application\n");
    QueueOption = QueueInit();
    InitializeLock();
    //namedWindow( "output", WINDOW_AUTOSIZE);
    //namedWindow( "Feedback", WINDOW_AUTOSIZE);
    createThreads();
    
    for ( int thread = 0; thread < NUM_OF_THREADS; thread++ )
         pthread_join(Threads[thread], NULL );
    
      

  exit(0);




}