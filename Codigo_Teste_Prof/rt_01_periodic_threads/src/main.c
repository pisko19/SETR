/*
 * Paulo Pedreiras, 2024/02
 * Zephyr: Simple thread creation example - with timers
 * 
 * Periodic tasks using timers
 *
 * In Zephyr there are severel timing functions. Timers can be set to generate one-time or
 *      periodic events, and also call a function when expire.
 * 
 * In this example timers are set to generate perioc events (that match the tasks' period), 
 *      and one function (k_timer_status_sync() ) is used to synchronize the task with
 *      the timer expiration. The function blocks the task until the timer’s status is non-zero (expired at least once)
 *      Note that this function resets the timer status. 
 *      Note also that the timer status is changed also when the timer is stopped (not an issue in this case as the timer is not stopped).
 * 
 *  Timers documentation:
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/timing/timers.html#timers
 * 
 * * Base documentation:      
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/index.html#kernel-services
 * 
 */

#include <zephyr/kernel.h>          /* for kernel functions*/
#include <zephyr/sys/printk.h>      /* for printk()*/
#include <zephyr/timing/timing.h>   /* Kernel timing services */

/* Error codes */
#define ERR_OK  0

/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority: 1...MAX, decreasing (smaller value -> Higher priority) */
#define thread_A_prio 1 /* Higher priority */     
#define thread_B_prio 2 /* Intermediate priority */
#define thread_C_prio 3 /* Lower priority */

/* Thread periodicity (in ms)*/
#define thread_A_period 1000
#define thread_B_period 2000
#define thread_C_period 4000

/* Create thread stack space */
K_THREAD_STACK_DEFINE(thread_A_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_B_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_C_stack, STACK_SIZE);
  
/* Create variables for thread data */
struct k_thread thread_A_data;
struct k_thread thread_B_data;
struct k_thread thread_C_data;

/* Create task IDs */
k_tid_t thread_A_tid;
k_tid_t thread_B_tid;
k_tid_t thread_C_tid;

/* Thread code prototypes */
void thread_A_code(void *argA, void *argB, void *argC);
void thread_B_code(void *argA, void *argB, void *argC);
void thread_C_code(void *argA, void *argB, void *argC);

/* Define timers for tasks activations */
K_TIMER_DEFINE(thread_A_timer, NULL, NULL);
K_TIMER_DEFINE(thread_B_timer, NULL, NULL);
K_TIMER_DEFINE(thread_C_timer, NULL, NULL);

/* Main function */
int main(void) {

    int arg1=0, arg2=0, arg3=0; // Input args of tasks (actually not used in this case)

    /* Crate three tasks */

    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
        K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
        &arg1, &arg2, &arg3, thread_A_prio, 0, K_NO_WAIT);

    thread_B_tid = k_thread_create(&thread_B_data, thread_B_stack,
        K_THREAD_STACK_SIZEOF(thread_B_stack), thread_B_code,
        NULL, NULL, NULL, thread_B_prio, 0, K_NO_WAIT);

    thread_B_tid = k_thread_create(&thread_C_data, thread_C_stack,
        K_THREAD_STACK_SIZEOF(thread_C_stack), thread_C_code,
        NULL, NULL, NULL, thread_C_prio, 0, K_NO_WAIT);

    return ERR_OK;

} 

/* Thread code implementation */
void thread_A_code(void *argA , void *argB, void *argC)
{
    /* Variables to time release and execution */
    timing_t time_stamp;

    printk("Thread A init (periodic)\n");

    /* Start periodic timer that expires once every thread_A_period ms */
    k_timer_start(&thread_A_timer, K_MSEC(thread_A_period), K_MSEC(thread_A_period));

    /* Thread loop */
    while(1) {
        
        /* Wait for timer event */
        k_timer_status_sync(&thread_A_timer);

        /* Do the workload */          
        time_stamp = k_uptime_get();
        printk("Thread A instance released at time: %lld (ms). \n",time_stamp);  
        {
            int i=0, j=1;
            for (i=0;i<10000;i++)
                j+=((float)i/3);
        }

        
    }
}


void thread_B_code(void *argA , void *argB, void *argC)
{
    /* Variables to time release and execution */
    timing_t time_stamp;

    printk("Thread B init (periodic)\n");

    /* Start periodic timer that expires once every thread_A_period ms */
    k_timer_start(&thread_B_timer, K_MSEC(thread_B_period), K_MSEC(thread_B_period));

    /* Thread loop */
    while(1) {
        
        /* Wait for timer event */
        k_timer_status_sync(&thread_B_timer);

        /* Do the workload */  
        time_stamp = k_uptime_get();
        printk("Thread B instance released at time: %lld (ms). \n",time_stamp);  
        {
            int i=0, j=1;
            for (i=0;i<10000;i++)
                j+=((float)i/3);
        }
        
    }
}


void thread_C_code(void *argA , void *argB, void *argC)
{
    /* Variables to time release and execution */
    timing_t time_stamp;

    printk("Thread C init (periodic)\n");

    /* Start periodic timer that expires once every thread_A_period ms */
    k_timer_start(&thread_C_timer, K_MSEC(thread_C_period), K_MSEC(thread_C_period));

    /* Thread loop */
    while(1) {
        
        /* Wait for timer event */
        k_timer_status_sync(&thread_C_timer);

        /* Do the workload */  
        time_stamp = k_uptime_get();
        printk("Thread C instance released at time: %lld (ms). \n",time_stamp);  
        {
            int i=0, j=1;
            for (i=0;i<10000;i++)
                j+=((float)i/3);
        }
        
    }
}
