/*
 * Print a list of all defined meanings of errno.
 * 
 * gcc list-errno.c -o list-errno
 */
 
#include <stdio.h>
#include <string.h> /* for strerror() and strerror_r() */

int main( int argc, char *argv[] )
{
	
	for( int i = 0; ; i++ )
	{
		
		char buf[1024]; /* buffer to hold the message */
		
		/* call strerror_r() to get the message */
		if( strerror_r( i, buf, sizeof(buf) ) != 0 )
			break;
		
		/* print the message */
		printf( "%d\t%s\n", i, buf );
		
		/*
		 * This would also print the error message,
		 * however in this context this makes it difficult to determine
		 * when to break out of this loop
		 * 
		 * printf( "%d\t%s\n", i, strerror( i ) );
		 */
		
	}

	return 0;
}
