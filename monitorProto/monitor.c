//=====monitor.c=====//
#include <pthread.h>
#include <semaphore.h>

#define CHAIR 6
cond stylistAvailable, customerAvailable;
int customer = 0;
int stylist = 0;
//add more variables as necessary(e.g.a semaphore for entry queue)

void mon_CheckCustomer()
{
    stylist++;
    signal(stylistAvailable);//stylist is ready to cut hair
    if(customer == 0){//do not use while here
        wait(customerAvailable);
    }
    customer--;
}

int mon_CheckStylist()  //This function may have faults. If you think it does, you’ll need to fix it.
{
    int status = 0;
    if(customer < CHAIRS){
        customer++;
        signal(customerAvailable);
        if(stylist == 0){//do not use while here
            wait(stylistAvailable);
        }
        stylist--;
        status = 1;
    }
    returnstatus;
}

void mondebugPrint(void)//print how many customers are waiting
{
//print the state of the waiting chair using the following
//format(the following four lines are the sample output):
//
//|1|1|1|0|0|0|0|=>3
//Given haircuts = X
//Salon full = Y times
//Salon empty = Z times
//
//Below is the explanation of each line.
//
//Line1:For each slot, 0 indicates that the chair is
//available, and 1 indicates that the chair is occupied.
//
//The value after=>indicates the number of occupied
//chairs.
//
//Line2:X=number of completed haircuts.
//
//Line3:Y=the number of times that all waiting chairs are
//full.That is,each time the number of occupied
//chairs increases to 7,this counter should group by 7.
//
//Line4:Z=the number of times that the stylist goes to
//sleep.That is,each time the stylist goes to sleep,
//this counter should go up by1.
}
