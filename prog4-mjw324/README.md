# prog4: Processes and Signals

## Learning Outcomes:

- Use process control functions to create and reap processes
- Define a signal handler using the guidelines for writing safe signal handlers
- Use signals to communicate between processes

## Specification

Write a program that prints the sum of the elements in an array. The program distributes the task of adding N elements of an array to a number of processes (P) including itself. Each process will determine a partial sum of N/P elements. Then, each child process sends a signal (SIGUSR2), that includes the partial sum, to the parent process.  The parent process will determine its own partial sum, reap all the child processes, and print the final sum before terminating.

Write the program described above and install a handler for the signal SIGUSR2. 

The handler should collect the partial sum sent by the child process with the signal and add it to the final sum (global variable shared between the handler and the parent process).

The handler should be written following the guidelines for writing safe signal handlers covered in class and listed below. You must justify how you implemented each guideline, if applicable.

- Keep handlers as simple as possible
- Call only safe or async-signal-safe functions in the handler
- Protect access to shared global data structures by blocking all signals
- Declare global variables with prefix volatile
- Declare flags with sig_atomic_t

All system calls should be performed using wrapper functions to handle errors as prototyped in the source file `prog4.c` (Fork, Wait, Waitpid, Signal, Sigqueue, Sigprocmask, Sigaction, Sigemptyset, Sigfillset, Read, and Write).

Use the system call `sigqueue` instead of `kill` to send a signal. The function `sigqueue` should be used as described below:

```
union sigval value; // sigval union

value.sival_int = val; /* set the field sival_int to the integer value you want to send with the signal*/ 

Sigqueue(pid, SIGUSR2, value);/*send SIGUSR2 to the process pid with the integer stored in value*/
```


The handler collects the info delivered by `sigqueue` as shown below (Note the signature of the handler):

```
void sigusr2_handler(int sig, siginfo_t *value, void *ucontext){

/* this is how you get the value sent in the siginfo_t structure */

   int psum = value->si_value.sival_int;
   
   ...
   
}
```


You are given a startup code in the file `prog4.c`.  

P (the number of processes) is defined at compile time as a macro with value 4 or 8 respectively. 

The program should distribute the task of adding 4096 elements on 4/8 processes (3/7 children and one parent). 

The program you will write must generate the exact output listed below for 4 processes. Only the order of the output messages and the numbers (pids and index ranges) may differ. 

```
Parent process 860123 installing SIGUSR2 handler

Parent process 860123 adding the elements from index 3072 to 4095

Child process 860125 adding the elements from index 0 to 1023

Child process 860125 sending SIGUSR2 to parent process with the partial sum 524800

Child process 860126 adding the elements from index 1024 to 2047

Child process 860126 sending SIGUSR2 to parent process with the partial sum 1573376

Child process 860127 adding the elements from index 2048 to 3071

Parent process caught SIGUSR2 with partial sum: 524800

Child process 860127 sending SIGUSR2 to parent process with the partial sum 2621952

Parent process caught SIGUSR2 with partial sum: 1573376

Parent process caught SIGUSR2 with partial sum: 2621952

Child process 860125 terminated normally with exit status 0

Child process 860126 terminated normally with exit status 0

Child process 860127 terminated normally with exit status 0

Final sum = 8390656
```


In addition to `prog4.c`, you are provided with the following script files to test your code:

`test.sh`: A bash script to compile `prog4.c`, run it and redirect the program output to a file named `output`. The script also runs the Perl script file `checkOutput.pl` to test the output file.

`checkOutput.pl`: A Perl script to compare the contents of the file `output` to the reference output. This script will display a score as shown below if your program runs correctly:

- one installing handler output message
- 3 or 7 sending signal output messages
- 3 or 7 caught signal output messages
- 3 or 7 child adding output messages
- 3 or 7 child processes terminated normally
- 0 child process terminated abnormally
- 1 parent adding output message
- 1 output message for the final sum 

Running the script with the command: `./checkOutput.pl output 3` should have the following output:

```
installing = 1
sending    = 3
caught     = 3
normally   = 3
abnormally = 0
parent adding = 1
child adding = 3
final sum = 1
---------------
Score  = 90/90
```
