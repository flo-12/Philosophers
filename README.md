# Philosophers
Welcome to a famous problem in Computer Science, formulated by Edsger Dijkstra in 1965, the **dining philosophers problem**. It is an introduction in concurrent programming.
The problem statement in our case goes as followed:
- One or more philosophers sit at a round table.
- The philosophers alternatively **eat**, **think**, or **sleep** (in that order!).
- There are as many forks (or chopsticks) on the table as philosophers.
- Each philosopher has to take their right and their left forks to eat.
- When a philosopher has finished eating, they put their forks back on the table, start sleeping and think after waking up.
- The simulation stops when a philosopher dies of starvation. And of course, philosophers should avoid dying.

Sadly, **philosophers don’t speak with each other** and don't know if an other philosopher is about to die. This information leads to the usage of **threads** and **mutexes**, which is the main goal of the project.

The program prompts a message each time a philosopher takes an action, which is formatted as followed:
```
[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died
```


## Learning goals
- understanding mechanisms that enforce limits on access to a resource when there are many threads of execution -> **mutexes**
- working with timestamps and time **synchronization** of threads
- getting used to **threads**
- and of course, structuting complex programs!


Allowed external functions / libraries:
- memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock


_As usual: All heap allocated memory space must be properly freed. No leaks will be tolerated._
_Additionally, data races have to be avoided._

# Usage
*Note that the program is written with Linux. Other operating systems were not tested.*

## Installing and Compiling
1) Clone the repository and its submodule by ``` git clone --recursive <project SSH/URL> ```
2) direct to the cloned folder ```cd <folder_name>```
3) ```make``` (automatically compiles the libft)


## Execution
Run the program with the following arguments:
```
./philo <number_of_philosophers> <time_to_die [ms]> <time_to_eat [ms]> <time_to_sleep [ms]> <[optional] number_of_times_each_philosopher_must_eat>
```


Examples:
* ```./philo 1 800 200 200``` -> the philosopher should not eat and should die
* ```./philo 5 800 200 200``` -> no one should die (end with CTRL+C)
* ```./philo 5 800 200 200 7``` -> no one should die and the simulation stops when all philosophers ate at least 7 times
* ```./philo 40 410 200 200``` -> no one should die (end with CTRL+C)
* ```./philo 40 310 200 200``` -> a philo should die

Note: The mutexes lead to a delay during execution. High numbers of philosophers (way above 200) can lead to unexpected deaths a philosophers.

## Check Data Races
In addition to the checks for memory leaks with ```valgrind``` possible data races had to be detected.
To check data races:

- compile with ```fsanitize=thread -g``` flag (the ```make SANITIZE``` rule includes this)
- execute the program with helgrind: ```valgrind --tool=helgrind ./philo <args>```
- execute the program with DRD: ```valgrind --tool=drd ./philo <args>```

_NOTE: using fsanitize and valgrind at the same time, can cause conflicts and unpredictable behaviour. Also valgrind slows the program down, which can cause earlier deaths of the philosophers._


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
