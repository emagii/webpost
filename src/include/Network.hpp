/*
 * Network.hpp
 *
 *  Created on: 10 mar 2015
 *      Author: ulf
 */

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <string>
#include <cstring>
#include <locale>
#include <fstream>
#include <iterator>
using namespace std;
namespace EM_Network {

class Network {
private:
	string	interface;
	string	sysfs_macaddress;
public:
	string	ipAddr;

	Network(string iface);
	virtual ~Network();
	string GetIPAddr();
	string GetMACAddr();
	string GetMyIP();
};

} /* namespace Network */

#endif /* NETWORK_HPP_ */
