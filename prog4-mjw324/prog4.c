/*
 *  CSE202: Processes and Signals
 *  Full name: Micah Worth
 *  Full Lehigh Email Address: mjw324@lehigh.edu
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

// Array size
#define N 4096

/* Global variable shared between the main process and the signal handler */
int volatile sum = 0;

/* function to initialize an array of integers */
void initialize(int *);
/* Wrapper functions for all system calls */
void unix_error(const char *msg);
pid_t Fork();
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *status, int options);
int Sigqueue(pid_t pid, int signum, union sigval value);
int Sigemptyset(sigset_t *set);
int Sigfillset(sigset_t *set);
int Sigaddset(sigset_t *set, int signum);
int Sigaction(int signum, const struct sigaction *new_act, struct sigaction *old_act);
int Sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
ssize_t Write(int d, const void *buffer, size_t nbytes);
ssize_t Read(int d, void *buffer, size_t nbytes);
typedef void handler_t;
handler_t *Signal(int signum, handler_t *handler);
void sigusr2_handler(int sig, siginfo_t *value, void *ucontext);

/* main function */
int main()
{
    int i;
    int j;
    // Declaring and initializing array of integers of size N (default 4096)
    int A[N];
    initialize(A);

    // There will be P processes (4 or 8)
    pid_t pid[P];
    
    /* install the SIGUSR2 handler using Signal (portable handler) */
    pid[0] = getpid(); // Get the process ID of the parent process
    char out[128];
    sprintf(out, "Parent process %d installing SIGUSR2 handler\n", pid[0]);
    fflush(stdout); // Flush any buffered data before writing
    Write(1, out, strlen(out)); // Write the message to stdout
    Signal(SIGUSR2, sigusr2_handler); // Install the SIGUSR2 signal handler
    int range = N / P; // Calculate the range of indices each process will handle
    
    /* Create child processes and perform calculations */
    for (i = 1; i < P; i++) {  
        if ((pid[i] = Fork()) == 0) // Create a child process using Fork()
        {
            /* child process */
            int start = i * range; // start index for child process number i
            int end = start + range; // end index for child process number i
            int partial_sum = 0;
            pid[i] = getpid(); // Get the process ID of the child process
            printf("Child process %d adding the elements from index %d to %d\n", pid[i], start, end - 1);
            // Calculate partial sum for child process number i
            for (j = start; j < end; j++)
            {
                partial_sum += A[j];
            }

            printf("Child process %d sending SIGUSR2 to parent process with the partial sum %d\n", pid[i], partial_sum);

            union sigval value;
            value.sival_int = partial_sum;
            sleep(i);
            // Sending a SIGUSR2 signal with the partial sum back to the parent process
            Sigqueue(pid[0], SIGUSR2, value);
            exit(0);
        }
    }

    /* parent process */
    int parent_start = 0;
    int parent_end = range;
    int parent_partial_sum = 0;

    printf("Parent process %d adding the elements from index %d to %d\n", getpid(), parent_start, parent_end - 1);
    
    // Calculate partial sum for parent process
    for (j = parent_start; j < parent_end; j++)
    {
        parent_partial_sum += A[j];
    }

    /* Block SIGUSR2 while updating the shared sum */
    sigset_t mask, prev_mask;
    // init empty mask
    Sigemptyset(&mask);
    // adds sigusr2 to signal set
    Sigaddset(&mask, SIGUSR2);
    // blocks sigusr2 signal
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask);
    // updates shared sum
    sum += parent_partial_sum;
    // unbloks sigusr2 signal
    Sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    int status;
    for (i = 1; i < P; i++)
    {
        // Parent waits for all children to process before terminating
        pid_t child_pid = Waitpid(-1, &status, 0);
        if(WIFEXITED(status))
            printf("Child process %d terminated normally with exit status %d\n", child_pid, WEXITSTATUS(status));
        else
            printf("Child process %d terminated abnormally\n", child_pid);

    }

    printf("Final sum = %d\n", sum);
    exit(0);
}

