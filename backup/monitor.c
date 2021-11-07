#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <monitor.h>
#include <string.h>
#include <stdbool.h>

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
    sem_post(&entryQueue);
	c->waiting++;
	sem_wait(&c->semaphore);
	c->waiting--;
    sem_wait(&entryQueue);
}

void signal(cv* c)
{
	sem_post(&c->semaphore);
}

void mon_debugPrint()
{
	sem_wait(&entryQueue);
	printf("\n");
    printf("Customers in Salon = %d\n",count(&stylistAvailable));
    printf("Given haircuts     = %d\n",haircutsGiven);
    printf("Salon full         = %d\n",timesFull);
    printf("Salon empty        = %d\n",timesEmpty);
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
        wait(&customerAvailable);
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
        wait(&stylistAvailable);
		if(stylists > 0)
		{
        	stylists = stylists - 1;
        	status = true;
		}
    }
    sem_post(&entryQueue);
    return status;
}