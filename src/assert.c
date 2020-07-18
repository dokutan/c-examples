/*
 * Shows how to use assert() and static_assert()
 * 
 * gcc assert.c -o assert
 */

/* If this macro is defined before assert is included,
 * all assert() statements will be skipped.
 */ 
// #define NDEBUG

#include <assert.h>
// <cassert> for C++

int main( int argc, char *argv[] )
{
	// The following two statements will be evaluated at runtime
	// This assert statement should not produce an error
	assert(1);
	// This assert statement should produce an error and exit the program
	assert(0);
	
	// The following statements will evaluated at compiletime
	// This static_assert statement should not produce an error
	static_assert(1);
	// This static_assert statement would produce an error during compilation
	// static_assert(0);
	
	return 0;
}
