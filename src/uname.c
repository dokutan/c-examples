/*
 * Print information about the system.
 * 
 * gcc uname.c -o uname
 */
 
#include <stdio.h>
#include <sys/utsname.h>

int main( int argc, char *argv[] ){
	
	struct utsname info; /* this struct holds the information */
	int res = uname( &info ); /* call uname() to fill the struct */
	
	/* print return value of uname() */
	printf( "uname() returned:\t%d\n", res );
	
	/* error handling, errno is set by uname() */
	if( res != 0 ){
		printf( "uname returned an error, quitting\n" );
		return 1;
	}
	
	/* print results */
	printf( "sysname:\t%s\n", info.sysname );
	printf( "nodename:\t%s\n", info.nodename );
	printf( "release:\t%s\n", info.release );
	printf( "version:\t%s\n", info.version );
	printf( "machine:\t%s\n", info.machine );
	
	return 0;
}
