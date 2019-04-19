/*
   mythread_q.h : Function prototypes for thread q functions.
*/

extern void mythread_q_init(mythread_private_t *node);
extern void mythread_q_add(mythread_private_t *node);
extern void mythread_q_delete(mythread_private_t *node);
extern void mythread_q_state_display();
extern mythread_private_t *mythread_q_search(unsigned long);
extern void mythread_q_print_array(int **array, int size_row, int size_columns);
extern void mythread_q_array_append(void *_array, int size_row, int size_columns, int number);
extern int mythread_q_count();
extern void mythread_q_lock(unsigned long new_tid);
extern void mythread_q_unlock(unsigned long new_tid);
extern void mythread_q_lock_all();
extern void mythread_q_unlock_fifo();
extern void mythread_q_unlock_lottery(void *_array, int size);
extern int mythread_q_array_verify(int **array, int size_row, int size_columns, int rand);
extern void mythread_q_array_fill(int **array, int size_row, int size_columns);
extern int mythread_q_array_isfull(int **array, int size_row, int size_columns);
extern int mythread_q_array_simple_isfull(void *_array, int size);
extern int mythread_q_array_simple_verify(void *_array, int size, int rand);
extern void mythread_q_array_simple_fill(void *_array, int size);
extern void mythread_q_array_simple_append(void *_array, int size, int number);
extern void mythread_q_print_array_simple(void *_array, int size);
extern void mythread_q_choose_tickets(void *_array, int size_row, int size_columns, void *_tickets);
extern void mythread_q_lottery();
