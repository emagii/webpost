#if !defined(__INIREADER_HPP)
#define	__INIREADER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
using namespace std;

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

using namespace boost;
namespace po = boost::program_options;

namespace EM_IniReader {
	class IniReader {
	public:
		IniReader(void);
		~IniReader(void);
		bool Open(string Filename);
		bool Close(void);
		void SetOptions(po::options_description *Options);
		bool ReadInt(string section, string option, int &value, int defval);
		bool ReadString(string section, string option, string &value, string defval);
		bool ReadBool(string section, string option, bool &value, bool defval);
	private:
		bool Open(void);
		string filename;
		ifstream ifs;
		bool	active;
		po::options_description *options;
	};
}
#endif
