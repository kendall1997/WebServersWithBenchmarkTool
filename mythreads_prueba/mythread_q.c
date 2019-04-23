#define _GNU_SOURCE
#include <mythread.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

/* The global extern pointer defined in mythread.h which points to the head node in
   Queue of the Thread Control Blocks.
*/
pthread_private_t *pthread_q_head;
int *scheduler_type;

/* This function initializes the Queue with a single node.
*/
void pthread_q_init(pthread_private_t *node)
{

    node->prev = node;
    node->next = node;

    pthread_q_head = node;
}

/* This function adds a node to the Queue, at the end of the Queue. 
   This is equivalent to Enque operation.
 */
void pthread_q_add(pthread_private_t *node)
{

    if (pthread_q_head == NULL)
    {

        pthread_q_init(node);
        return;
    }

    node->next = pthread_q_head;
    node->prev = pthread_q_head->prev;
    pthread_q_head->prev->next = node;
    pthread_q_head->prev = node;

    return;
}

/* This function deleted a specified(passed as a parameter) node from the Queue.
 */
void pthread_q_delete(pthread_private_t *node)
{

    pthread_private_t *p;
    if (node == pthread_q_head && node->next == pthread_q_head)
    {
        printf("The Q is now Empty!\n");
        pthread_q_head = NULL;
    }

    if (node == pthread_q_head)
        pthread_q_head = node->next;

    p = node->prev;

    p->next = node->next;
    node->next->prev = p;

    return;
}

/* This function iterates over the ntire Queue and prints out the state(see mythread.h to refer to various states)
   of all the tcb members.
 */
void pthread_q_state_display()
{

    if (pthread_q_head != NULL)
    {

        printf("\n The Q contents are -> \n");
        pthread_private_t *p;
        p = pthread_q_head;
        do
        {
            printf(" %d\n", p->state);
            p = p->next;
        } while (p != pthread_q_head);
    }
}

/* This function iterates over the Queue and prints out the state of the specified thread.
 */
pthread_private_t *pthread_q_search(unsigned long new_tid)
{

    pthread_private_t *p;
    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;
        do
        {
            if (p->tid == new_tid)
                return p;
            p = p->next;
        } while (p != pthread_q_head);
    }
    return NULL;
}

/**
 * This functions is used to lock all the treads 
 * except the thread is given
 * */

void pthread_q_lock(unsigned long new_tid)
{
    pthread_private_t *p;

    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;

        do
        {
            if (p->tid != new_tid)
            {
                printf("BLOCKING T %d \n\n", p->tid);
                p->state = BLOCKED;
                kill(p->tid, SIGSTOP);
            }
            p = p->next;
        } while (p != pthread_q_head);
    }
}

/**
 * This function is for unlock all the treads
 * except the thread is given
 * */

void pthread_q_unlock(unsigned long new_tid)
{

    pthread_private_t *p;

    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;

        do
        {
            if (p->tid != new_tid)
            {
                printf("UNBLOCKING T %d \n\n", p->tid);
                p->state = READY;
                kill(p->tid, SIGCONT);
            }
            p = p->next;
        } while (p != pthread_q_head);
    }
}

/**
 * This function lock all the threads 
 * */

void pthread_q_lock_all()
{
    pthread_private_t *p;

    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;

        do
        {
            kill(p->tid, SIGSTOP);
            p->state = BLOCKED;
            printf("STOPPING T %d \n\n", p->tid);
            p = p->next;
        } while (p != pthread_q_head);
    }
}

/**
 * This function unlock the threads in a FIFO
 * form
 * */

void pthread_q_unlock_fifo()
{
    pthread_private_t *p;

    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;

        int flag = FALSE;
        do
        {
            pthread_t t;

            t.tid = p->tid;

            pthread_join(t, NULL);

            p = p->next;

        } while (p != pthread_q_head);
    }
}

/**
 * Function that makes all the threads
 * of the lottery scheduler run
 * */

