#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// int main()
// {


// 	pthread_mutex_t *ptr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
// 	pthread_mutex_init(ptr, NULL);
// 	pthread_mutex_lock(ptr);
// 	pthread_mutex_unlock(ptr);
// 	int res = pthread_mutex_unlock(ptr);
// 	printf("%d\n", res);
// 	pthread_mutex_destroy(ptr);
// 	free(ptr);
// 	return (0);
// }

// typedef struct s_test
// {
// 	int a;
// 	int *ptr;
// 	char c;
// } t_test;

// int main()
// {
// 	t_test test[5];
// 	memset(test, 0, sizeof(t_test) * 5);
// 	printf("%d\n", test[3].a);
// 	printf("%p\n", test[4].ptr);
// 	printf("%c\n", test[0].c);
// 	return (0);
// }

void *run()
{
	int i = 0;
	while (i < 5)
		i++;
	return (NULL);
}

int main()
{
	pthread_t t;
	pthread_create(&t, NULL, run, NULL);
	while (1)
		;

	return (0);
}