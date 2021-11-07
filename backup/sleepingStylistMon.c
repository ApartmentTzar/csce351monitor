#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>

#define CHAIRS 6 
#define DELAY 100000000 // adjust this value
#define NUM 76

sem_t entryQueue;
int stylists = 0;
int customers = 0;

int haircutsGiven = 0;
int timesFull = 0;
int timesEmpty = 0;

cv stylistAvailable;
cv customerAvailable;

void stylist(void)
{
    while (1) 
    {
		mon_debugPrint();
		mon_checkCustomer() ;
		for(int k = 0; k < DELAY; k++); // cut hair
		printf("Gave Haircut\n");
        haircutsGiven++;
    }
}

void customer(void *id)
{
	int *i = (int *)id;
	while (1)
	{
		mon_debugPrint();
		if (mon_checkStylist(*i))
			break;
		printf("Customer %d gone shopping\n",*i);
		for (int j = 0;j < DELAY; j++); // go shopping
	}
}

void main (void)
{

	sem_init(&entryQueue,0,1);
	initCond(&stylistAvailable,1);
	initCond(&customerAvailable,0);

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