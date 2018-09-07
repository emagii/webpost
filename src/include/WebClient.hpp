#if !defined(__WEBCLIENT_HPP)
#define	__WEBCLIENT_HPP

#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

namespace EM_WebClient {
	class WebClient {
	private:
		static const int MAX_FILE_LENGTH = 20000;
		string url;
		string userpwd;
	public:
		WebClient(string);
		WebClient(string, string);
		string Post(string);
		void setUrl(string);
		void setUrl(string, string);
		string Upload(string);
	private:
	};
}
#endif
