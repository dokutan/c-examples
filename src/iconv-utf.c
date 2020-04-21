/*
 * Shows how to convert a utf-8 string to utf-32 with iconv
 * The utf-8 string is specified on the commandline and the number of
 * bytes and the individual codepoints will be shown.
 * 
 * gcc iconv-utf.c -o iconv-utf
 */
 
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iconv.h>

int main( int argc, char *argv[] )
{
	/* check arguments */
	if( argc < 2 )
	{
		printf( "Usage: iconv-utf someUTF8string\n" );
		return 0;
	}
	
	iconv_t cd; /* conversion descriptor */
	cd = iconv_open( "UTF-32BE", "UTF-8" ); /* open conversion descriptor */
	
	if( cd == (iconv_t)-1 ) /* if iconv_open failed */
	{
		perror( "iconv_open failed" );
		return 1;
	}
	
	/* UTF-8 input string */
	char *utf8_str = argv[1];
	printf( "UTF-8 string (%d bytes): %s\n", strlen( utf8_str ), utf8_str );
	
	/* UTF-32 output string */
	char utf32_str[ 4*sizeof(utf8_str) ]; /* this guarantees that the string is big enough */
	char *out = utf32_str;
	
	/* number of bytes in the input and output strings */
	size_t inbytes = strlen( utf8_str ), outbytes = sizeof( utf32_str );
	
	/* do the conversion */
	size_t result = iconv( cd, &utf8_str, &inbytes, &out, &outbytes );
	
	if( result == (size_t)-1 ) /* if iconv failed */
	{
		perror( "iconv failed" );
	}
	
	/* clean up utf32_str, \0 needs to be added at the end */
	utf32_str[ sizeof( utf32_str ) - outbytes ] = '\0';
	
	/* print total number of codepoints */
	printf( "Number of codepoints: %d\n", (sizeof( utf32_str )-outbytes)/4 );
	
	/* dump all utf32 characters (= unicode codepoints) */
	printf( "\nUnicode codepoints:\n" );
	for( int i = 0; i < sizeof( utf32_str )-outbytes; i+=4 )
	{
		/* printf( "%02hhx %02hhx %02hhx %02hhx\n", utf32_str[i], utf32_str[i+1], utf32_str[i+2], utf32_str[i+3] ); */
		printf( "U+%.0hhx%.0hhx%.0hhx%.0hhx\n", utf32_str[i], utf32_str[i+1], utf32_str[i+2], utf32_str[i+3] );
	}
	
	iconv_close( cd ); /* close conversion descriptor */
	
	return 0;
}
