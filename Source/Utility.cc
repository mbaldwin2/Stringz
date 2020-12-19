#define API_EXPORT
#include <Stringz/Utility.h>

#include <iostream>
#include <stdint.h>

#include <locale>
#include <codecvt>

#define NPOS std::string::npos

namespace Stringz {

	API std::wstring WString( const std::string & master ){
		return std::wstring_convert< std::codecvt_utf8<wchar_t> >().from_bytes( master.c_str() );
	}

	API std::string Whitespace() { return " \t\n\r"; }
	API std::string Numbers() { return "0123456789"; }
	API std::string SpecialChars() { return "`~!@#$%^&*()+-="; }
	API std::string Alphabet() { return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
	API std::string AlphaNumeric() { return Alphabet() + Numbers(); }
	
	API bool IsWhitespace(char c) { return Whitespace().find(c) != NPOS; }
	API bool IsAlpha(char c) { return Alphabet().find(c) != NPOS; }
	API bool IsSpecialChar(char c) { return SpecialChars().find(c) != NPOS; }
	API bool IsNumeric(char c) { return Numbers().find(c) != NPOS; }
	API bool IsAlphaNumeric(char c) { return AlphaNumeric().find(c) != NPOS; }

	API bool IsWhitespace(const std::string & master){
		for(const auto & i : master) if( !IsWhitespace(i) ) return false;
		return true;
	}

	API bool IsAlpha(const std::string & master){
		for(const auto & i : master) if( !IsAlpha(i) ) return false;
		return true;
	}

	API bool IsSpecialChar(const std::string & master){
		for(const auto & i : master) if( !IsSpecialChar(i) ) return false;
		return true;
	}

	API bool IsNumeric(const std::string & master){
		for(const auto & i : master) if( !IsNumeric(i) ) return false;
		return true;
	}

	API bool IsAlphaNumeric(const std::string & master){
		for(const auto & i : master) if( !IsAlphaNumeric(i) ) return false;
		return true;
	}

	API std::string Strip(const std::string & str, const std::string & hash) {
		uint32_t a=0,b=str.length()-1;
		for(;a < str.length(); a++){
			auto c = str[a];
			if( hash.find(c) == NPOS ) break;
		}

		for(;b>a;b--){
			auto c = str[b];
			if( hash.find(c) == NPOS ) break;
		}
		return str.substr(a,b-a+1);
	}

	API std::vector<int> Locate(const std::string & master, const std::string & key){
		std::vector<int> set;
		int at = 0;
		while( (at = master.find(key,at)) != NPOS ){
			set.push_back(at);
			at += key.length();
		}
		return set;
	}

	API std::vector< std::string > Split( const std::string & master, char key ) {
		std::vector< std::string > set;
		size_t at = 0, prev;

		prev = at;
		while( (at = master.find(key,prev)) != NPOS ){
			set.push_back( master.substr(prev,at-prev) );
			prev = at+1;
		}

		if( prev < master.length() ) set.push_back( master.substr(prev) );
		return set;
	}

	API std::vector< std::string > Split(const std::string & master, const std::string & key) {
		std::vector< std::string > set;
		size_t at=0,prev=0;

		while( (at = master.find(key,prev)) != NPOS ){
			set.push_back( master.substr(prev,at-prev) );
			prev = at + key.length() + 1;
		}

		if( prev < master.length() ) set.push_back( master.substr(prev) );
		return set;
	}

	API std::string Replace(const std::string & master, const std::string & old, const std::string & key) {
		std::vector<std::string> set = Split(master,old);
		std::string newMaster = "";
		for(size_t i=0;i<set.size()-1;i++)
			newMaster += set[i] + key;
		return newMaster + set[ set.size()-1 ];
	}

	API bool IsHex(const std::string & master){
		auto front = master.find("0x");
		std::string buffer;
		char c = master[ master.length()-1 ];
		if(front != NPOS){
			buffer = Strip(master,"0x");
		}else if( c == 'h' or c == 'H' ) buffer = Strip(master,std::string({c,0}));
		else return false;

		bool is = true;
		for(const auto & byte : buffer){
			is = IsNumeric(byte)
				or ((byte >= 'a') and (byte <= 'f')) or ((byte >= 'A') and (byte <= 'F'));
			if(!is) return false;
		}
		return true;
	}

	API bool IsBinary(const std::string & master){
		char b = master[ master.length()-1 ];
		std::string buffer;
		if( b == 'b' or b == 'B' ) buffer = Strip(master,{b,0});
		else return false;

		for(const auto & i:buffer)
			if( (i != '0') and (i != '1') ) return false;
		return true;
	}

	API bool IsFloat(const std::string & master) {
		char f = master[ master.length() - 1 ];
		if( (f == 'f') or (f == 'F') )
			return IsDouble( master.substr(0,master.length()-1) );
		return false;
	}

	API bool IsDouble(const std::string & master) {
		std::vector<std::string> sides = Split(master,".");
		if( sides.size() == 1 ) return false;

		for(size_t i=0;i<std::max(sides[0].size(),sides[1].size());i++){
			if( i < sides[0].size() )
				if( !IsNumeric(sides[0][i]) ) return false;

			if( i < sides[1].size() )
				if( !IsNumeric(sides[1][i]) ) return false;
		}
		return true;
	}

	API std::string Remove(const std::string & master, char x){
		std::string buffer = "";
		for(size_t i=0;i<master.length();i++){
			if(x == master[i]) continue;
			else buffer += master[i];
		}
		return buffer;
	}

	API std::string Remove(const std::string & master, const std::string & key) {
		std::string buffer = "";
		size_t at = 0, prev =0;
		while( (at = master.find(key,prev)) != NPOS ){
			buffer += master.substr(prev,at-prev);
			prev = at+1;
		}

		if( prev < master.length() ) buffer += master.substr(prev);
		return buffer;
	}

	API std::string Remove(const std::string & master, const std::initializer_list<char> & list){
		std::string buffer = master;
		for(const auto & item : list)
			buffer = Remove(buffer,item);
		return buffer;
	}

	API std::string Remove(const std::string & master, const std::initializer_list<std::string> & list){
		std::string buffer = master;
		for(const auto & item : list)
			buffer = Remove(buffer,item);
		return buffer;
	}

	API std::vector<int> GetSpecialLocations(const std::string & master) {
		std::vector<int> set;
		for(size_t i=0;i<master.length();i++){
			auto byte = master[i];
			if( IsSpecialChar(byte) ) set.push_back(i);
		}
		return set;
	}

	API std::vector<int> GetAlphaLocations(const std::string & master) {
		std::vector<int> set;
		for(size_t i=0;i<master.length();i++){
			auto byte = master[i];
			if( IsAlpha(byte) ) set.push_back(i);
		}
		return set;
	}

	API std::vector<int> GetNumericLocations(const std::string & master) {
		std::vector<int> set;
		for(size_t i=0;i<master.length();i++){
			auto byte = master[i];
			if( IsNumeric(byte) ) set.push_back(i);
		}
		return set;
	}

	API std::vector<int> GetAlphaNumericLocations(const std::string & master) {
		std::vector<int> set;
		for(size_t i=0;i<master.length();i++){
			auto byte = master[i];
			if( IsAlphaNumeric(byte) ) set.push_back(i);
		}
		return set;
	}

	API std::vector<int> GetWhitespaceLocations(const std::string & master) {
		std::vector<int> set;
		for(size_t i=0;i<master.length();i++){
			auto byte = master[i];
			if( IsWhitespace(byte) ) set.push_back(i);
		}
		return set;
	}

	API bool HasWhitespace(const std::string & master) {
		std::string key = " \t\n\r";
		for(const auto & i : master)
			if( key.find(i) != NPOS ) return true;
		return false;
	}

	API bool HasSpecialChar(const std::string & master) {
		std::string key = "`~!@#$%^&*()_+-=";
		for(const auto & i : master)
			if( key.find(i) != NPOS ) return true;
		return false;
	}

	API bool HasNumeric(const std::string & master) {
		std::string key = "0123456789";
		for(const auto & i : master)
			if( key.find(i) != NPOS ) return true;
		return false;
	}

	API bool HasAlpha(const std::string & master) {
		std::string key = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for(const auto & i : master)
			if( key.find(i) != NPOS ) return true;
		return false;
	}

	API std::string Scale(const std::string & master, uint32_t r) {
		std::string copy;
		if(r) for(int i=0;i<r;i++) copy += master;
		return copy;
	}

	API bool StartsWithANumber(const std::string & master) {
		std::string clone = Strip(master);
		if( IsNumeric(clone[0]) ) return true;
		else return false;
	}

	API std::string RemoveEachOf(const std::string & master, const std::string & bytes) {
		if( bytes.length() < 1 ) return master;
		std::string clean;

		for(const auto & a : master) if( bytes.find(a) == NPOS ) clean += a;
		return clean;
	}

	API bool IsUpper(char x) { return (x >= 'A') and (x <= 'Z'); }
	API bool IsLower(char x) { return (x >= 'a') and (x <= 'z'); }

	API std::string ToLower(const std::string & master){
		std::string lower;
		for(const auto & byte : master) {
			if( IsUpper(byte) ) lower += static_cast<char>(byte + ('a' - 'A'));
			else lower += byte;
		}
		return lower;
	}

	API std::string ToUpper(const std::string & master) {
		std::string upper;
		for(const auto & byte : master) {
			if( IsLower(byte) ) upper += static_cast<char>(byte - ('a' - 'A'));
			else upper += byte;
		}
		return upper;
	}
}