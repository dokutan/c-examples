/*
 * ICU and std strings, conversion between different encodings.
 * 
 * g++ ICU-char-properties.cpp -o ICU-char-properties `pkg-config --libs icu-uc icu-io`
 * 
 */
#include <iostream>
#include <string>

#include <unicode/uchar.h> 
#include <unicode/unistr.h> 
#include <unicode/schriter.h> 

/* std::string (UTF-8) → std::u32string (UTF-32) 
 * 
 * This is done with ICU in this case, alternatively iconv could be used
 */
void UTF8toUTF32( const std::string &utf8string, std::u32string &utf32string )
{
	/* create icu UnicodeString from utf8string */
	icu::UnicodeString utf16string;
	utf16string = icu::UnicodeString::fromUTF8( utf8string );
	
	/* iterate over UnicodeString */
	icu::StringCharacterIterator it( utf16string );
	for( it.setToStart(); it.hasNext(); )
	{
		utf32string.push_back( it.next32PostInc() );
	}
	
}

int main( int argc, char *argv[] )
{
	
	/* std::string (char internally: UTF-8) */
	std::string utf8_string = "Some Unicode characters → 😀 αβγ か カ 𛀁";
	
	/* std::u32string (char32_t internally: UTF-32) */
	std::u32string utf32_string;
	
	/* call function to convert UTF-8 to UTF-32 */
	UTF8toUTF32( utf8_string, utf32_string );
	
	/* print string and size */
	std::cout << utf8_string << "\n";
	std::cout << "UTF-32:\t" << utf32_string.length() << "×4 Bytes\n";
	std::cout << "UTF-8:\t" <<  utf8_string.length() << "×1 Bytes\n";
	
	std::cout << "\nCodepoints:\n";
	
	/* iterate over u32string and print codepoint properties */
	for( auto it = utf32_string.begin(); it != utf32_string.end(); it++ )
	{
		/* codepoint */
		std::cout << "U+" << std::hex << *it << std::dec;
		
		/* block and script */
		std::cout << "\t" << u_getPropertyValueName( UCHAR_BLOCK, u_getIntPropertyValue( *it, UCHAR_BLOCK ) , U_LONG_PROPERTY_NAME ); 
		std::cout << "\t" << u_getPropertyValueName( UCHAR_SCRIPT, u_getIntPropertyValue( *it, UCHAR_SCRIPT ) , U_LONG_PROPERTY_NAME ); 
		
		/* codepoint name */
		char buffer[1024];
		UErrorCode err = U_ZERO_ERROR;
		u_charName( *it, U_UNICODE_CHAR_NAME, buffer, sizeof(buffer), &err );
		std::cout << "\t" << buffer;
		
		/* codepoint alias ? */
		err = U_ZERO_ERROR;
		u_charName( *it, U_CHAR_NAME_ALIAS, buffer, sizeof(buffer), &err );
		if( buffer[0] == '\0' )
			std::cout << "\tno alias\n";
		else
			std::cout << "\t" << buffer << "\n"; 
		
	}
	
	return 0;
}
