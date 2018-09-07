/*
 * IniReader.cpp
 *
 *  Created on: 29 sep 2013
 *      Author: ulf
 */
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
using namespace std;

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "IniReader.hpp"

using namespace boost;
using namespace EM_IniReader;

namespace po = boost::program_options;

namespace EM_IniReader {

IniReader::IniReader(void) {
	active = false;
	options = NULL;
}

IniReader::~IniReader(void) {
	this->Close();
}

bool IniReader::Open(void) {
	try {
		ifs.open(filename.c_str(), ifstream::in);
		if (!ifs) {
			cerr << "can not open config file: \"" << filename << "\"\n";
			return false;
		}
		active = true;
	} catch (po::error& e) {
		std::cerr << "ERROR in \"" << filename << "\":" << e.what() << std::endl
				<< std::endl;
		return false;
	}
	return true;
}

bool IniReader::Close(void) {
	if (active) {
		active = false;
		try {
			ifs.close();
		} catch (po::error& e) {
			cerr << "ERROR while closing " << filename << ":" << e.what()
					<< std::endl;
			return false;
		}
	}
	return true;
}

bool IniReader::Open(string filename) {
	// This open will only store the file name of a file that can be opened.
	this->filename = filename;
	if (!Open()) {
		this->filename = "";
		return false;
	}
	if (!Close()) {
		this->filename = "";
	}
	return true;
}

void IniReader::SetOptions(po::options_description *Options) {
	options = Options;
}

bool IniReader::ReadInt(string section, string option, int &value, int defval) {
	po::variables_map vm;
	if (!Open()) {
		value = defval;
		return false;
	}
	po::store(po::parse_config_file(ifs, *options), vm);
	// ----------------------------------------------------------

	string option_name = section + "." + option;

	try {
		if (vm.count(option_name)) {
			value = vm[option_name].as<int>(); // May throw an exception
			po::notify(vm);
		}
	} catch (po::error& e) {
		value = defval;
		return false;
	}
	if (Close()) {

	}
	return true;
}

bool IniReader::ReadString(string section, string option, string &value,
		string defval) {
	po::variables_map vm;
	if (!Open()) {
		value = defval;
		return false;
	}
	po::store(po::parse_config_file(ifs, *options), vm);
	// ----------------------------------------------------------

	string option_name = section + "." + option;


	try {
		if (vm.count(option_name)) {
			value = vm[option_name].as<string>(); // May throw an exception
			po::notify(vm);
		}
	} catch (po::error& e) {
		value = defval;
		return false;
	}

	// ----------------------------------------------------------
	if (Close()) {

	}
	return true;
}

bool IniReader::ReadBool(string section, string option, bool &value,
		bool defval) {
	po::variables_map vm;
	if (!Open()) {
		value = defval;
		return false;
	}
	po::store(po::parse_config_file(ifs, *options), vm);
	// ----------------------------------------------------------
	string option_name = section + "." + option;

	try {
		if (vm.count(option_name)) {
			value = vm[option_name].as<bool>(); // May throw an exception
			po::notify(vm);
		}
	} catch (po::error& e) {
		value = defval;
		return false;
	}

	// ----------------------------------------------------------
	if (Close()) {

	}
	return true;
}
}