void pthread_q_unlock_lottery(void *_array, int size)
{
    pthread_private_t *p;
    int number = 0;
    int i = 0;
    int(*array) = _array;
    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;

        int flag = FALSE;
        do
        {

            if (p == pthread_q_head)
            {

                i = 0;
            }

            if (array[number] == i)
            {
                pthread_t t;
                t.tid = p->tid;
                printf("UNBLOCKING %d\n", t.tid);

                number++;
                pthread_join(t, NULL);
            }

            p = p->next;
            i++;

        } while ((number != size));
    }
}

/**
 * This function count how many threads
 * were declared
 * */

int pthread_q_count()
{
    pthread_private_t *p;
    int count = 0;
    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;
        do
        {
            count++;
            p = p->next;
        } while (p != pthread_q_head);
    }
    return count;
}

/**
 * This function verify if the array has the number
 * rand
 * */

int pthread_q_array_verify(void *_array, int size_row, int size_columns, int rand)
{
    int(*array)[size_columns] = _array;
    for (int i = 0; i < size_row; i++)
    {
        for (int j = 0; j < size_columns; j++)
        {

            if (array[i][j] == rand)
            {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * This function fills an array 
 * with -1 in all positions
 * */

void pthread_q_array_fill(void *_array, int size_row, int size_columns)
{
    int(*array)[size_columns] = _array;
    for (int i = 0; i < size_row; i++)
    {
        for (int j = 0; j < size_columns; j++)
        {
            array[i][j] = -1;
        }
    }
}

/**
 * This function verify if the array is 
 * full
 * */

int pthread_q_array_isfull(void *_array, int size_row, int size_columns)
{
    int(*array)[size_columns] = _array;
    for (int i = 0; i < size_row; i++)
    {
        for (int j = 0; j < size_columns; j++)
        {

            if (array[i][j] == -1)
            {
                return 0;
            }
        }
    }

    return 1;
}

/**
 * This function prints an array
 * */

void pthread_q_print_array(void *_array, int size_row, int size_columns)
{
    int(*array)[size_columns] = _array;
    printf("[");
    for (int i = 0; i < size_row; i++)
    {
        printf("[");
        for (int j = 0; j < size_columns; j++)
        {
            if (j == 0)
            {
                printf("%d", array[i][j]);
            }
            else if (i == size_row - 1 && j == size_columns - 1)
            {
                printf(",%d", array[i][j]);
            }
            else
            {
                printf(",%d", array[i][j]);
            }
        }
        printf("]");
    }
    printf("]\n");
}

/**
 * This function appends only 1 number
 * in an array
 * */

void pthread_q_array_append(void *_array, int size_row, int size_columns, int number)
{
    int(*array)[size_columns] = _array;
    int append = FALSE;
    for (int i = 0; i < size_row; i++)
    {
        for (int j = 0; j < size_columns; j++)
        {

            if (array[i][j] == -1 && append == FALSE)
            {
                array[i][j] = number;
                append = TRUE;
            }
        }
    }
}

int pthread_q_array_simple_isfull(void *_array, int size)
{
    int(*array) = _array;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == -1)
        {
            return 0;
        }
    }
    return 1;
}

int pthread_q_array_simple_verify(void *_array, int size, int rand)
{
    int(*array) = _array;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == rand)
        {
            return 1;
        }
    }

    return 0;
}

void pthread_q_array_simple_fill(void *_array, int size)
{
    int(*array) = _array;
    for (int i = 0; i < size; i++)
    {
        array[i] = -1;
    }
}

void pthread_q_array_simple_append(void *_array, int size, int number)
{
    int(*array) = _array;
    int append = FALSE;

    for (int i = 0; i < size; i++)
    {
        if (append == FALSE && array[i] == -1)
        {
            append = TRUE;
            array[i] = number;
        }
    }
}

