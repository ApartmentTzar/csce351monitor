/* // ==== s l e e p i n g S t y l i s t S e m . c ====// */
# define CHAIRS 6 
# define DELAY 1000000 // adjust this value

semaphore mutex = 1 , stylist = 0, customers = 0 ;
int waiting = 0 ;

void main( void )
{
  //create a specified number of customer threads
  // and a stylist thread. Don’t forget to join threads
}
void stylist ( void )
{
  int j ;
  while ( 1 ) {
    down(&customers);
    down(&mutex);
    waiting = waiting − 1;
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
      waiting = waiting + 1;
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
