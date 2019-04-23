/*
   mythread_q.h : Function prototypes for thread q functions.
*/

extern void pthread_q_init(pthread_private_t *node);
extern void pthread_q_add(pthread_private_t *node);
extern void pthread_q_delete(pthread_private_t *node);
extern void pthread_q_state_display();
extern pthread_private_t *pthread_q_search(unsigned long);
extern void pthread_q_print_array(int **array, int size_row, int size_columns);
extern void pthread_q_array_append(void *_array, int size_row, int size_columns, int number);
extern int pthread_q_count();
extern void pthread_q_lock(unsigned long new_tid);
extern void pthread_q_unlock(unsigned long new_tid);
extern void pthread_q_lock_all();
extern void pthread_q_unlock_fifo();
extern void pthread_q_unlock_lottery(void *_array, int size);
extern int pthread_q_array_verify(int **array, int size_row, int size_columns, int rand);
extern void pthread_q_array_fill(int **array, int size_row, int size_columns);
extern int pthread_q_array_isfull(int **array, int size_row, int size_columns);
extern int pthread_q_array_simple_isfull(void *_array, int size);
extern int pthread_q_array_simple_verify(void *_array, int size, int rand);
extern void pthread_q_array_simple_fill(void *_array, int size);
extern void pthread_q_array_simple_append(void *_array, int size, int number);
extern void pthread_q_print_array_simple(void *_array, int size);
extern void pthread_q_choose_tickets(void *_array, int size_row, int size_columns, void *_tickets);
extern void pthread_q_lottery();
extern void pthread_q_queue_fill_pid(void *_array, int size);
extern void pthread_q_swap_rr(void *_array, int size);
