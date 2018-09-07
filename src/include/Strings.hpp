#if !defined(__STRINGS_HPP)
#define	__STRINGS_HPP
/*
 * Strings.hpp
 *
 *  Created on: 30 sep 2013
 *      Author: ulf
 */
#include <cstring>
#include <string>
#include <vector>

using namespace std;

extern string ito_string(int i);
//extern	string To_String(unsigned int i);
extern string lto_string(long i);
extern string dto_string(double d);
extern vector<string> split(string src, unsigned char pattern);
extern void TrimEndingChar(string &s, char cmp);
extern string to_hex_string(string val);
extern string to_hex_string(const char *pval);
extern string to_hex_string(unsigned char val);
extern string to_hex_string(string val, unsigned int len);
extern string cond(bool c);
extern unsigned int	GetInt(string s);
extern unsigned int	GetSwapInt(string s);
extern int	GetByte(string s, unsigned int pos);

extern string GetPortName(int portno);


#endif

