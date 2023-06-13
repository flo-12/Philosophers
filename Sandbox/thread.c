
// cc thread.c -lpthread

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

int	counter;

void	*myThread(void *arg)
{
	/*int	*myid;

	usleep(100);
	myid = (int *)arg;
	printf("In Thread %d\n", *myid);*/

	pthread_mutex_t	*lock;

	lock = arg;
	pthread_mutex_lock(lock);

	unsigned long	i = 0;
	
	counter += 1;
	printf("\n Job %d has started\n", counter);
	while (i < (0x0FFFFFFF))
		i++;
	printf("\n Job %d has finished\n", counter);
	
	pthread_mutex_unlock(lock);

	return (NULL);
}

int	main()
{
	int				n_thread = 5;
	pthread_mutex_t	lock;
	pthread_t		tid[n_thread];
	int				i = -1;

	pthread_mutex_init(&lock, NULL);
	printf("Before Threads\n");
	while (++i < n_thread)
		pthread_create(&(tid[i]), NULL, myThread, (void *)&lock);
		//pthread_join(tid[i], NULL);
	i = -1;
	while (++i < n_thread)
		pthread_join(tid[i], NULL);
	pthread_mutex_destroy(&lock);
	printf("After Threads\n");
	return (0);
}

