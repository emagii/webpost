/*
 * Network.cpp
 *
 *  Created on: 10 mar 2015
 *      Author: ulf
 */

#include <iostream>
#include <string>
#include <cstring>
#include <locale>
#include <fstream>
#include <iterator>

#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <ifaddrs.h>

#include <Network.hpp>
#include "Strings.hpp"


using namespace std;
namespace EM_Network {

Network::Network(string iface) {
	interface = iface;
	sysfs_macaddress = "/sys/class/net/" + iface + "/address";
}

Network::~Network() {
	// TODO Auto-generated destructor stub
}

string Network::GetIPAddr() {

	struct ifaddrs	*ifa;
	struct ifaddrs	*p;
	struct sockaddr *sa;
	ipAddr = "XX.XX.XX.XX (Unknown)";

	if(getifaddrs(&ifa)) {
		return ipAddr;
	}

	p = ifa;

	while (p != NULL) {
		if(p->ifa_name == interface) {
			sa = p->ifa_addr;
			if (sa->sa_family == AF_INET) {
				ipAddr = "";
				ipAddr.append(ito_string((unsigned int) (sa->sa_data[ 2] & 0xff)));
				ipAddr.append(".");
				ipAddr.append(ito_string((unsigned int) (sa->sa_data[ 3] & 0xff)));
				ipAddr.append(".");
				ipAddr.append(ito_string((unsigned int) (sa->sa_data[ 4] & 0xff)));
				ipAddr.append(".");
				ipAddr.append(ito_string((unsigned int) (sa->sa_data[ 5] & 0xff)));
				break;
			}
		}
		p = p->ifa_next;
	}
	freeifaddrs(ifa);
	return	ipAddr;
}

string Network::GetMACAddr() {
	  string line;
	  ifstream myfile (sysfs_macaddress.c_str());
	  if (myfile.is_open()) {
	    getline (myfile,line);
	    myfile.close();
	    return line;
	  }
	  return "XX:XX:XX:XX:XX:XX (Unknown)";
}

string Network::GetMyIP() {
	  string line;
	  ifstream myfile ("/etc/MyIP");
	  /* "/etc/MyIP" could be created through:
	   * dig +short myip.opendns.com @resolver1.opendns.com
	   */
	  if (myfile.is_open()) {
	    getline (myfile,line);
	    myfile.close();
	    return line;
	  }
	  return "XX.XX.XX.XX (Unknown)";
}

} /* namespace Network */
