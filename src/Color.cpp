/*
 * Color.cpp
 *
 *  Created on: 29 sep 2013
 *      Author: ulf
 */

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Debug.hpp"

using namespace std;

using namespace EM_Color;

static void colorlog(ColorMode c) {
	IF_COLOR_FLAG {
		if (c == Terminal) {
			cout << "Mode=Terminal" << endl;
		} else if (c == Windows) {
			cout << "Mode=Windows" << endl;
		} else if (c == None) {
			cout << "Mode=None" << endl;
		}
	}
}

static void colorassign(ColorMode c) {
	IF_COLOR_FLAG {
		if (c == Terminal) {
			cout << "Mode=Terminal" << endl;
		} else if (c == Windows) {
			cout << "Mode=Windows" << endl;
		} else if (c == None) {
			cout << "Mode=None" << endl;
		}
	}
}
#define	CLOG(c)	colorlog((c))
#define	ALOG(c)	colorassign((c))

const std::string DebugColor::WPREFIX = "!#Color:";
const std::string DebugColor::WPOSTFIX = "";
const std::string DebugColor::WCRESET = "";
const std::string DebugColor::WBlack = WPREFIX + "Black ";
const std::string DebugColor::WBlue = WPREFIX + "Blue ";
const std::string DebugColor::WCyan = WPREFIX + "Cyan ";
const std::string DebugColor::WDarkBlue = WPREFIX + "DarkBlue ";
const std::string DebugColor::WDarkCyan = WPREFIX + "DarkCyan ";
const std::string DebugColor::WDarkGrey = WPREFIX + "DarkGrey ";
const std::string DebugColor::WDarkGreen = WPREFIX + "DarkGreen ";
const std::string DebugColor::WDarkMagenta = WPREFIX + "DarkMagenta ";
const std::string DebugColor::WDarkRed = WPREFIX + "DarkRed ";
const std::string DebugColor::WDarkYellow = WPREFIX + "DarkYellow ";
const std::string DebugColor::WGreen = WPREFIX + "Green ";
const std::string DebugColor::WGrey = WPREFIX + "Grey ";
const std::string DebugColor::WMagenta = WPREFIX + "Magenta ";
const std::string DebugColor::WRed = WPREFIX + "Red ";
const std::string DebugColor::WWhite = WPREFIX + "White ";
const std::string DebugColor::WYellow = WPREFIX + "Yellow ";

const std::string DebugColor::PREFIX = "\033[";
const std::string DebugColor::POSTFIX = "m";
const std::string DebugColor::CRESET = "\033[0m";
const std::string DebugColor::Black = PREFIX + "30;0" + POSTFIX;
const std::string DebugColor::Red = PREFIX + "31;1" + POSTFIX;
const std::string DebugColor::Green = PREFIX + "32;1" + POSTFIX;
const std::string DebugColor::Yellow = PREFIX + "33;1" + POSTFIX;
const std::string DebugColor::Blue = PREFIX + "34;1" + POSTFIX;
const std::string DebugColor::Magenta = PREFIX + "35;1" + POSTFIX;
const std::string DebugColor::Cyan = PREFIX + "36;1" + POSTFIX;
const std::string DebugColor::White = PREFIX + "37;1" + POSTFIX;

const std::string DebugColor::DarkBlue = PREFIX + "34;0" + POSTFIX;
const std::string DebugColor::DarkCyan = PREFIX + "36:1" + POSTFIX;
const std::string DebugColor::DarkGrey = PREFIX + "30;1" + POSTFIX;
const std::string DebugColor::DarkGreen = PREFIX + "32;0" + POSTFIX;
const std::string DebugColor::DarkMagenta = PREFIX + "35;0" + POSTFIX;
const std::string DebugColor::DarkRed = PREFIX + "31;0" + POSTFIX;
const std::string DebugColor::DarkYellow = PREFIX + "33;0" + POSTFIX;
const std::string DebugColor::Grey = PREFIX + "37;0" + POSTFIX;

DebugColor::DebugColor() {
	Mode = None;
	cout << "Creating new DebugColor" << endl;
}

void DebugColor::setMode(ColorMode c) {
	ALOG(c);
	Mode = c;
}

ColorMode DebugColor::getMode(void) {
	return Mode;
}

string DebugColor::Reset(void) {
	if (Mode == Terminal) {
		return CRESET;
	} else if (Mode == Windows) {
		return "";
	} else {
		return "";
	}
}

string DebugColor::ClearScreen(void) {
	if (Mode == Terminal) {
		return PREFIX + "2J";
	} else if (Mode == Windows) {
		return "";
	}
	return "";
}

const string DebugColor::To_String(ConsoleColor color) {
	CLOG(Mode);
	if (Mode == Windows) {
		switch (color) {
		case BLACK:
			return DebugColor::WBlack;
			break;
		case BLUE:
			return DebugColor::WBlue;
			break;
		case CYAN:
			return DebugColor::WCyan;
			break;
		case DARKBLUE:
			return DebugColor::WDarkBlue;
			break;
		case DARKCYAN:
			return DebugColor::WDarkCyan;
			break;
		case DARKGREY:
			return DebugColor::WDarkGrey;
			break;
		case DARKGREEN:
			return DebugColor::WDarkGreen;
			break;
		case DARKMAGENTA:
			return DebugColor::WDarkMagenta;
			break;
		case DARKRED:
			return DebugColor::WDarkRed;
			break;
		case DARKYELLOW:
			return DebugColor::WDarkYellow;
			break;
		case GREEN:
			return DebugColor::WGreen;
			break;
		case GREY:
			return DebugColor::WGrey;
			break;
		case MAGENTA:
			return DebugColor::WMagenta;
			break;
		case RED:
			return DebugColor::WRed;
			break;
		case WHITE:
			return DebugColor::WWhite;
			break;
		case YELLOW:
			return DebugColor::WYellow;
			break;
		}
	} else if (Mode == Terminal) {
		switch (color) {
		case BLACK:
			return DebugColor::Black;
			break;
		case BLUE:
			return DebugColor::Blue;
			break;
		case CYAN:
			return DebugColor::Cyan;
			break;
		case DARKBLUE:
			return DebugColor::DarkBlue;
			break;
		case DARKCYAN:
			return DebugColor::DarkCyan;
			break;
		case DARKGREY:
			return DebugColor::DarkGrey;
			break;
		case DARKGREEN:
			return DebugColor::DarkGreen;
			break;
		case DARKMAGENTA:
			return DebugColor::DarkMagenta;
			break;
		case DARKRED:
			return DebugColor::DarkRed;
			break;
		case DARKYELLOW:
			return DebugColor::DarkYellow;
			break;
		case GREEN:
			return DebugColor::Green;
			break;
		case GREY:
			return DebugColor::Grey;
			break;
		case MAGENTA:
			return DebugColor::Magenta;
			break;
		case RED:
			return DebugColor::Red;
			break;
		case WHITE:
			return DebugColor::White;
			break;
		case YELLOW:
			return DebugColor::Yellow;
			break;
		}
	}
	return DebugColor::White;
}
