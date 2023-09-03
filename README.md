# Philosophers


## Learning goals


# Usage
*Note that the program is written with Linux. Other operating systems were not tested.*

## Installing and Compiling
1) Clone the repository and its submodule by ``` git clone --recursive <project SSH/URL> ```
2) direct to the cloned folder ```cd <folder_name>```
3) ```make``` (automatically compiles the libft)


## Execution
The proram will take the _number of philosophers_, the _time to die [ms]_, the _time to eat [ms]_, the _time to sleep [ms]_ and the _number of times each philosopher must eat_ (optional) as an input:
* ```./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]```
Examples:
* ```./philo 1 800 200 200``` -> the philosopher should not eat and should die
* ```./philo 5 800 200 200``` -> no one should die (end with CTRL+C)
* ```./philo 5 800 200 200 7``` -> no one should die and the simulation stops when all philosophers ate at least 7 times
* ```./philo 40 410 200 200``` -> no one should die (end with CTRL+C)
* ```./philo 40 310 200 200``` -> a philo should die

Note: The mutexes lead to a delay during execution. High numbers of philosophers (way above 200) can lead to unexpected deaths a philosophers.

## Check Leaks


# Sources
The following list is a recommendation of sources for anyone who wants to know more about the topics:
| Topic								| Link                                                        	|
|----------------------------------:|:--------------------------------------------------------------|
| Intro Dining Philosophers Problem | [Wikipedia - Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) |
| Video Tutorial | [C program for dining philosophers problem using semaphore and mutex in operating system](https://www.youtube.com/watch?v=1LgFnXFpNMg) |
| Video Tutorial Threads | [Program to Pass Parameters to a Thread](https://www.youtube.com/watch?v=60NBJxX9n-M) |
| Intro about threads and mutexes | [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/) |
| man pages pthread_mutex_* | [pthread_mutex_init](https://linux.die.net/man/3/pthread_mutex_init), [pthread_mutex_lock](https://linux.die.net/man/3/pthread_mutex_lock), [pthread_mutex_unlock](https://linux.die.net/man/3/pthread_mutex_unlock) |
| man pages pthread_* | [pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [pthread_join](https://man7.org/linux/man-pages/man3/pthread_join.3.html), [pthread_detach](https://man7.org/linux/man-pages/man3/pthread_detach.3.html) |
