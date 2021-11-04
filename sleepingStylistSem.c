#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
/* // ==== s l e e p i n g S t y l i s t S e m . c ====// */
# define CHAIRS 6 
# define DELAY 1000000 // adjust this value
# define NUM 76

semaphore mutex = 1 , stylist = 0, customers = 0 ;
// customers is waiting line, stylist is their availability, mutex is to get into queue
int waiting = 0 ;

void main( void )
{
  pthread_t thread[NUM];
  for (i = 0; i < NUM; i++) {
		if (i == 0) {
			pthread_create(&thread[i], NULL, (void *) stylist, NULL);
    }
		else {
			pthread_create(&thread[i], NULL, (void *) customer, NULL);
	  }
  for (i = 0; i < NUM; i++) {
		pthread_join(thread[i], NULL);
  }
  // create a specified number of customer threads
  // and a stylist thread. Don’t forget to join threads
}
void stylist ( void )
{
  int j ;
  while ( 1 ) {
    down(&customers);
    down(&mutex);
    waiting--;
    up(&stylist);
    up(&mutex ) ;
    for ( j = 0 ; j < DELAY; j + + ); //cut hair
					      }
}
void customer( void )
{
  int j ;
  while ( 1 ) {
    down(&mutex ) ;
    if ( waiting < CHAIRS ) {
      waiting++;
      up(&customers);
      up(&mutex);
      down(&stylist);
      break ;
    }
    else {
      up(&mutex );
      for ( j = 0 ; j < DELAY; j + + ); //go shopping
		}
  }
}
