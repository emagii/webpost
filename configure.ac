AC_INIT([WebPost], [0.1], [ulf@emagii.com],
             [webpost-0.1], [http://www.emagii.com/])
AC_PREREQ([2.59])
AC_CONFIG_HEADERS([src/include/config.h])

# check if the source folder is available
AC_CONFIG_SRCDIR([src/WebPost.cpp])

: ${CXXFLAGS=""}
# check for C++ preprocessor and compiler
AC_PROG_CXXCPP
AC_PROG_CXX

AM_INIT_AUTOMAKE([1.10 -Wall no-define])

# use the C++ compiler for the following checks
AC_LANG([C++])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([iostream])
AC_CHECK_HEADERS([cstring])
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([list])
AC_CHECK_HEADERS([vector])
AC_CHECK_HEADERS([sstream])
AC_CHECK_HEADERS([boost/asio.hpp])
AC_CHECK_HEADERS([curl/curl.h])
AC_CHECK_HEADERS([curlpp/cURLpp.hpp])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# distribute additional compiler and linker flags among Makefiles
# --> set and change these variables instead of CXXFLAGS or LDFLAGS (for user only)
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

######### CurlPP ##############################################################
# Get CurlPP include locations
AC_ARG_WITH([curlpp-include-path],
  [AS_HELP_STRING([--with-curlpp-include-path],[location of the CurlPP headers, defaults to /usr/local/include])],
  [CURLPP_CXXFLAGS="-I$withval"],
  [CURLPP_CXXFLAGS='-I/usr/local/include'])
AC_SUBST([CURLPP_CXXFLAGS])

# Get CurlPP library locations
AC_ARG_WITH([curlpp-lib-path],
  [AS_HELP_STRING([--with-curlpp-lib-path], [location of the CurlPP libraries])],
  [CURLPP_LIBS="-L$withval -lcurlpp"],
  [CURLPP_LIBS='-L/usr/local/lib -lcurlpp'])
AC_SUBST([CURLPP_LIBS])

######### BOOST ###############################################################
# Get Boost library and include locations
AC_ARG_WITH([boost-include-path],
  [AS_HELP_STRING([--with-boost-include-path],
    [location of the Boost headers, defaults to /usr/include/boost])],
  [BOOST_CXXFLAGS="-I$withval"],
  [BOOST_CXXFLAGS='-I/usr/include/boost'])
AC_SUBST([BOOST_CXXFLAGS])

AC_ARG_WITH([boost-lib-path],
  [AS_HELP_STRING([--with-boost-lib-path], [location of the Boost libraries])],
  [BOOST_LIBS="-L$withval -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread"],
  [BOOST_LIBS='-L/usr/lib -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread -lpthread'])
AC_SUBST([BOOST_LIBS])

######### Curl ################################################################
# Get Curl library locations
AC_ARG_WITH([curl-lib-path],
  [AS_HELP_STRING([--with-curl-lib-path], [location of the cURL libraries])],
  [CURL_LIBS="-L$withval -lcurl"],
  [CURL_LIBS='-L/usr/lib -lcurl'])
AC_SUBST([CURL_LIBS])

######### Curl ################################################################
# Get pthread library locations
AC_ARG_WITH([pthread-lib-path],
  [AS_HELP_STRING([--with-pthread-lib-path], [location of the pthread libraries])],
  [PTHREAD_LIBS="-L$withval -lpthread"],
  [PTHREAD_LIBS='-L/usr/lib -lpthread'])
AC_SUBST([PTHREAD_LIBS])



AC_SUBST([CXXFLAGS])

AC_CONFIG_FILES([Makefile])
# AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT
