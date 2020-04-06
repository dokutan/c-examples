/*
 * Get keyboard indicator state with Xlib
 * 
 * Requires Xlib (libx11) to be installed, (and obviously a running X server).
 * 
 * gcc X-keyboard-indicator.c -o X-keyboard-indicator -lX11
 * 
 * Further information on Xlib:
 * https://www.x.org/releases/current/doc/libX11/libX11/libX11.html
 * https://www.x.org/releases/current/doc/libX11/XKB/xkblib.html
 */
 
#include <stdio.h>
#include <X11/XKBlib.h>

int main( int argc, char *argv[] ){
	
	/* open X display */
	Display *display = XOpenDisplay( NULL ); /* get display from DISPLAY environmental variable */
	if( display == NULL ){
		printf( "Error: Couldn't open X display\n" );
		return 1;
	}
	
	/* get keyboard indicator state with XkbGetIndicatorState() */
	unsigned int state; /* indicator state */  
	Status status; /* return value of the function */
	status = XkbGetIndicatorState( display, XkbUseCoreKbd, &state );
	
	/* print indicator state if successful */
	if( status == Success ){
		printf( "XkbGetIndicatorState:\t%d\n", state );
	} else if( status == BadMatch ){
		printf( "Error: Xkb is not availabe\n" );
	} else {
		printf( "Error: XkbGetIndicatorState failed\n" );
	}
	
	/* close X display */
	XCloseDisplay( display );
	
	return 0;
}
