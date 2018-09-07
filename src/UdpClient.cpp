/*
 * UdpClient.cpp
 *
 *  Created on: 29 sep 2013
 *      Author: ulf
 */
#include <iostream>
#include <string>
#include <cstring>
#include <boost/asio.hpp>
#include "UdpClient.hpp"
#include "Color.hpp"

using namespace std;
using namespace EM_UdpClient;
using namespace EM_Color;
extern DebugColor Colors;
using boost::asio::ip::udp;
using namespace boost::asio;
using namespace boost;
#include "Debug.hpp"

namespace EM_UdpClient {
UdpClient::UdpClient() {
	ipAddress = "";
	Port = "";
	init = false;
	pSocket = NULL;
	s = NULL;
}

UdpClient::UdpClient(string ipaddr, string port) {
	ipAddress = ipaddr;
	Port = port;
	init = false;
	pSocket = NULL;
	s = NULL;
}

void UdpClient::ReInit(string ipaddr, string port) {
	// TODO: 001: Add Mutex
	while (1) {
		boost::mutex::scoped_lock lock(Send_Lock, boost::try_to_lock);
		if (lock) {
			ipAddress = ipaddr;
			Port = port;
			break;
		} else {
			this_thread::yield();
		}
	}
}

bool UdpClient::CreateSocket(void) {
	pSocket = NULL;
	try {
		pSocket = new udp::socket(io_service);
	} catch (boost::system::system_error &e) {
		cout << "Socket could not be created" << endl;
		return false;
	} catch (std::exception &e) {
		cout << "Socket could not be created" << endl;
		return false;
	}
	return true;
}

bool UdpClient::OpenSocket(void) {
	try {
		pSocket->open(udp::v4());
	} catch (boost::system::system_error &e) {
		cout << "Socket could not be opened" << endl;
		delete pSocket;
		return false;
	} catch (std::exception &e) {
		cout << "Socket could not be opened" << endl;
		delete pSocket;
		return false;
	}
	return true;
}

bool UdpClient::Open(void) {
	try {
		udp::resolver resolver(io_service);
		// TODO: 001: Add Mutex for ipAddress & Port
		udp::resolver::query query(udp::v4(), ipAddress, Port);
		Endpoint = *resolver.resolve(query);
		if (!CreateSocket()) {
			return false;
		}
		if (!OpenSocket()) {
			return false;
		}
		init = true;
		return true;
	} catch (boost::system::system_error &e) {
		// We might not have a network connection
		return false;
	}
}

void UdpClient::Welcome(void) {
	Send(Colors.ClearScreen());
	IF_UDP_FLAG {
		Send("UDP Connection Established!\n");
		std::cout << "Opening port [" + Port + "] on " + ipAddress + "\n";
	}
}

void UdpClient::Send(string packet) {
	while (1) {
		boost::mutex::scoped_lock lock(Send_Lock, boost::try_to_lock);
		if (lock) {
			try {
				if (Open()) {
					pSocket->send_to(
							boost::asio::buffer(packet.c_str(), packet.size()),
							Endpoint);
					Close();
				} else {
					cout << "UDP Fail [" << packet << "]" << endl;
				}
			} catch (boost::system::system_error &e) {
				// We might not have a network connection
				cout << "UDP Fail [" << packet << "]" << endl;
			}
			break;
		} else {
			this_thread::yield();
		}
	}
}

void UdpClient::Run() {
	io_service.run();
}

void UdpClient::Close() {
	try {
		pSocket->close();
	} catch (boost::system::system_error &e) {
		// We might not have a network connection
		cout << "UDP Close Fail" << endl;
	}
	try {
		delete pSocket;
	} catch (std::exception &e) {
		cout << "UDP could not delete socket" << endl;
	}
}
}
