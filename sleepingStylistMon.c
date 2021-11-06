#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>

#define CHAIRS 6 
#define DELAY 100000000 // adjust this value
#define NUM 20


//pthread_cond_t barber;
//pthread_cond_t customers;
pthread_mutex_t lock;
int waiting = 0;
sem_t entryQueue;
//int stylists = 0;
bool sleeping = false;

typedef struct cv 
{
	int waiting;
	sem_t semaphore;
}cv;

cv barber;
cv customers;

void initCond(cv * cond,int count)
{
	sem_init(&cond->semaphore,0,count);
}

int count(cv* c)
{
	return c->waiting;
}

void wait(cv* c)
{
	sem_wait(&c->semaphore);
	return;
}

void signal(cv* c)
{
	if(c->waiting>0)
	{
		c->waiting--;
	}
	sem_post(&c->semaphore);
	return;
}

void mon_debugPrint(bool isStylist)
{
	if(isStylist)
	{
		//printf("Stylist Debug: %d customers in chair\n",waiting);
	}
	else
	{
		//printf("Customer Debug: %d customers in chair\n",waiting);
	}
}

void mon_checkCustomer()
{
	sem_wait(&entryQueue);
	if(waiting==0)
	{
		printf("No customers going to sleep\n");
		//pthread_cond_wait(&barber,&lock);
		wait(&barber);
		printf("Woke up, cutting hair\n");
	}
	else
	{
		waiting--;
		printf("%d customers in shop\n",waiting);
		//pthread_cond_signal(&customers);
		signal(&customers);
		//sem_post(&entryQueue);
	}
	sem_post(&entryQueue);
	return;
}

bool mon_checkStylist(int id)
{
	sem_wait(&entryQueue);
	if(waiting<CHAIRS)
	{
		waiting++;
		//pthread_cond_signal(&barber);
		//signal(&barber);
		//pthread_cond_wait(&customers,&lock);
		wait(&customers);
		printf("Customer %d entering barber shop\n",id);
		printf("%d customers in shop\n",waiting);
		sem_post(&entryQueue);
		return true;
	}
	else
	{
		sem_post(&entryQueue);
		return false;
	}
}

void stylist(void)
{
    while (1) 
    {
		mon_debugPrint(true);
		mon_checkCustomer() ;
		for(int k = 0; k < DELAY; k++); // cut hair
		printf("Gave Haircut\n");
    }
}

void customer(void *id)
{
	int *i = (int *)id;
	while (1)
	{
		mon_debugPrint(false);
		if (mon_checkStylist(*i))
			break;
		printf("Customer %d gone shopping\n",*i);
		for (int j = 0;j < DELAY; j++); // go shopping
	}
}

void main (void)
{
	//pthread_cond_init(&barber,NULL);
	//pthread_cond_init(&customers,NULL);
	pthread_mutex_init(&lock,NULL);
	sem_init(&entryQueue,0,1);
	initCond(&barber,1);
	initCond(&customers,CHAIRS);
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
			int * id = (int *)malloc(sizeof(int));			//This leaks memory but going through the effort of fixing it is not worth the effort since this program only terminates via SIGINT
			*id = i;
			pthread_create(&thread[i], NULL, (void *) customer, (void *)id);
		}
	}
	
	for (int i = 0; i < NUM; i++) 
	{
		pthread_join(thread[i], NULL);
	}
	//Free memory here 
}


