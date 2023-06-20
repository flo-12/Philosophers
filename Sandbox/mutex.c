
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

/* void	*thread1(void *arg)
{
	printf("[T1] 1\n");
	usleep(250);
	printf("[T1] 2\n");
	usleep(250);
	printf("[T1] 3\n");
	usleep(250);
	printf("[T1] 4\n");
	return (NULL);
}

void	*thread2(void *arg)
{
	printf("[T2] 1\n");
	usleep(550);
	printf("[T2] 2\n");
	return (NULL);
}
 */
int	main()
{
	pthread_mutex_t		mute1;
	pthread_mutex_t		mute2;

	printf("Initialize Mutex 1\n");
	pthread_mutex_init(&mute1, NULL);
	printf("Destroy unlocked Mutex\n");
	pthread_mutex_destroy(&mute1);
	printf("Re-Initialize and lock Mutex 1\n");
	pthread_mutex_init(&mute1, NULL);
	pthread_mutex_lock(&mute1);
	printf("Destroy locked Mutex\n");
	pthread_mutex_destroy(&mute1);
	
	printf("Destroy un-initialized Mutex 2\n");
	pthread_mutex_destroy(&mute2);
	printf("Done\n");
	return (0);
}
