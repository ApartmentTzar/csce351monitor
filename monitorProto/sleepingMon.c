//====sleepingStylistMon.c====//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include <monitor.h>

#define DELAY 1000000//adjust this value

void stylist(void)
{//add more variables as needed
    int j;
    while(1){
    mondebugPrint();
    moncheckCustomer();
    for(j =0; j < DELAY; j++);//cut hair
    }
}

void customer(void)
{//add more variables as needed
    int j;
    while(1){
    mondebugPrint();
    if(moncheckStylist())
        break;
    for(j = 0; j < DELAY; j++);//go shopping
    }
}

void main(void)
{
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
}
