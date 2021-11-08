#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "monitor.h"

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

void mon_debugPrint()
{
	sem_wait(&entryQueue);
	printf("\n|");
	for(int k = 1; k <= CHAIRS; k++){
    	if(k <= count(&stylistAvailable)){
			printf("1|");
		}
		else {printf("0|");}
	}
	printf(" => %i\n", count(&stylistAvailable));
	printf("Given haircuts     = %i\n",haircutsGiven);
    printf("Salon full         = %i times\n",timesFull);
    printf("Salon empty        = %i times\n",timesEmpty);
	printf("\n");
	sem_post(&entryQueue);
}

void mon_checkCustomer()
{
    sem_wait(&entryQueue);
	stylists = stylists + 1;
    signal(&stylistAvailable);
    if(count(&stylistAvailable) <= 0)
    {
        printf("No customers going to sleep\n");
        timesEmpty++;
        wait(&customerAvailable,&entryQueue);
    	printf("Woke up, cutting hair\n");

    }
    customers=customers - 1;
    sem_post(&entryQueue);
}

bool mon_checkStylist(int id)
{
    sem_wait(&entryQueue);
	bool status = false;
    if(count(&stylistAvailable) < CHAIRS)
    {
        customers = customers + 1;
        if(count(&stylistAvailable)==CHAIRS-1)
        {
            timesFull++;
        }
        printf("Customer %d entering barber shop\n",id);
		if(count(&customerAvailable)>0)
		{
			signal(&customerAvailable);
		}
        wait(&stylistAvailable,&entryQueue);
		if(stylists > 0)
		{
        	stylists = stylists - 1;
        	status = true;
		}
    }
    sem_post(&entryQueue);
    return status;
}

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


