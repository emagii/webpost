#if	!defined(__DATETIME_HPP)
#define	__DATETIME_HPP

#define	DATETIME_DEBUG	1

#include <iostream>
#include <cstring>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"	// Date/Time
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

/*
 * Ticks in C# vs Ticks in Linux
 *
 * Ticks is C# refer to the number of 100-nanosecond intervals that have elapsed since 12:00:00 midnight, January 1, 0001
 * which represents DateTime.MinValue. It does not include the number of ticks that are attributable to leap seconds.
 *
 * Ticks in Linux refer to the CONFIG_HZ value when configuring the Linux kernel
 * This is typically 100 for ARM and 1000 for x86
 *
 * The C# 100-nanosecond resolution corresponds to a CONFIG_HZ = 10000000.
 */

extern string GetTime(void);
extern string GetRawTime(void);
extern time_t getTicksSinceEpoch(void);

namespace EM_DateTime {

	enum TimeOption {
		Methusalem, // Start of Time = 1970-01-01 00:00:00
		SecondRes, // Get Time of Day with second resolution
		MinuteRes, // Get Time of Day with Minute Resolution (Second = Clear)
	};

	class DateTime {
	private:
		ptime Seconds;
		tm Now;
	public:
		time_t Ticks;

		DateTime(); // Gets TimeOfDay when initialized
		DateTime(time_t timestamp); // Gets TimeOfDay when initialized
		DateTime(TimeOption timeOpt); // Gets TimeOfDay with specified resolution
		DateTime(int Year, int Month, int Day, int Hour, int Minute, int Second);
		void Update(void); // Update TimeOfDay
		unsigned int UpTime(void);
		void Copy(DateTime *t);
		int getYear(void);
		int getMonth(void);
		int getDay(void);
		int getHour(void);
		int getMinute(void);
		int getSecond(void);
		long getTicksToTime(tm t);
		void getLocalTime(void);
		string DateString(void);
		string TimeOfDay(bool brackets);
		string MinValue(void);
		DateTime *StartOfTime(void);
		void AddDays(int i);
		void AddHours(int i);
		void AddMinutes(int i);
		void AddSeconds(int i);
		bool operator<(DateTime& other);
		bool operator<=(DateTime& other);
		bool operator>(DateTime& other);
		bool operator>=(DateTime& other);
		bool operator==(DateTime& other);
#if	defined(DATETIME_DEBUG)
		void VerifySec(void);
		void VerifyMin(void);
		void VerifyHour(void);
		void Verify(void);
	};
}

#endif
#endif
