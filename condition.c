/*
 * =====================================================================================
 *
 *       Filename:  condition.c
 *
 *    Description:  This program is demostrate to how to use conditon var
 *
 *        Version:  1.0
 *        Created:  2011年04月05日 21时26分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liang Gang 
 *        Company:  Schuan University
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void* thread1(void*);
void* thread2(void*);

int i=1;

int main(void)
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1,NULL,(void*)thread1,NULL);
	pthread_create(&t2,NULL,(void*)thread2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	exit(0);

}

void* thread1(void* arg)
{
	for(i=1;i<=9;i++)
	{
		pthread_mutex_lock(&mutex);
		
		if (i%3==0)
			pthread_cond_signal(&cond);
		else
			printf("thread1:%d\n",i);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

}

void* thread2(void* arg)
{
	while(i<=9)
	{
		pthread_mutex_lock(&mutex);

		if (i%3!=0)
			pthread_cond_wait(&cond,&mutex);
		
		printf("thread2:%d\n",i);

		pthread_mutex_unlock(&mutex);
		sleep(1);
	
	}
}

