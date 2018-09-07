AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = $(DEPS_CFLAGS)

LIB_CXXFLAGS = $(CURLPP_CXXFLAGS) $(BOOST_CXXFLAGS)

# additional include paths necessary to compile the C++ library
AM_CXXFLAGS = -I$(top_srcdir)/src/include $(LIB_CXXFLAGS) -Wall -O0 -g3 -fmessage-length=0  @AM_CXXFLAGS@ -std=c++11

webpost_LDADD = $(DEPS_LIBS) $(CURLPP_LIBS) $(BOOST_LIBS) $(CURL_LIBS) $(PTHREAD_LIBS)

bin_PROGRAMS = webpost

webpost_SOURCES = \
	src/Color.cpp \
	src/DateTime.cpp \
	src/IniReader.cpp \
	src/Network.cpp \
	src/Strings.cpp \
	src/UdpClient.cpp \
	src/UdpDebug.cpp \
	src/WebClient.cpp \
	src/WebPost.cpp \
	src/include/Color.hpp \
	src/include/config.h \
	src/include/config.hpp \
	src/include/DateTime.hpp \
	src/include/IniReader.hpp \
	src/include/Network.hpp \
	src/include/Strings.hpp \
	src/include/UdpClient.hpp \
	src/include/UdpDebug.hpp \
	src/include/WebClient.hpp

dist_noinst_SCRIPTS = autogen.sh
