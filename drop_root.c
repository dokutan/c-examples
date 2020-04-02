/*
 * Shows how to drop root privileges
 * 
 * gcc drop_root.c -o drop_root
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc, char *argv[] ){
	
	// print real and effective uid
	printf( "real uid: %d\n", getuid() );
	printf( "effective uid: %d\n", geteuid() );
	// print real and effective gid
	printf( "real gid: %d\n", getgid() );
	printf( "effective gid: %d\n", getegid() );
	
	printf( "\n" );
	
	// if root: drop root privileges 
	// important: set gid before uid
	if( getuid() == 0 )
	{
		printf( "attempting to drop root privileges\n" );
		
		if( setregid(1000, 1000) != 0 )
		{
			printf( "setgid failed\n" );
			return 1;
		}
		if( setreuid(1000, 1000) != 0 )
		{
			printf( "setuid failed\n" );
			return 1;
		}
	}
	else
	{
		printf( "don't have root privileges\n" );
	}
	
	printf( "\n" );
	
	// print real and effective uid
	printf( "real uid: %d\n", getuid() );
	printf( "effective uid: %d\n", geteuid() );
	// print real and effective gid
	printf( "real gid: %d\n", getgid() );
	printf( "effective gid: %d\n", getegid() );
	
	return 0;
}
