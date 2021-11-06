#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>

#define CHAIRS 6 
#define DELAY 100000000 // adjust this value
#define NUM 20


pthread_cond_t barber;
pthread_cond_t customers;
pthread_mutex_t lock;
int waiting = 0;
bool sleeping = false;
typedef struct cv 
{
	int threadsBlocked;
	sem_t semaphore;
	pthread_mutex_t lock;
}cv;

cv cond;

struct cv initCond()
{
	cv newCond;
	sem_init(&newCond.semaphore,0,CHAIRS);
	pthread_mutex_init(&newCond.lock,NULL);
	return newCond;
}

int count(cv c)
{
	return c.threadsBlocked;
}

void wait(cv c)
{
	pthread_mutex_lock(&c.lock);
	c.threadsBlocked++;
	pthread_mutex_unlock(&c.lock);
	sem_wait(&c.semaphore);
	return;
}

void signal(cv c)
{
	if(c.threadsBlocked>0)
	{
		c.threadsBlocked--;
	}
	sem_post(&c.semaphore);
	return;
}

void mon_debugPrint(bool isStylist)
{
	if(isStylist)
	{
		printf("Stylist Debug: %d customers in chair\n",waiting);
	}
	else
	{
		printf("Customer Debug: %d customers in chair\n",waiting);
	}
}

void mon_checkCustomer()
{
	if(waiting==0)
	{
		pthread_cond_wait(&barber,&lock);
	}
	--waiting;
	pthread_cond_signal(&customers);
}

bool mon_checkStylist()
{
	if(waiting<CHAIRS)
	{
		waiting++;
		pthread_cond_signal(&barber);
		pthread_cond_wait(&customers,&lock);
		return true;
	}
	else
	{
		return false;
	}
}

void stylist(void)
{
    while (1) 
    {
		mon_debugPrint(true);
		mon_checkCustomer() ;
		printf("Cutting hair\n");
		for(int k = 0; k < DELAY; k++); // cut hair
    }
}

void customer(void *id)
{
	int *i = (int *)id;
	while (1)
	{
		mon_debugPrint(false);
		if (mon_checkStylist())
			break;
		printf("Customer %d Shopping time\n",*i);
		for (int j = 0;j < DELAY; j++); // go shopping
	}
}

void main (void)
{
	pthread_cond_init(&barber,NULL);
	pthread_cond_init(&customers,NULL);
	pthread_mutex_init(&lock,NULL);
	//cond = initCond();
	pthread_t thread[NUM];
	for (int i = 0; i < NUM; i++) 
	{
		if (i == 0)
		{
			pthread_create(&thread[i], NULL, (void *) stylist, NULL);
		}
		else 
		{
			int * id = (int *)malloc(sizeof(int));
			*id = i;
			pthread_create(&thread[i], NULL, (void *) customer, (void *)id);
		}
	}
	
	for (int i = 0; i < NUM; i++) 
	{
		pthread_join(thread[i], NULL);
	}
}


