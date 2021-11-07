#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
/* // ==== s l e e p i n g S t y l i s t S e m . c ====// */
#define CHAIRS 6 
#define DELAY 1000000 // adjust this value
#define NUM 76

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
    printf("A new customer is being seen.\n%i customers waiting.\n", waiting);
    sem_post(&stylist);
    sem_post(&mutex) ;
    for ( j = 0 ; j < DELAY; j++ ); //cut hair
  }
}
void customer( void * id )
{
  int j ;
  int* threadId = (int *)id;
  while ( 1 ) {
    sem_wait(&mutex);
    printf("Customer %i checked in.\n", *threadId);
    if ( waiting < CHAIRS ) {
      waiting++;
      printf("%i customer(s) waiting.\n", waiting);
      sem_post(&customers);
      sem_post(&mutex);
      sem_wait(&stylist);
      break ;
    }
    else {
      printf("Customer %i went shopping.\n", *threadId);
      sem_post(&mutex);
      for ( j = 0 ; j < DELAY; j++ ); //go shopping
    }	
  }
  printf("Customer %i got a haircut.\n", *threadId);
}

void main( void )
{
  sem_init(&mutex, 0, 1);
  sem_init(&stylist, 0, 0);
  sem_init(&customers, 0, 0);
  pthread_t thread[NUM];
  for (int i = 0; i < NUM; i++) {
    if (i == 0) {
      pthread_create(&thread[i], NULL, (void *) style, NULL);
    }
    else {
      int * id = (int *)malloc(sizeof(int));
			*id = i;
			pthread_create(&thread[i], NULL, (void *) customer, (void *)id);
    }
  }
  for (int i = 0; i < NUM; i++) {
    pthread_join(thread[i], NULL);
  }
  // create a specified number of customer threads
  // and a stylist thread. Don’t forget to join threads
}

