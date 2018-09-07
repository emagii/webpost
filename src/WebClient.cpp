/*
 * WebClient.cpp
 *
 *  Created on: 29 sep 2013
 *      Author: ulf
 */
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "UdpClient.hpp"
#include "UdpDebug.hpp"
// #include "Externals.hpp"
using namespace std;

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "WebClient.hpp"
#include "Debug.hpp"
using namespace EM_WebClient;
using namespace EM_UdpClient;
using namespace EM_UdpDebug;
string buffer;
extern UdpDebug DebugPort;
WebClient::WebClient(string Url) {
	DebugPort.WriteLine("Connecting to: " + Url, GREEN);
	url = Url;
	buffer = "";
	userpwd = "";
}

WebClient::WebClient(string Url, string credentials = "") {
	DebugPort.WriteLine("Connecting to Protected: " + Url, BLUE);
	url = Url;
	buffer = "";
	userpwd = credentials;
}

void WebClient::setUrl(string Url) {
	url = Url;
	buffer = "";
	userpwd = "";
}

void WebClient::setUrl(string Url, string credentials = "") {
	url = Url;
	buffer = "";
	userpwd = credentials;
}

string WebClient::Post(string query) {
	try {
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		// Setting the URL to retrive.
		request.setOpt(new curlpp::options::Url(url + query));
		request.setOpt(new curlpp::options::Verbose(false));
		request.setOpt(new curlpp::options::Timeout(30));
		if (userpwd != "") {
			request.setOpt(new curlpp::options::UserPwd(userpwd));
			request.setOpt(new curlpp::options::HttpAuth(CURLAUTH_DIGEST));
		}

		std::list<std::string> header;
		header.push_back("Content-Type: application/octet-stream");

		request.setOpt(new curlpp::options::PostFields(query));
		request.setOpt(new curlpp::options::PostFieldSize(query.size()));

		cout	<< "BEGIN"	<< endl;
		request.perform();
		cout	<< "END"	<< endl;
//		ostringstream os;
//		os << request << std::endl;
//		return os.str();
		return "";

	} catch (curlpp::LibcurlRuntimeError & e) {
		DebugPort.WriteLine("cURLpp Exception: LibCurlRuntimeError", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::LibcurlLogicError & e) {
		DebugPort.WriteLine("cURLpp Exception: LibcurlLogicError", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::UnsetOption & e) {
		DebugPort.WriteLine("cURLpp Exception: UnsetOption", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::NotAvailable & e) {
		DebugPort.WriteLine("cURLpp Exception: NotAvailable", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::UnknowException & e) {
		DebugPort.WriteLine("cURLpp Exception: UnknowException ", RED);
		std::cout << e.what() << std::endl;
#if	0
	} catch (curlpp::CallbackException & e) {
		std::cout << e.what() << std::endl;
#endif
	} catch (curlpp::LogicError & e) {
		DebugPort.WriteLine("cURLpp Exception: LogicError", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::RuntimeError & e) {
		DebugPort.WriteLine("cURLpp Exception: RuntimeError", RED);
		std::cout << e.what() << std::endl;
	}
	return buffer;
}

string data;

size_t readData(char *buffer, size_t size, size_t nitems) {
	strncpy(buffer, data.c_str(), size * nitems);
	return size * nitems;
}

string WebClient::Upload(string payload) {
	data = payload;
	try {
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		// Setting the URL to retrive.
		using namespace curlpp::Options;
		request.setOpt(new Url(url));
		request.setOpt(new Verbose(false));

		std::list<std::string> headers;
		headers.push_back("Content-Type: application/text");
		request.setOpt(new HttpHeader(headers));
		request.setOpt(new PostFields(data));
		request.setOpt(new PostFieldSize(data.size()));
		request.setOpt(new Timeout(30));
		if (userpwd != "") {
			request.setOpt(new curlpp::options::UserPwd(userpwd));
			request.setOpt(new curlpp::options::HttpAuth(CURLAUTH_DIGEST));
		}

		request.perform();
		ostringstream os;
		os << request << std::endl;
		return os.str();

	} catch (curlpp::LibcurlRuntimeError & e) {
		DebugPort.WriteLine("cURLpp Exception: LibCurlRuntimeError", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::LibcurlLogicError & e) {
		DebugPort.WriteLine("cURLpp Exception: LibcurlLogicError", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::UnsetOption & e) {
		DebugPort.WriteLine("cURLpp Exception: UnsetOption", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::NotAvailable & e) {
		DebugPort.WriteLine("cURLpp Exception: NotAvailable", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::UnknowException & e) {
		DebugPort.WriteLine("cURLpp Exception: UnknowException ", RED);
		std::cout << e.what() << std::endl;
#if	0
	} catch (curlpp::CallbackException & e) {
		std::cout << e.what() << std::endl;
#endif
	} catch (curlpp::LogicError & e) {
		DebugPort.WriteLine("cURLpp Exception: LogicError", RED);
		std::cout << e.what() << std::endl;
	} catch (curlpp::RuntimeError & e) {
		DebugPort.WriteLine("cURLpp Exception: RuntimeError", RED);
		std::cout << e.what() << std::endl;
	}
	return buffer;
}

