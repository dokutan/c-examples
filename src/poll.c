/*
 * Shows how to poll a file descriptor
 * 
 * gcc poll.c -o poll
 */
 
#include <stdio.h>
#include <errno.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
	
	/* filename provided ? */
	if( argc < 2 ){
		printf( "Filename expected as argument\n" );
		return 1;
	}
	
	/* open file */
	int fd = open( argv[1], O_RDWR );
	if( fd == -1 ) /* error */
	{
		printf( "Error: %s\n", strerror( errno ) );
		return 1;
	}
	
	/* describes which files to poll for what */
	struct pollfd fds[1];
	fds[0].fd = fd; /* file descriptor */
	fds[0].events = POLLIN; /* events to poll for */
	
	int result = poll( fds, 1, -1 ); /* fds, num of elements in fds, timeout */
	if( result == -1 )
	{
		printf( "Error: %s\n", strerror( errno ) );
		close( fd );
		return 1;
	}
	else if( result == 0 )
	{
		printf( "poll timed out\n" );
	}
	else
	{
		printf( "poll returned\n" );
		/* check fds[0].revents for returned events */ 
	}
	
	/* close file descriptor */
	close( fd );
	
	return 0;
}
