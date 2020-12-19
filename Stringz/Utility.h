#pragma once

#ifndef STRINGZ_UTILITY
#define STRINGZ_UTILITY

#include <string>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
# pragma comment(lib, "OSDetect.lib")
#endif

#include <OS/Prefix.h>

namespace Stringz {

	/*
		Is*(char): compares the given character for the information in the function name.
		i.e.:	-> IsWhitespace(byte) compares the byte against the common whitespace characters.
			-> IsNumeric(byte) compares against numbers.

		Is*(string): copmares the given string against the information in the function name.
	*/
	API bool IsWhitespace(char);
	API bool IsSpecialChar(char);
	API bool IsNumeric(char);
	API bool IsAlphaNumeric(char);
	API bool IsAlpha(char);
	API bool IsUpper(char);
	API bool IsLower(char);

	API bool IsWhitespace(const std::string &);
	API bool IsSpecialChar(const std::string &);
	API bool IsNumeric(const std::string &);
	API bool IsAlphaNumeric(const std::string &);
	API bool IsAlpha(const std::string &);

	API bool IsHex(const std::string &);
	API bool IsBinary(const std::string &);
	API bool IsFloat(const std::string &);
	API bool IsDouble(const std::string &);

	/*
		Split(master, by): separates the master string according to the by, byte or string.
		i.e.:	Split("Thisxisxaxtest",'x') -> {"This","is","a","test"} (std::vector)
	*/
	API std::vector< std::string > Split(const std::string &, char =' ');
	API std::vector< std::string > Split(const std::string &, const std::string &);
	/*
		Strip(master, items): searches for the individual characters in the `items' string
			and removes the ones that were located.
	*/
	API std::string Strip(const std::string &, const std::string & =" \t\n\r");
	/*
		Locate(master,item): returns the locations of the item in the master string.
		->	Returns the zero byte location in reference master's zero byte.
	*/
	API std::vector<int> Locate(const std::string &, const std::string &);
	/*
		Replace(master, this, that): replaces `this' with `that' string in `master'.
	*/
	API std::string Replace(const std::string &, const std::string &, const std::string &);
	/*
		Remove(master, this): removes `this' from `master' as it is found.
		Remove(master, items): removes a list of `items' from `master' as they are found.
	*/
	API std::string Remove(const std::string &, char);
	API std::string Remove(const std::string &, const std::string &);
	API std::string Remove(const std::string &, const std::initializer_list<char> &);
	API std::string Remove(const std::string &, const std::initializer_list<std::string> &);
	
	/*
		RemoveEachOf(master, bytes): removes each occurance of any byte given.
	*/
	API std::string RemoveEachOf(const std::string &, const std::string &);

	/*
		Get*Locations(master): returns the zeroth byte locations of given `master' string.
	*/
	API std::vector<int> GetWhitespaceLocations(const std::string &);
	API std::vector<int> GetSpecialCharLocations(const std::string &);
	API std::vector<int> GetNumericLocations(const std::string &);
	API std::vector<int> GetAlphaLocations(const std::string &);
	API std::vector<int> GetAlphaNumericLocations(const std::string &);

	/*
		Has*(master): returns true if the given information 
	*/
	API bool HasSpecialChar(const std::string &);
	API bool HasWhitespace(const std::string &);
	API bool HasNumeric(const std::string &);
	API bool HasAlpha(const std::string &);

	/*
		Scale(master,n_times): returns a concatinated copy of `master'*`n_times'
	*/
	API std::string Scale(const std::string &, uint32_t);\
	/*
		StartsWithANumber(master): determins if master starts with a number
	*/
	API bool StartsWithANumber(const std::string &);

	API std::string SpecialChars();
	API std::string Numbers();
	API std::string Whitespace();

	/*
		WString(master): converts master to std::wstring object.
	*/
	API std::wstring WString( const std::string & );

	API std::string ToLower(const std::string &);
	API std::string ToUpper(const std::string &);
	API std::string ToNameCase(const std::string &);
}

#endif // ending STRINGZ_UTILITY //