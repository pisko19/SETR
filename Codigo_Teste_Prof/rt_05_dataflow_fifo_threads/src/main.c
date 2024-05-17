/*
 * Paulo Pedreiras, 2023/03
 * Zephyr: Simple task synchronization example
 * 
 * One of the tasks is periodic, the other two synchronzie via fifos 
 *      Uses dynamic memory allocation, using the system heap. 
 *      System heap size set via CONFIG_HEAP_MEM_POOL_SIZE in prj.conf
 *      Allocation / release of memory carrie dout via k_malloc()/k_free() 
 * 
 * Base documentation:
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/index.html#kernel-services
 * 
 */

#include <zephyr/kernel.h>          /* for kernel functions*/
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/timing/timing.h>   /* for timing services */

/* Error codes */
#define ERR_OK  0

/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority (natural numbers, decreasing priority) */
#define thread_A_prio 1     // Higher priority 
#define thread_B_prio 2
#define thread_C_prio 3     // Lower priority

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

/* Create fifos*/
struct k_fifo fifo_ab;
struct k_fifo fifo_bc;

/* Create fifo data structure and variables */
struct data_item_t {
    void *fifo_reserved;    /* 1st word reserved for use by FIFO */
    uint16_t data;          /* Actual data */
};

/* Thread code prototypes */
void thread_A_code(void *, void *, void *);
void thread_B_code(void *, void *, void *);
void thread_C_code(void *, void *, void *);


/* Main function */
int main(void) {

    /* Welcome message */
     printk("\n\r IPC via FIFO example \n\r");
    
    /* Create/Init fifos */
    k_fifo_init(&fifo_ab);
    k_fifo_init(&fifo_bc);
        
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

    /* FIFO related variables */
    size_t FIFO_elem_size = sizeof(struct data_item_t);
    struct data_item_t *FIFO_elem_ptr;

    /* Other local variables */
    long int nact = 0;
    
    
    printk("Thread A init (periodic)\n");

    /* Compute next release instant */
    release_time = k_uptime_get() + thread_A_period;
    
    /* Thread loop */
    while(1) {
        
        /* Do the workload */          
        printk("\n\nThread A instance %ld released at time: %lld (ms). \n",++nact, k_uptime_get());  
                
#if 0
        /* Standard malloc/free don't work. */
        /* It compiles and links, but using an implict declaration. */
        /* Activate this section to see what happens */ 
        FIFO_elem_ptr=malloc(FIFO_elem_size);
        printk("Ponteiro: %p\n\r", FIFO_elem_ptr);
        while(1);
#else        
        FIFO_elem_ptr = k_malloc(FIFO_elem_size); 
#endif
        if( FIFO_elem_ptr == NULL) {
            printk("Failed to allocate memory for FIFO ab\n");
        } else {
            FIFO_elem_ptr->data = (nact + 100);
            k_fifo_put(&fifo_ab, FIFO_elem_ptr);
            printk("Thread A data in fifo_ab: %d\n",FIFO_elem_ptr->data);  
        }
       
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
    /* Local variables */
    long int nact = 0;
    
    /* FIFO related variables */
    size_t FIFO_elem_size = sizeof(struct data_item_t);
    struct data_item_t *FIFO_ab_elem_ptr;
    struct data_item_t *FIFO_bc_elem_ptr;

    printk("Thread B init (sporadic, waits on a FIFO ab)\n");
    while(1) {
        
        
        /* Wait for data in FIFO ab */
        FIFO_ab_elem_ptr = k_fifo_get(&fifo_ab, K_FOREVER);
    
        /* Get data from FIFO and release memory */
        printk("Thread B instance %ld released at time: %lld (ms). \n",++nact, k_uptime_get());  
        printk("Task B read fifo ab value: %d\n",FIFO_ab_elem_ptr->data);
        k_free(FIFO_ab_elem_ptr);

        /* NOTE */
        /* Strictly speaking, in this case it s not necessary to release and allocate again memory */
        /*    because the elements of fifos "ab" and "bc" are similar. But to keep the example */ 
        /*    generic, it is done this way */
         
        /* Send data to FIFO bc */
        FIFO_bc_elem_ptr = k_malloc(FIFO_elem_size);
        if(FIFO_bc_elem_ptr == NULL) {
            printk("Failed to allocate memory for FIFO bc\n");
        } 
        else {        
            FIFO_bc_elem_ptr->data = nact + 200;

            k_fifo_put(&fifo_bc, FIFO_bc_elem_ptr);
            printk("Thread B set fifo bc value to: %d \n",FIFO_bc_elem_ptr->data);     
        }
               
  }
}

void thread_C_code(void *argA , void *argB, void *argC)
{
    /* Local variables */
    long int nact = 0;

    /* FIFO related variables */
    struct data_item_t *FIFO_bc_elem_ptr;

    printk("Thread C init (sporadic, waits on a FIFO bc)\n");
    while(1) {
        FIFO_bc_elem_ptr = k_fifo_get(&fifo_bc, K_FOREVER);
        printk("Thread C instance %5ld released at time: %lld (ms). \n",++nact, k_uptime_get());          
        printk("Task C read bc value: %d\n",FIFO_bc_elem_ptr->data);
        k_free(FIFO_bc_elem_ptr);
            
  }
}

