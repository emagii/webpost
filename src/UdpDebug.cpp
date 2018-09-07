/*
 * UdpDebug.cpp
 *
 *  Created on: 29 sep 2013
 *      Author: ulf
 */
#define	FIX	1
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "boost/date_time/gregorian/gregorian.hpp"	// Date/Time
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>

// #include "TypeDefinitions.hpp"
#include "UdpClient.hpp"
#include "UdpDebug.hpp"
#include "Color.hpp"
#include "DateTime.hpp"
#include "Strings.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace EM_UdpClient;

using namespace EM_UdpDebug;
using namespace EM_DateTime;
using namespace EM_Color;
using namespace EM_IniReader;
namespace po = boost::program_options;
extern DebugColor Colors;

#include	"Debug.hpp"

void iTo_String(int i, string& result) {
	ostringstream convert; // stream used for the conversion
	convert << i; // insert the textual representation of 'Number' in the characters in the stream
	string s = convert.str();
	cout << "String Size: " << s.size() << endl;
	result = s;
	cout << "String Size: " << result.size() << endl;

}

namespace EM_UdpDebug {
UdpDebug::UdpDebug() {
	fileName = "webpost.conf";
	UDPPort = "4100";
}

void UdpDebug::Init(void) {
	bool config;
	fileName = "webpost.conf";
	ipAddress = "127.0.0.1";
	UDPPort = "4100";
	debugType = ERROR;
	reconfig = false;
	isClient = false;
	DEBUG_ALL = "++DebugAll";

	config = ReadConfig(false);
	try {
		udpClient = new UdpClient(ipAddress, UDPPort);
		udpClient->Welcome();
		if (!config) {
			WriteLine("Using default configuration", RED);
		}
	} catch (std::exception& e) {
		std::cerr << "Exception in OpenUdp " << e.what() << std::endl;
	}
}

bool UdpDebug::OpenIni(string fname) {
	string home;
	string sysconfig;
	string current;
	bool configurable = false;

	try {
		home = getenv("HOME");
		//	When run as a service on ARM, environment does not contain $PWD
		//	Results in SIGSEGV
		home.append("/.local/share/webpost/");
		sysconfig = "/etc/";
		current = "";
#if	defined(HAS_PWD)
		string pwd;
		cwd = getenv("PWD");
		cout << "PWD=" << pwd << endl;
#endif
		if (debug_ini.Open(current + fname) == true) {
			if (reconfig)
				WriteLine("Opening: " + current + fname, UdpDebug::VERBOSE);
			configurable = true;
		} else if (debug_ini.Open(home + fname) == true) {
			if (reconfig)
				WriteLine("Opening: " + home + fname, UdpDebug::VERBOSE);
			configurable = true;
		} else if (debug_ini.Open(sysconfig + fname) == true) {
			if (reconfig)
				WriteLine("Opening: " + sysconfig + fname, UdpDebug::VERBOSE);
			configurable = true;
		} else {
			if (reconfig)
				WriteLine(fname + " not found", UdpDebug::VERBOSE);
		}
	} catch (std::exception& e) {
		cerr << "Warning: Cannot open " << fname << endl;
		configurable = false;
	}
	return configurable;
}

bool UdpDebug::ReadConfig(bool reload) {
	string option;
	int DebugType;
	int Term;
	po::options_description debug("Debug");
	debug.add_options()
			("Debug.Port", po::value<int>(), "UDP Port")
			("Debug.IPAddress", po::value<string>(), "IP Address")
			("Debug.DebugType", po::value<int>(), "Debug Type")
			("Debug.DebugFlags", po::value<int>(), "Debug Flags")
			("Debug.DebugXML", po::value<int>(), "Debug XML")
			("Debug.Color",po::value<int>(), "UDP Color Mode");

	try {
		if (OpenIni(fileName)) {
			debug_ini.SetOptions(&debug);
			if (reconfig)
				WriteLine("UDP Configuration Reloaded", MAGENTA);
			IF_INIT_FLAG {
				cout << "Configuring from webpost.conf" << endl;
			}
			// It is OK to change these variables, since the only other user is the Constructor
			int iUDPPort;
			bool tmp = debug_ini.ReadInt("Debug", "Port", iUDPPort, 4100);
			if (tmp)
				this->UDPPort = ito_string(iUDPPort);

			tmp = debug_ini.ReadString("Debug", "IPAddress", ipAddress,
					"127.0.0.1");
			tmp = debug_ini.ReadInt("Debug", "DebugType", DebugType, 1);
			tmp = debug_ini.ReadInt("Debug", "DebugFlags", debug_flags, 0);
			tmp = debug_ini.ReadInt("Debug", "DebugXML", debug_xml, 0);
			debugType = (DebugTypes) DebugType;
			if (Colors.getMode() == None || reload) {
				// TODO: 050: If we are rereading the config, we might use the wrong color mode on the old terminal
				// ToDo: Add Mutex to UdpClient
				// Default color mode is Windows..,
				bool tmp = debug_ini.ReadInt("Debug", "Color", Term, 2);
				if (Term == 1) {
					Colors.setMode(Terminal);
				} else if (Term == 2) {
					Colors.setMode(Windows);
				} else {
					cout << "Unknown Color=" << Term << endl;

				}
				if (tmp) {
				} // Avoid warning!
			}
			debug_ini.Close();
		} else {
			if (reconfig)
				WriteLine("UDP Reonfiguration failed", RED);
			// Open Failed
			// Use default values
			IF_INIT_FLAG {
				cout << "Configuring using default" << endl;
			}
			UDPPort = "4100";
			ipAddress = "127.0.0.1";
			DebugType = ERROR;
			Colors.setMode(Terminal);
			return false;
		}
	} catch (std::exception& e) {
		cerr << "Warning: Failed to read " << fileName << endl;
		UDPPort = "4100";
		ipAddress = "127.0.0.1";
		DebugType = ERROR;
		if (Colors.getMode() == None) {
			IF_INIT_FLAG {
				cout << "Configuring using default due to exception" << endl;
			}
			Colors.setMode(Windows);
		}
		return false;
	}
	return true;
}

void UdpDebug::ReloadConfig(void) {
	reconfig = true;
	ReadConfig(true);
	udpClient->ReInit(ipAddress, UDPPort);
}

void UdpDebug::Run(void) {
	udpClient->Run();
}

void UdpDebug::setDebugType(DebugTypes value) {
	debugType = value;
}

void UdpDebug::setDebugType(int value) {
	debugType = (DebugTypes) value;
}

UdpDebug::DebugTypes UdpDebug::getDebugType(void) {
	return debugType;
}

void UdpDebug::IsClient(bool value) {
	isClient = value;
}

void UdpDebug::WriteLine(string line) {
	string timestamp = Clock.TimeOfDay(true);
	line = timestamp + line;
	udpClient->Send(line);
}

void UdpDebug::WriteLine(string line1, string line2) {
	string line = Clock.TimeOfDay(true) + ":[" + line1 + "] " + line2;
	udpClient->Send(line);
}

void UdpDebug::WriteLine(string line, DebugTypes type) {
	if (type <= debugType) {
		line = Clock.TimeOfDay(true) + ":" + line;
		udpClient->Send(line);
	}
}

void UdpDebug::WriteLine(string line1, string line2, DebugTypes type) {
	// TODO: 050: If the rereading the initialization,causes a change in ipaddress/port/debuglevel
	// we might change the debug level before the ipaddress/port is changedd
	// so the current port might get the new debug level for one or more messages
	if (type <= debugType) {
		string line = Clock.TimeOfDay(true) + ":[" + line1 + "] " + line2;
		udpClient->Send(line);
	}
}

void UdpDebug::WriteLine(string line, ConsoleColor color) {
	line = Colors.To_String(color) + " " + Clock.TimeOfDay(true) + ":[" + line
			+ "]" + Colors.Reset();
	udpClient->Send(line);
}

void UdpDebug::WriteLine(string line1, string line2, ConsoleColor color) {
	string line = Colors.To_String(color) + " " + Clock.TimeOfDay(true) + ":["
			+ line1 + "] " + line2 + Colors.Reset();
	udpClient->Send(line);
}

void UdpDebug::WriteLine(bool isClient, string line1, string line2,
		string line3) {
	string mode = "";
	enum ConsoleColor color;

	if (isClient) {
		mode = " Client ";
		color = CYAN;
	} else {
		mode = " Server ";
		color = WHITE;
	}

	string line = Colors.To_String(color) + " " + Clock.TimeOfDay(true) + ":["
			+ mode + "] " + line1 + " : " + line2 + " : " + line3;

	udpClient->Send(line);
}

void UdpDebug::WriteHex(string line1, string line2) {
	string line = Clock.TimeOfDay(true) + ":[" + line1 + "] "
			+ to_hex_string(line2);
	udpClient->Send(line);
}
}
