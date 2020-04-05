/*
 * Various tests with standard i/o
 * 
 * gcc iotest.c -o iotest
 * 
 * ./iotest
 * ./iotest | tee
 * yes | ./iotest
 */
 
#include <stdio.h> /* for fileno() */
#include <unistd.h> /* for isatty(), ttyname() */
#include <errno.h>

int main( int argc, char *argv[] )
{
	
	/* print the file descriptors of stdio, stderr, stdin */
	printf( "file descriptor of stdin:\t%d\n", fileno(stdin) );
	printf( "file descriptor of stdout:\t%d\n", fileno(stdout) );
	printf( "file descriptor of stderr:\t%d\n", fileno(stderr) );
	printf( "\n" );
	
	/* does stdout refer to a terminal ? */
	if( isatty( fileno(stdout) ) )
		printf( "stdout refers to a terminal\n" );
	else if( errno == ENOTTY ) /* fd valid, but not a terminal */
		printf( "stdout does not refer to a terminal\n" );
	printf( "\n" );
	
	/* print terminal name */
	char *name =  ttyname( fileno(stdin) );
	if( name != NULL )
		printf( "stdin is open on terminal:\t%s\n", name );
	
	name =  ttyname( fileno(stdout) );
	if( name != NULL )
		printf( "stdout is open on terminal:\t%s\n", name );
	
	name =  ttyname( fileno(stderr) );
	if( name != NULL )
		printf( "stderr is open on terminal:\t%s\n", name );
	
	return 0;
}
