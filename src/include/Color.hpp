#if !defined(__COLOR_HPP)
#define	__COLOR_HPP

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

enum ConsoleColor {
	BLACK,
	BLUE,
	CYAN,
	DARKBLUE,
	DARKCYAN,
	DARKGREY,
	DARKGREEN,
	DARKMAGENTA,
	DARKRED,
	DARKYELLOW,
	GREEN,
	GREY,
	MAGENTA,
	RED,
	WHITE,
	YELLOW
};

enum ColorMode {
	None, Terminal, Windows
};
namespace EM_Color {

	class DebugColor {
	private:
		// Windows Colors
		static const string WPREFIX;
		static const string WPOSTFIX;
		static const string WCRESET;
		static const string WBlack;
		static const string WBlue;
		static const string WCyan;
		static const string WDarkBlue;
		static const string WDarkCyan;
		static const string WDarkGrey;
		static const string WDarkGreen;
		static const string WDarkMagenta;
		static const string WDarkRed;
		static const string WDarkYellow;
		static const string WGreen;
		static const string WGrey;
		static const string WMagenta;
		static const string WRed;
		static const string WWhite;
		static const string WYellow;

		// Linux Colors (Terminal)
		static const string PREFIX;
		static const string POSTFIX;
		static const string CRESET;
		static const string Black;
		static const string Blue;
		static const string Cyan;
		static const string DarkBlue;
		static const string DarkCyan;
		static const string DarkGrey;
		static const string DarkGreen;
		static const string DarkMagenta;
		static const string DarkRed;
		static const string DarkYellow;
		static const string Green;
		static const string Grey;
		static const string Magenta;
		static const string Red;
		static const string White;
		static const string Yellow;

		ColorMode Mode;
	public:
		DebugColor();
		const string To_String(ConsoleColor color);
		void setMode(ColorMode c);
		ColorMode getMode(void);
		string Reset(void);
		string ClearScreen(void);
	};
}
#endif