/* SIGUSR2 signal handler function */
void sigusr2_handler(int sig, siginfo_t *value, void *ucontext)
{
    int olderrno = errno; // Store the current errno value to restore later

    // Extract the partial sum sent by the child process using the siginfo_t structure
    int psum = value->si_value.sival_int;

    /* Block SIGUSR2 while updating the shared sum */
    sigset_t mask, prev_mask;
    Sigemptyset(&mask); // Initialize an empty signal set
    Sigaddset(&mask, SIGUSR2); // Add SIGUSR2 to the signal set
    Sigprocmask(SIG_BLOCK, &mask, &prev_mask); // Block SIGUSR2 signals

    sum += psum; // Update the shared sum with the received partial sum

    Sigprocmask(SIG_SETMASK, &prev_mask, NULL); // Unblock SIGUSR2 signals

    // Prepare a message to print the received partial sum
    char out[128];
    sprintf(out, "Parent process caught SIGUSR2 with partial sum: %d\n", psum);
    fflush(stdout); // Flush any buffered data before writing
    Write(1, out, strlen(out)); // Write the message to stdout

    errno = olderrno; // Restore the original errno value
}

/* Initializes array of size N, each value in the array is its index+1 */
void initialize(int M[N])
{
    int i;
    for (i = 0; i < N; i++)
    {
        M[i] = i + 1;
    }
}

/* Definition of the wrapper system call functions */

/* These functions just wrap the system calls, and catch unexpected behavior with unix_error */


void unix_error(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        unix_error("Fork error");
    }

    return pid;
}

pid_t Wait(int *status)
{
    pid_t pid;

    if ((pid = wait(status)) < 0)
    {
        unix_error("Wait error");
    }

    return pid;
}

pid_t Waitpid(pid_t pid, int *status, int options)
{
    pid_t ret_pid;

    if ((ret_pid = waitpid(pid, status, options)) < 0)
    {
        unix_error("Waitpid error");
    }

    return ret_pid;
}

int Sigqueue(pid_t pid, int signum, union sigval value)
{
    int result;

    if ((result = sigqueue(pid, signum, value)) < 0)
    {
        unix_error("Sigqueue error");
    }

    return result;
}

int Sigemptyset(sigset_t *set)
{
    int result;

    if ((result = sigemptyset(set)) < 0)
    {
        unix_error("Sigemptyset error");
    }

    return result;
}

int Sigfillset(sigset_t *set)
{
    int result;

    if ((result = sigfillset(set)) < 0)
    {
        unix_error("Sigfillset error");
    }

    return result;
}

int Sigaction(int signum, const struct sigaction *new_act, struct sigaction *old_act)
{
    int result;

    if ((result = sigaction(signum, new_act, old_act)) < 0)
    {
        unix_error("Sigaction error");
    }

    return result;
}

int Sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
    int result;

    if ((result = sigprocmask(how, set, oldset)) < 0)
    {
        unix_error("Sigprocmask error");
    }

    return result;
}

int Sigaddset(sigset_t *set, int signum)
{
    int result;

    if ((result = sigaddset(set, signum)) < 0)
    {
        unix_error("Sigaddset error");
    }

    return result;
}

ssize_t Write(int d, const void *buffer, size_t nbytes)
{
    ssize_t result;

    if ((result = write(d, buffer, nbytes)) < 0)
    {
        unix_error("Write error");
    }

    return result;
}

ssize_t Read(int d, void *buffer, size_t nbytes)
{
    ssize_t result;

    if ((result = read(d, buffer, nbytes)) < 0)
    {
        unix_error("Read error");
    }

    return result;
}

handler_t *Signal(int signum, handler_t *handler)
{
    struct sigaction action, old_action;
    action.sa_handler = handler;
    Sigemptyset(&action.sa_mask); /* blocks sigs of the type being handled  */
    action.sa_flags = SA_RESTART | SA_SIGINFO; /* restart syscalls if possible */
    Sigaction(signum, &action, &old_action);
    return (old_action.sa_handler); 
}