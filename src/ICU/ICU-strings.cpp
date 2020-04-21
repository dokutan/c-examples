/*
 * ICU and std strings, conversion between different encodings.
 * 
 * g++ ICU-strings.cpp -o ICU-strings `pkg-config --libs icu-uc icu-io`
 * 
 */

#include <iostream>
#include <string>

#include <unicode/unistr.h> 
#include <unicode/schriter.h> /* string character iterator */

int main( int argc, char *argv[] )
{
	
	/* icu::UnicodeString (UTF-16 internally) */
	icu::UnicodeString utf16_string( "Some Unicode characters → 😀 αβγ か カ" );
	
	/* std::string (char internally: UTF-8) */
	std::string utf8_string;
	
	/* convert icu::UnicodeString(UTF-16) to std::string(UTF-8) */
	utf16_string.toUTF8String( utf8_string );
	
	/* std::u32string (char32_t internally: UTF-32) */
	std::u32string utf32_string;
	
	/* convert icu::UnicodeString(UTF-16) to std::u32string(UTF-32) */
	icu::StringCharacterIterator it( utf16_string );
	for( it.setToStart(); it.hasNext(); )
	{
		utf32_string.push_back( it.next32PostInc() );
	}
	
	/* print string and size */
	std::cout << utf8_string << "\n";
	std::cout << "UTF-32:\t" << utf32_string.length() << "×4 = " << utf32_string.length()*4 << " Bytes\n";
	std::cout << "UTF-16:\t" << utf16_string.length() << "×2 = " << utf16_string.length()*2 << " Bytes\n";
	std::cout << "UTF-8:\t" <<  utf8_string.length() << "×1 = " << utf8_string.length() << " Bytes\n";
	
	return 0;
}