void pthread_q_print_array_simple(void *_array, int size)
{
    int(*array) = _array;
    printf("[");
    for (int i = 0; i < size; i++)
    {

        if (i == 0)
        {
            printf("%d", array[i]);
        }
        else if (i == size - 1)
        {
            printf(",%d", array[i]);
        }
        else
        {
            printf(",%d", array[i]);
        }
    }
    printf("]\n");
}

/**
 * This function gives the tickets to shcedulers
 * */

void pthread_q_choose_tickets(void *_array, int size_row, int size_columns, void *_tickets)
{
    int(*array)[size_columns] = _array;
    int random;
    int(*tickets) = _tickets;
    int full = 0;

    pthread_q_array_simple_fill(tickets, size_row);

    int flag;
    while (full != 1)
    {
        random = rand() % (size_row * 5);

        for (int i = 0; i < size_row; i++)
        {
            for (int j = 0; j < size_columns; j++)
            {

                if (array[i][j] == random)
                {
                    flag = !pthread_q_array_simple_verify(tickets, size_row, i);

                    if (flag == 1)
                    {
                        pthread_q_array_simple_append(tickets, size_row, i);

                        sleep(1);
                    }
                }
            }
        }
        full = pthread_q_array_simple_isfull(tickets, size_row);
    }
}

/**
 * This function have all the logic of 
 * the lottery scheduler
 * */

void pthread_q_lottery()
{
    int number_threads = pthread_q_count();
    int array[number_threads][5];

    int number_max = number_threads * 5;

    int full = 0;

    int rand_number;

    pthread_q_array_fill(array, 3, 5);

    while (full != 1)
    {
        rand_number = rand() % ((number_threads * 5));

        if (!pthread_q_array_verify(array, number_threads, 5, rand_number))
        {
            pthread_q_array_append(array, number_threads, 5, rand_number);
        }
        full = pthread_q_array_isfull(array, number_threads, 5);
    }
    pthread_q_print_array_simple(array, number_threads);

    int tickets[number_threads];
    pthread_q_choose_tickets(array, number_threads, 5, tickets);
    pthread_q_print_array_simple(array, number_threads);
    pthread_q_unlock_lottery(tickets, number_threads);
}

/**
 * Function that fills an array with all pids created
 * */
void pthread_q_queue_fill_pid(void *_array, int size)
{
    pthread_private_t *p;
    int i = 0;
    int(*array) = _array;
    if (pthread_q_head != NULL)
    {

        p = pthread_q_head;

        do
        {

            array[i] = p->tid;

            p = p->next;
            i++;

        } while ((i != size));
    }
}

/**
 * Function used for change the position
 * of the data in array moving one position
 * forward, like a circular shift
 * */

void pthread_q_swap_rr(void *_array, int size)
{
    int i = 0;
    int(*array) = _array;

    int temp_last = array[0];
    int temp;
    printf("%d\n", temp_last);
    for (i; i < size; i++)
    {
        if (i == size - 1)
        {
            array[i] = temp_last;
        }
        else
        {
            array[i] = array[i + 1];
        }
    }
}
/**
 * Function that has all the logic for 
 * Selfish Round Robin algorithm
 * */
void pthread_q_ssrr()
{
    int number_threads = pthread_q_count();
    int array_pids[number_threads];
    pthread_q_queue_fill_pid(array_pids, number_threads);
    pthread_q_print_array_simple(array_pids, number_threads);

    int number = 0;
    int i = 0;

    pthread_private_t *p;

    p = pthread_q_search(array_pids[number_threads - 1]);

    printf("STATE: %d, PID: %d\n", p->state, p->tid);

    while (p->state != DEFUNCT)
    {
        if (i == number_threads)
        {
            i = 0;
        }

        kill(array_pids[i], SIGCONT);

        sleep(1);

        kill(array_pids[i], SIGSTOP);

        printf("STATE: %d, PID: %d\n", p->state, p->tid);
        i++;
    }
}
