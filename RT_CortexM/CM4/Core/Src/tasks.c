/* This is a small demo of the high-performance ThreadX kernel.  It includes examples of eight
   threads of different priorities, using a message queue, semaphore, mutex, event flags group, 
   byte pool, and block pool.  */

#include "tx_api.h"
#include "openamp.h"
#include "main.h"
// #include "stm32mp1xx_hal_gpio.h"
#include "gpio.h"
#include <stdio.h>

#define DEMO_STACK_SIZE         1024
#define DEMO_BYTE_POOL_SIZE     9120
#define DEMO_BLOCK_POOL_SIZE    100
#define DEMO_QUEUE_SIZE         100

/* Define the priority used by threads */

#define MAIN_TASK_PRIORITY          100U
#define IDLE_TASK_PRIORITY          255U
#define CYCLE_5MS_TASK_PRIORITY     5U
#define CYCLE_10MS_TASK_PRIORITY    10U
#define CYCLE_25MS_TASK_PRIORITY    15U
#define CYCLE_50MS_TASK_PRIORITY    50U

#define MAIN_TASK_PRIORITY_THR       MAIN_TASK_PRIORITY
#define IDLE_TASK_PRIORITY_THR       IDLE_TASK_PRIORITY
#define CYCLE_5MS_TASK_PRIORITY_THR  CYCLE_5MS_TASK_PRIORITY
#define CYCLE_10MS_TASK_PRIORITY_THR CYCLE_10MS_TASK_PRIORITY
#define CYCLE_25MS_TASK_PRIORITY_THR CYCLE_25MS_TASK_PRIORITY
#define CYCLE_50MS_TASK_PRIORITY_THR CYCLE_50MS_TASK_PRIORITY
/* Define the ThreadX object control blocks...  */

TX_THREAD               thread_main;
TX_THREAD               thread_idle;
TX_THREAD               threadx_5ms;
TX_THREAD               threadx_10ms;
TX_THREAD               threadx_25ms;
TX_THREAD               threadx_50ms;

TX_QUEUE                queue_0;
TX_SEMAPHORE            semaphore_0;
TX_MUTEX                mutex_0;
TX_EVENT_FLAGS_GROUP    event_flags_0;
TX_BYTE_POOL            byte_pool_0;
TX_BLOCK_POOL           block_pool_0;
UCHAR                   memory_area[DEMO_BYTE_POOL_SIZE];

TX_TIMER    timer_5ms;
TX_TIMER    timer_10ms;
TX_TIMER    timer_25ms;
TX_TIMER    timer_50ms;


/* Define the counters used in the demo application...  */

 ULONG                   thread_50ms_counter;



/* Define thread prototypes.  */

void    thread_main_entry(ULONG thread_input);
void    thread_idle_entry(ULONG thread_input);
void    threadx_5ms_entry(ULONG thread_input);
void    threadx_10ms_entry(ULONG thread_input);
void    threadx_25ms_entry(ULONG thread_input);
void    threadx_50ms_entry(ULONG thread_input);

void timer_5ms_callback(ULONG id);
void timer_10ms_callback(ULONG id);
void timer_25ms_callback(ULONG id);
void timer_50ms_callback(ULONG id);

static void Inter_Processor_Communication_Remote_Core(void);

/* Define main entry point.  */

//int main()
//{
//
//    /* Enter the ThreadX kernel.  */
//    tx_kernel_enter();
//}


/* Define what the initial system looks like.  */

