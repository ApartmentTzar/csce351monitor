#ifndef MONITOR
#define 
#include <semaphore.c>

struct cond{
    int blockedThreads;
    sem_t cvSem;
}

void mon_checkCustomer();

int mon_checkStylist();

void mon_debugPrint();

#endif