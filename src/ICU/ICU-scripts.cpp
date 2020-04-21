/*
 * List all scipts from Unicode
 * 
 * This is done in C++, because uscript_getSampleUnicodeString() returns
 * an UTF-16 string, in C++ ICU is able to automatically convert it to
 * UTF-8 for output.
 * 
 * g++ ICU-scripts.cpp -o ICU-scripts `pkg-config --libs icu-uc icu-io`
 * 
 */
#include <iostream>

#include <unicode/uscript.h> /* scripts */
#include <unicode/ustream.h> /* i/o */

int main( int argc, char *argv[] )
{
	/* iterate over UScriptCode enum */
	for( int i = USCRIPT_COMMON; i < USCRIPT_CODE_LIMIT; i++ )
	{
		/* print name, short name, sample, if right-to-left */
		std::cout << uscript_getName( (UScriptCode)i );
		std::cout << "\t" << uscript_getShortName( (UScriptCode)i );
		std::cout << "\t" << uscript_getSampleUnicodeString( (UScriptCode)i );
		uscript_isRightToLeft( (UScriptCode)i ) ? std::cout << "\tRTL\n" : std::cout << "\n";
	}
	
	return 0;
}
