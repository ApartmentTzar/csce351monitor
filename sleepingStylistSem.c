#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
/* // ==== s l e e p i n g S t y l i s t S e m . c ====// */
# define CHAIRS 6 
# define DELAY 1000000 // adjust this value
# define NUM 76

sem_t mutex;
sem_t stylist;
sem_t customers;

// customers is waiting line, stylist is their availability, mutex is to get into queue
int waiting = 0 ;

void style ( void )
{
  int j ;
  while ( 1 ) {
    sem_wait(&customers);
    sem_wait(&mutex);
    waiting--;
    printf("A new customer is being seen.")
    sem_post(&stylist);
    sem_post(&mutex) ;
    for ( j = 0 ; j < DELAY; j++ ); //cut hair
  }
}
void customer( void )
{
  int j ;
  while ( 1 ) {
    sem_wait(&mutex) ;
    if ( waiting < CHAIRS ) {
      waiting++;
      printf("Customer %i is now waiting.");
      sem_post(&customers);
      sem_post(&mutex);
      sem_wait(&stylist);
      break ;
    }
    else {
      sem_post(&mutex);
      for ( j = 0 ; j < DELAY; j++ ); //go shopping
    }	
  }
  printf("Thread %i got a haircut.\n",);
}

void main( void )
{
  sem_init(&mutex, 0, 1);
  sem_init(&stylist, 0, 1);
  sem_init(&customers, 0, 1);
  pthread_t thread[NUM];
  for (int i = 0; i < NUM; i++) {
    if (i == 0) {
      pthread_create(&thread[i], NULL, (void *) style, NULL);
    }
    else {
      pthread_create(&thread[i], NULL, (void *) customer, NULL);
    }
  }
  for (int i = 0; i < NUM; i++) {
    pthread_join(thread[i], NULL);
  }
  // create a specified number of customer threads
  // and a stylist thread. Don’t forget to join threads
}

