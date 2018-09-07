/*
 * Strings.cpp
 *
 *  Created on: 30 sep 2013
 *      Author: ulf
 */
#include <iostream>
#include <cstring>
#include <string>
#include "stdio.h"
#include <vector>
#include <sstream>

#include <fstream>
#include <iterator>
#include <list>
#include <cstdlib>



#include "Strings.hpp"
#include <boost/lexical_cast.hpp>

using namespace std;

string ito_string(int i) {
	return boost::lexical_cast<string>(i);
}

string lto_string(long i) {
	return boost::lexical_cast<string>(i);
}

string dto_string(double d) {
#define	DOUBLE_STRSZ	16
	char	image[DOUBLE_STRSZ];
	if (__isnan(d) || __isinf(d)) {
		return "#,#"; // Instead of Null
	}

	sprintf(image, "%0.1f", d);
	for (unsigned int i=0; i < strlen(image); i++) {
		if (image[i] == '.') {
			image[i] = ',';
		}
	}
	return string(image);
}

string to_hex_string(string val, unsigned int len) {
	string s = "";
	string adder = "";
	char buf[256];

	//If len >= 30 we have corrupt data
	if (len > 32) {
		len = 32;
		adder = "...";
	}
	string tmp;
	try {
		for (unsigned int i = 0; i < len; i++) {
			sprintf(buf, "%02x ", ((unsigned char) val[i]) & 0xff);
			s.append(buf);
		}
		s.append(adder);
	} catch (std::exception& e) {
	}
	return s;
}

string to_hex_string(string val) {
	string s = "";
//TODO: 100: to_hex_string: Why is length in first character, use normal size() for now...
	int len = val[0];
	char buf[256];

	//If len >= 30 we have corrupt data
	if (len >= 29) {
		len = 28;
	}
	string tmp;
	try {
		for (int i = 0; i <= len; i++) {
			sprintf(buf, "%02x ", ((unsigned char) val[i]) & 0xff);
			s.append(buf);
		}
	} catch (std::exception& e) {
	}
	return s;
}

string to_hex_string(const char *pval) {
	string s = "";
	size_t len = strlen(pval);
	char buf[256];

	try {
		for (unsigned int i = 0; i < len; i++) {
			sprintf(buf, "%02x ", *pval++);
			s.append(buf);
		}
	} catch (std::exception& e) {
	}
	return s;
}

string to_hex_string(unsigned char val) {
	string s = "";
	char buf[16];

	sprintf(buf, "%02x ", val);
	s.append(buf);
	return s;
}

vector<string> split(string src, unsigned char pattern) {
	vector<string> tmp;
	string part;
	unsigned int start, stop, len, size;
	const char *p = src.c_str();
	bool found = false;
	size = src.size();
	if (size == 0) {
		tmp.push_back("");
	} else {
		for (start = 0, stop = 0; stop < size; stop++) {
			if (p[stop] == pattern) {
				found = true;
				len = stop - start;
				if (len == 0) { // pattern in the first character
//					cout << "^";
					tmp.push_back("");
				} else {
					part = src.substr(start, len);
//					cout << "." << part;
					tmp.push_back(part); // Do not include pattern
				}
				start = stop + 1; // prepare for next
			} else {
				found = false;
			}
		}
		if (found) {
			tmp.push_back("");
		} else if (start < size) {
			len = stop - start;
			part = src.substr(start, len);
//			cout << "#" << start << ":" << stop << part;
			tmp.push_back(part);
		} else {
			cout << "?";
		}
//		cout << endl;
	}
	return tmp;
}

void TrimEndingChar(string &s, char cmp) {
	unsigned int sz = s.size();
	while (s[sz - 1] == cmp) {
		sz--;
		s.resize(sz);
	}
}

string cond(bool c) {
	if (c)
		return "true";
	else
		return "false";
}

string GetPortName(int portno) {
	string PortName;
	if (portno < 100) {
		PortName = "ttyUSB" + /* _str. */ito_string(portno);
	} else if (portno < 200) {
		PortName = "ttyUSB" + /* _str. */ito_string(portno - 100);
	} else if (portno < 300) {
		PortName = "ttyS" + /* _str. */ito_string((int) portno - 200);
	} else if (portno < 400) {
		PortName = "ttyO" + /* _str. */ito_string((int) portno - 300);
	} else {
		PortName = "ttyACM" + /* _str. */ito_string(portno - 400);
	}
	return PortName;
}

unsigned int	GetInt(string s)
{
	unsigned int	retval;
	if	(s.size() < 4)
		return	0xDEADBEEF;

	retval	=	(s[0] & 0xFF);
	retval	<<=	8;
	retval	|=	(s[1] & 0xFF);
	retval	<<=	8;
	retval	|=	(s[2] & 0xFF);
	retval	<<=	8;
	retval	|=	(s[3] & 0xFF);
	return	retval;
}

unsigned int	GetSwapInt(string s)
{
	unsigned int	retval;
	if	(s.size() < 4)
		return	0xDEADBEEF;

	retval	=	(s[3] & 0xFF);
	retval	<<=	8;
	retval	|=	(s[2] & 0xFF);
	retval	<<=	8;
	retval	|=	(s[1] & 0xFF);
	retval	<<=	8;
	retval	|=	(s[0] & 0xFF);
	return	retval;
}

int	GetByte(string s, unsigned int pos)
{
	if (pos >= s.size())
		return 0xFF;
	return	(s[pos] & 0xFF);
}


