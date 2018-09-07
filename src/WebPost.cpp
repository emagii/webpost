/*
 * WebPost.cpp
 *
 *  Created on: 7 Sep 2018
 *      Author: Ulf Samuelsson
 */
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "UdpClient.hpp"
#include "UdpDebug.hpp"
#include "WebClient.hpp"
#include "Color.hpp"

using namespace std;
using namespace EM_WebClient;
using namespace EM_UdpDebug;
using namespace EM_Color;
UdpDebug DebugPort;
int	debug_flags;
int     debug_xml;
DebugColor Colors;

int main(int argc, char **argv)
{
	string response;
	DebugPort.Init();

	WebClient echo = WebClient("http://169.254.1.1/echo/");

        response = echo.Post("?name=WTF&is=happening");
}