void    tx_application_define(void *first_unused_memory)
{

CHAR    *pointer = TX_NULL;


    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", memory_area, DEMO_BYTE_POOL_SIZE);

    /* Put system definition stuff in here, e.g. thread creates and other assorted
       create information.  */

    /* Allocate the stack for thread main.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    /* Create the main thread.  */
    tx_thread_create(&thread_main, "main thread", thread_main_entry, 0,  
            pointer, DEMO_STACK_SIZE, 
            MAIN_TASK_PRIORITY, MAIN_TASK_PRIORITY_THR, TX_NO_TIME_SLICE, TX_AUTO_START);


    /* Allocate the stack for thread idle.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    /* Create threads 1 and 2. These threads pass information through a ThreadX 
       message queue.  It is also interesting to note that these threads have a time
       slice.  */
    tx_thread_create(&thread_idle, "idle thread", thread_idle_entry, 1,  
            pointer, DEMO_STACK_SIZE, 
            IDLE_TASK_PRIORITY, IDLE_TASK_PRIORITY_THR, 4, TX_AUTO_START);

    /* Allocate the stack for thread 2.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&threadx_5ms, "5ms cyclic task", threadx_5ms_entry, 2,  
            pointer, DEMO_STACK_SIZE, 
            CYCLE_5MS_TASK_PRIORITY, CYCLE_5MS_TASK_PRIORITY_THR, 4, TX_AUTO_START);

    /* Allocate the stack for thread 3.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    /* Create threads 3 and 4.  These threads compete for a ThreadX counting semaphore.  
       An interesting thing here is that both threads share the same instruction area.  */
    tx_thread_create(&threadx_10ms, "10ms cyclic task", threadx_10ms_entry, 3,  
            pointer, DEMO_STACK_SIZE, 
            CYCLE_10MS_TASK_PRIORITY, CYCLE_10MS_TASK_PRIORITY_THR, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Allocate the stack for thread 4.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&threadx_25ms, "25ms cyclic task", threadx_25ms_entry, 4,  
            pointer, DEMO_STACK_SIZE, 
            CYCLE_25MS_TASK_PRIORITY, CYCLE_25MS_TASK_PRIORITY_THR, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Allocate the stack for thread 5.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    /* Create thread 5.  This thread simply pends on an event flag which will be set
       by thread_main.  */
    tx_thread_create(&threadx_50ms, "50ms cyclic task", threadx_50ms_entry, 5,  
            pointer, DEMO_STACK_SIZE, 
            CYCLE_50MS_TASK_PRIORITY, CYCLE_50MS_TASK_PRIORITY_THR, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Allocate the message queue.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);

    /* Create the message queue shared by threads 1 and 2.  */
    tx_queue_create(&queue_0, "queue 0", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    /* Create the semaphore used by threads 3 and 4.  */
    tx_semaphore_create(&semaphore_0, "semaphore 0", 1);

    /* Create the event flags group used by threads 1 and 5.  */
    tx_event_flags_create(&event_flags_0, "event flags 0");

    /* Create the mutex used by thread 6 and 7 without priority inheritance.  */
    tx_mutex_create(&mutex_0, "mutex 0", TX_NO_INHERIT);

    // /* Allocate the memory for a small block pool.  */
    // tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_BLOCK_POOL_SIZE, TX_NO_WAIT);

    // /* Create a block memory pool to allocate a message buffer from.  */
    // tx_block_pool_create(&block_pool_0, "block pool 0", sizeof(ULONG), pointer, DEMO_BLOCK_POOL_SIZE);

    // /* Allocate a block and release the block memory.  */
    // tx_block_allocate(&block_pool_0, (VOID **) &pointer, TX_NO_WAIT);

    // /* Release the block back to the pool.  */
    // tx_block_release(pointer);

    /* Timer create. */
    tx_timer_create(&timer_5ms,  "cyclic timer 5ms",  timer_5ms_callback,  5, 50, 50,   TX_AUTO_ACTIVATE);
    tx_timer_create(&timer_10ms, "cyclic timer 10ms", timer_10ms_callback, 10, 100, 100, TX_AUTO_ACTIVATE);
    tx_timer_create(&timer_25ms, "cyclic timer 25ms", timer_25ms_callback, 25, 250, 250, TX_AUTO_ACTIVATE);
    tx_timer_create(&timer_50ms, "cyclic timer 50ms", timer_50ms_callback, 50, 500, 500, TX_AUTO_ACTIVATE);

}

void timer_5ms_callback(ULONG id)
{
    tx_thread_resume(&threadx_5ms);
}

void timer_10ms_callback(ULONG id)
{
    tx_thread_resume(&threadx_10ms);
}

void timer_25ms_callback(ULONG id)
{
    tx_thread_resume(&threadx_25ms);
}

void timer_50ms_callback(ULONG id)
{
    tx_thread_resume(&threadx_50ms);
}

/* Define the test threads.  */

void    thread_main_entry(ULONG thread_input)
{
    /* This thread simply sits in while-forever-sleep loop.  */
    while(1)
    {
    	tx_thread_sleep(100);
    	Inter_Processor_Communication_Remote_Core();
    }
}


void    thread_idle_entry(ULONG thread_input)
{
    while(1)
    {
        /* Do something in idle task, like task statistics. */
    }
}


void    threadx_5ms_entry(ULONG thread_input)
{
    while(1)
    {
        printf("5ms cyclic task is running!\n");
        tx_thread_suspend(&threadx_5ms);
    }
}


void    threadx_10ms_entry(ULONG thread_input)
{
    while(1)
    {
        printf("10ms cyclic task is running!\n");
        tx_thread_suspend(&threadx_10ms);
    }
}

void    threadx_25ms_entry(ULONG thread_input)
{
    while(1)
    {
        printf("25ms cyclic task is running!\n");
        tx_thread_suspend(&threadx_25ms);
    }
}

void    threadx_50ms_entry(ULONG thread_input)
{
    /* This thread simply waits for an event in a forever loop.  */
    while(1)
    {
    	if((thread_50ms_counter++) % 10u)
    	{
    		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_3);
    	}
        printf("50ms cyclic task is running!\n");
        tx_thread_suspend(&threadx_50ms);
    }
}


uint32_t count = 0; /* Number of send times */
uint8_t msg[32]; /* Message copy buffer */
extern __IO FlagStatus rx_status;
extern struct rpmsg_endpoint resmgr_ept;
static void Inter_Processor_Communication_Remote_Core(void)
{
	OPENAMP_check_for_message();

	if(rx_status == SET)
	{
		rx_status = RESET;

		if(count++ < 100)
		{
			sprintf((char *)msg, "M4 -> A7  %02ld", count);
		}
		else
		{
			strcpy((char *)msg, "goodbye!");
		}

		if(OPENAMP_send(&resmgr_ept, msg, strlen((char *)msg) + 1) < 0)
		{
			printf("Failed to send message\r\n");
			Error_Handler();
		}

		printf("%s\r\n", msg);
	}
}

