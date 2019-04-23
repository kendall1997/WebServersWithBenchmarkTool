#define _GNU_SOURCE
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

// 64kB stack
#define FIBER_STACK 1024 * 64

// The child thread will execute this function
int threadFunction(void *argument)
{
    printf("child thread exiting %d\n", (int *)argument);
    return 0;
}

int main()
{
    void *stack;
    pid_t pid;
    int *str = 4;

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0)
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    printf("Creating child thread\n");

    // Call the clone system call to create the child thread
    pid = clone(&threadFunction, (char *)stack + FIBER_STACK,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, str);
    if (pid == -1)
    {
        perror("clone");
        exit(2);
    }

    // Wait for the child thread to exit

    // Free the stack
    free(stack);

    printf("Child thread returned and stack freed.\n");

    return 0;
}
