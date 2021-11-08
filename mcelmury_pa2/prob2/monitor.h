#ifndef MONITOR_H_   /* Include guard */
#define MONITOR_H_
#include <semaphore.h>
#include <pthread.h>

typedef struct cv 
{
	int waiting;
	sem_t semaphore;
}cv;

void initCond(cv * cond,int count);

int count(cv* c);

void wait(cv* c,sem_t * entryQueue);

void signal(cv* c);

#endif // MONITOR_H_
