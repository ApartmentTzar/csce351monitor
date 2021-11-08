#include "monitor.h"

void initCond(cv * cond,int count)
{
	sem_init(&cond->semaphore,0,count);
}

int count(cv* c)
{
	return c->waiting;
}

void wait(cv* c,sem_t * entryQueue)
{
    sem_post(entryQueue);
	c->waiting++;
	sem_wait(&c->semaphore);
	c->waiting--;
    sem_wait(entryQueue);
}

void signal(cv* c)
{
	sem_post(&c->semaphore);
}