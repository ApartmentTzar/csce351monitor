#ifndef
#define
#include <semaphore.h>

struct cv
{
    int waiting;
    sem_t semaphore;
}

void initCond(cv*, int);
int count(cv*);
void wait(cv*);
void signal(cv*);
void mon_debugPrint();
void mon_checkCustomer();
bool mon_checkStylist(int);

#endif