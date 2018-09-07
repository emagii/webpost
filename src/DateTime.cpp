/*
 * DateTime.cpp
 *
 *  Created on: 29 sep 2013
 *      Author: ulf
 */
#include <iostream>
#include <cstring>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"	// Date/Time
#include "boost/date_time/posix_time/posix_time.hpp"
#include <ctime>
#include <cassert>
#include "DateTime.hpp"
#include "Strings.hpp"

using namespace std;
using namespace EM_DateTime;

DateTime Start_Date(1970, 1, 1, 0, 0, 0);
ptime Epoch(date(1900,Jan,1));

DateTime::DateTime() {
	Seconds = second_clock::local_time();
	Now = to_tm(Seconds);
	Ticks = getTicksToTime(Now);
}

DateTime::DateTime(TimeOption to) {

	if (to == Methusalem) {
		Seconds = Epoch;
		Now.tm_year = 0;
		Now.tm_mon = 0;
		Now.tm_mday = 0;
		Now.tm_hour = 0;
		Now.tm_min = 0;
		Now.tm_sec = 0;
		Ticks = 0;
	} else {
		Seconds = second_clock::local_time();
		Now = to_tm(Seconds);
		if (to == MinuteRes) {
			Now.tm_sec = 0;
		}
		Ticks = getTicksToTime(Now);
	}
}

DateTime::DateTime(int Year, int Month, int Day, int Hour, int Minute,
		int Second) {
	Now.tm_year = Year - 1900;
	Now.tm_mon = Month - 1;
	Now.tm_mday = Day;
	Now.tm_hour = Hour;
	Now.tm_min = Minute;
	Now.tm_sec = Second;
	Ticks = getTicksToTime(Now);
	// TODO: 100 Calculate real seconds
	Seconds = Epoch;
}

DateTime::DateTime(time_t timestamp) {	// Seconds since Epoch
	struct tm * t = gmtime (&timestamp);
	Now.tm_year = t->tm_year;
	Now.tm_mon = t->tm_mon;
	Now.tm_mday = t->tm_mday;
	Now.tm_hour = t->tm_hour;
	Now.tm_min = t->tm_min;
	Now.tm_sec = t->tm_sec;
	Ticks = timestamp;
	// TODO: 100 Calculate real seconds
	Seconds = Epoch;
}

void DateTime::Update(void) {
	Seconds = second_clock::local_time();
	Now = to_tm(Seconds);
	Ticks = getTicksToTime(Now);
}

unsigned int DateTime::UpTime(void) {
	/* The time since this DateTime was created */
	ptime current_time = second_clock::local_time();
	time_duration uptime = current_time - Seconds;
	return uptime.total_seconds();
}

time_t getTicksSinceEpoch(void) {	// Seconds since Epoch
	long ticks;
	ptime time_t_epoch(date(1970, 1, 1));
	ptime now = microsec_clock::local_time();
	time_duration diff = now - time_t_epoch;

#if	0
	ticks = diff.total_milliseconds();

	assert((CLOCKS_PER_SEC == 100) | (CLOCKS_PER_SEC == 1000));

	if (CLOCKS_PER_SEC == 100) {
		ticks = ticks / 10;
	}
#endif
	ticks = diff.total_seconds();
	return ticks;
}

long DateTime::getTicksToTime(tm t) {
	long ticks;
	ptime time_t_epoch(date(1970, 1, 1));
	ptime pt = ptime_from_tm(t);

	time_duration diff = pt - time_t_epoch;
#if	0
	ticks = diff.total_milliseconds();

	assert((CLOCKS_PER_SEC == 100) | (CLOCKS_PER_SEC == 1000));

	if (CLOCKS_PER_SEC == 100) {
		ticks = ticks / 10;
	}
#endif
	ticks = diff.total_seconds();
	return ticks;
}

void DateTime::Copy(DateTime *t) {
	Now.tm_year = t->Now.tm_year;
	Now.tm_mon = t->Now.tm_mon;
	Now.tm_mday = t->Now.tm_mday;
	Now.tm_hour = t->Now.tm_hour;
	Now.tm_min = t->Now.tm_min;
	Now.tm_sec = t->Now.tm_sec;
}

int DateTime::getYear(void) {
	return Now.tm_year + 1900;

}

int DateTime::getMonth(void) {
	return Now.tm_mon + 1;
}

int DateTime::getDay(void) {
	return Now.tm_mday;
}

int DateTime::getHour(void) {
	return Now.tm_hour;

}

int DateTime::getMinute(void) {
	return Now.tm_min;
}

int DateTime::getSecond(void) {
	return Now.tm_sec;
}

void DateTime::getLocalTime(void) {
	Now = to_tm(second_clock::local_time());
}

string DateTime::DateString(void) {
	string image;
	string adder;
	int year, month, day, hour, minute, second;

	year = Now.tm_year + 1900;
	//TODO: 100: DateTime.cpp cannot use to_string for some reason.
	image.append(/* _str. */ito_string(year) + "-");

	month = Now.tm_mon + 1;
	if (month < 10)
		image.append("0");
	image.append(/* _str. */ito_string(month) + "-");

	day = Now.tm_mday;
	if (day < 10)
		image.append("0");
	image.append(/* _str. */ito_string(day) + " ");

	hour = Now.tm_hour;
	if (hour < 10)
		image.append("0");
	image.append(/* _str. */ito_string(hour) + ":");

	minute = Now.tm_min;
	if (minute < 10)
		image.append("0");
	image.append(/* _str. */ito_string(minute) + ":");

	second = Now.tm_sec;
	if (second < 10)
		image.append("0");
	image.append(/* _str. */ito_string(second));
	return image;
}

string DateTime::TimeOfDay(bool brackets) {
	tm ToD = to_tm(second_clock::local_time());
	string image;
	string adder;
	int year, month, day, hour, minute, second;

	if (brackets) {
		image.append("[");
	}
	year = ToD.tm_year + 1900;
	//TODO: 100: DateTime.cpp cannot use to_string for some reason.
	image.append(/* _str. */ito_string(year) + "-");

	month = ToD.tm_mon + 1;
	if (month < 10)
		image.append("0");
	image.append(/* _str. */ito_string(month) + "-");

	day = ToD.tm_mday;
	if (day < 10)
		image.append("0");
	image.append(/* _str. */ito_string(day) + " ");

	hour = ToD.tm_hour;
	if (hour < 10)
		image.append("0");
	image.append(/* _str. */ito_string(hour) + ":");

	minute = ToD.tm_min;
	if (minute < 10)
		image.append("0");
	image.append(/* _str. */ito_string(minute) + ":");

	second = ToD.tm_sec;
	if (second < 10)
		image.append("0");
	image.append(/* _str. */ito_string(second));
	if (brackets) {
		image.append("]");
	}
	return image;

}

#if	0
string DateTime::MinValue(void) {
	//TODO: 999; Remove DateTime::MinValue
	string str_today = "1970-01-01 00:00:00";
	return str_today;
}
#endif

DateTime *DateTime::StartOfTime(void) {
	return &Start_Date;
}

void DateTime::AddDays(int i) {
	Now = to_tm(ptime_from_tm(Now) + days(i));
}

void DateTime::AddHours(int i) {
	Now = to_tm(ptime_from_tm(Now) + hours(i));
}

void DateTime::AddMinutes(int i) {
	Now = to_tm(ptime_from_tm(Now) + minutes(i));
}

void DateTime::AddSeconds(int i) {
	Now = to_tm(ptime_from_tm(Now) + seconds(i));
}

bool DateTime::operator<(DateTime& other) {
	//NOTE: 100: Verify DateTime operator "<"
	return (ptime_from_tm(Now) < ptime_from_tm(other.Now));
}

bool DateTime::operator<=(DateTime& other) {
	//NOTE: 100: Verify DateTime operator "<="
	return ptime_from_tm(Now) <= ptime_from_tm(other.Now);
}

bool DateTime::operator>(DateTime& other) {
	//NOTE: 100: Verify DateTime operator ">"
	return ptime_from_tm(Now) > ptime_from_tm(other.Now);
}

bool DateTime::operator>=(DateTime& other) {
	//NOTE: 100: Verify DateTime operator ">="
	return ptime_from_tm(Now) >= ptime_from_tm(other.Now);
}

bool DateTime::operator==(DateTime& other) {
	//NOTE: 100: Verify DateTime operator "=="
	return ptime_from_tm(Now) == ptime_from_tm(other.Now);
}

#if	defined(DATETIME_DEBUG)
void DateTime::VerifySec(void)
{
	cout << DateString() << " + 1 second => ";
	AddSeconds(1);
	cout << DateString() << endl;
}

void DateTime::VerifyMin(void)
{
	cout << DateString() << " + 1 minute => ";
	AddMinutes(1);
	cout << DateString() << endl;
}

void DateTime::VerifyHour(void)
{
	cout << DateString() << " + 1 hour   => ";
	AddHours(1);
	cout << DateString() << endl;
}

void DateTime::Verify(void)
{
	VerifySec();
	VerifyMin();
	VerifyHour();
}
#endif
// ****** Not in the Class !!!!

/* Get number of seconds since 1970-01-01 00:00 */
string GetTime(void) {
	time_t	now = getTicksSinceEpoch();
	return ito_string((long) now);
}

/* Get number of seconds since 1970-01-01 00:00 as a string of 4 bytes*/
string GetRawTime(void) {
	time_t lticks = getTicksSinceEpoch();
	unsigned int ticks = lticks & 0xFFFFFFFF;
	string result;
	result.resize(4, 0);
	result[0] = ticks & 0xFF;
	ticks >>= 8;
	result[1] = ticks & 0xFF;
	ticks >>= 8;
	result[2] = ticks & 0xFF;
	ticks >>= 8;
	result[3] = ticks & 0xFF;
	return result;
}
