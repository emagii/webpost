#if !defined(__UDP_DEBUG_HPP)
#define	__UDP_DEBUG_HPP
#include <iostream>
#include <cstring>
#include <string>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

namespace po = boost::program_options;

#include "UdpClient.hpp"
#include "Color.hpp"
#include "DateTime.hpp"
#include "IniReader.hpp"

using namespace std;
using namespace EM_UdpClient;
using namespace EM_Color;
using namespace EM_DateTime;
using namespace EM_IniReader;

using boost::asio::ip::udp;

namespace EM_UdpDebug {
	class UdpDebug {
	public:

		enum DebugTypes {
			NODEBUG = 0, ERROR, DEBUG, VERBOSE, INSANE, DANGEROUS
		};

		string DEBUG_ALL;

	private:
		// The Following variables are only used by constructor, and when reloading
		string fileName;
		// Debug.ini will set the following variables
		string ipAddress;
		string UDPPort;
		DebugTypes debugType;

		// --------------------------------------------------------------------------
		IniReader debug_ini;

		// Thge following variables should be left alone when reloading.
		UdpClient *udpClient;
		bool isClient;
		bool reconfig;
		DateTime Clock; // Replacing DateTime.Now.ToLongTimeString()
		int	dummy;

	public:
		UdpDebug();
		void Init(void);
		bool OpenIni(string);
		bool ReadConfig(bool);
		void ReloadConfig(void);
		void Run(void);

		void setDebugType(DebugTypes value);
		void setDebugType(int value);
		DebugTypes getDebugType(void);

		void IsClient(bool value);

		void WriteLine(string line);
		void WriteLine(string line1, string line2);

		void WriteLine(string line, DebugTypes type);
		void WriteLine(string line1, string line2, DebugTypes type);

		void WriteLine(string line, ConsoleColor color);
		void WriteLine(string line1, string line2, ConsoleColor color);

		void WriteLine(bool isClient, string line1, string line2, string line3);
		void WriteHex(string line1, string line2);

	};
}

#endif
