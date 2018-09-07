#if !defined(__UDP_CLIENT_HPP)
#define	__UDP_CLIENT_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

using boost::asio::ip::udp;

namespace EM_UdpClient {
	class UdpClient {
	public:
		UdpClient();
		UdpClient(string ipaddr, string port);
		void ReInit(string ipaddr, string port);
		bool Open(void);
		void Send(string packet);
		void Welcome(void);
		void Run(void);
	private:
		bool CreateSocket(void);
		bool OpenSocket(void);
		void Close(void);
		boost::mutex Send_Lock;
		bool init;
		boost::mutex Udp_Lock;
		string ipAddress;
		string Port;
		boost::asio::io_service io_service;
		udp::endpoint Endpoint;
		udp::socket *pSocket;
		udp::socket *s;
	};
}

#endif

