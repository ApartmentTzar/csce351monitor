 //==== s l e e p i n g S t y l i s t M o n . c ====//
# define DELAY 1000000
void main (void)
{
// c r e a t e a s p e c i f i e d number o f c u st o m e r t h r e a d s
// and a s t y l i s t t h r e a d . Don ’ t f o r g e t t o j o i n t h r e a d s
}

void stylist (void)
{
    int j ;
    while (1) 
    {
		mondebugPrint ( ) ;
		moncheckCustomer ( ) ;
		for(j = 0; j < DELAY; j++); // c u t h a i r
    }
}

void customer(void)
{
	int j ;
	while ( 1 )
	{
		mondebugPrint ( ) ;
		if ( moncheckStylist ( ) )
			break ;
		for (j = 0;j < DELAY; j++); // go s h o p pi n g
	}
}
