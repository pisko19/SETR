/*
 * Paulo Pedreiras, 2024/03
 * Zephyr: Simple thread creation example
 * 
 * One of the tasks is (aprox.) periodc, the other two are activated via a semaphore. Data communicated via sharem memory 
 *
 * Base documentation:
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/index.html#kernel-services
 * 
 */


#include <zephyr/kernel.h>          /* for kernel functions*/
#include <zephyr/sys/printk.h>
#include <zephyr/timing/timing.h>   /* for timing services */

/* Error codes */
#define ERR_OK  0

/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority (Natural numbers, decreasing priorities)*/
#define thread_A_prio 1     /* Higher priority */
#define thread_B_prio 2
#define thread_C_prio 3     /* Lower priority */

/* Therad periodicity (in ms)*/
#define thread_A_period 1000

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

/* Global vars (shared memory between tasks A/B and B/C, resp) */
int ab = 100;
int bc = 200;

/* Semaphores for task synch */
struct k_sem sem_ab;
struct k_sem sem_bc;

/* Thread code prototypes */
void thread_A_code(void *argA, void *argB, void *argC);
void thread_B_code(void *argA, void *argB, void *argC);
void thread_C_code(void *argA, void *argB, void *argC);


/* Main function */
int main(void) {
    
    /* Welcome message */
    printk("\n\r Illustration of the use of shmem + semaphores\n\r");
   
    /* Create and init semaphores */
    k_sem_init(&sem_ab, 0, 1);
    k_sem_init(&sem_bc, 0, 1);
    
    /* Create tasks */
    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
        K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
        NULL, NULL, NULL, thread_A_prio, 0, K_NO_WAIT);

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
    /* Timing variables to control task periodicity */
    int64_t fin_time=0, release_time=0;

    /* Other variables */
    long int nact = 0;
    
    printk("Thread A init (periodic)\n");

    /* Compute next release instant */
    release_time = k_uptime_get() + thread_A_period;

    /* Thread loop */
    while(1) {
        
        /* Do the workload */          
        printk("\n\nThread A instance %ld released at time: %lld (ms). \n",++nact, k_uptime_get());  
        
        ab++;
        printk("Thread A set ab value to: %d \n",ab);  
        
        k_sem_give(&sem_ab);

       
        /* Wait for next release instant */ 
        fin_time = k_uptime_get();
        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_A_period;

        }
    }

}

void thread_B_code(void *argA , void *argB, void *argC)
{
    /* Other variables */
    long int nact = 0;

    printk("Thread B init (sporadic, waits on a semaphore by task A)\n");
    while(1) {
        k_sem_take(&sem_ab,  K_FOREVER);
        printk("Thread B instance %ld released at time: %lld (ms). \n",++nact, k_uptime_get());  
        printk("Task B read ab value: %d\n",ab);
        bc++;
        printk("Thread B set bc value to: %d \n",bc);  
        k_sem_give(&sem_bc);

        
  }
}

void thread_C_code(void *argA , void *argB, void *argC)
{
    /* Other variables */
    long int nact = 0;

    printk("Thread C init (sporadic, waits on a semaphore by task A)\n");
    while(1) {
        k_sem_take(&sem_bc, K_FOREVER);
        printk("Thread C instance %5ld released at time: %lld (ms). \n",++nact, k_uptime_get());          
        printk("Task C read bc value: %d\n",bc);

        
  }
}

