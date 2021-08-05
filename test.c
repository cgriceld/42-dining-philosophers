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

static int ret1()
{
	printf("from 1\n");
	return (0);
}

static int ret2()
{
	printf("from 2\n");
	return (0);
}

static int ret3()
{
	printf("from 3\n");
	return (1);
}

static int ret()
{
	return (ret1() || ret2() || ret3());
}

int main()
{
	printf("%d\n", ret());
	return (0);
}