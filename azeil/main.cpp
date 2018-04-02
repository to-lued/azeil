#include <unistd.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "stampdb.h"
#include "wtCalculator.h"

int main() {
	auto database = StampDB::getInstance();
	database->open("/home/void/.stamping/database", true);

	/*
	 *        struct tm t1;
	 *        t1.tm_year = 118;
	 *        t1.tm_mon = 3;
	 *        t1.tm_mday = 2;
	 *        t1.tm_hour = 7;
	 *        t1.tm_min = 30;
	 *        t1.tm_sec = 0;
	 *
	 *        struct tm t2 = t1;
	 *        t2.tm_hour = 16;
	 *        t2.tm_min = 23;
	 *
	 *        StampEntry startentry;
	 *        startentry.type = STAMP_UNDEFINED;
	 *        startentry.timestamp =
	 * std::chrono::system_clock::from_time_t(mktime(&t1));
	 *        StampEntry stopentry;
	 *        stopentry.type = STAMP_UNDEFINED;
	 *        stopentry.timestamp =
	 * std::chrono::system_clock::from_time_t(mktime(&t2));
	 *
	 *        database->writeStampEntry(startentry);
	 *        database->writeStampEntry(stopentry);
	 */

	WTCalculator calc(database);
	auto result = calc.worktimeForMonth(std::chrono::system_clock::now());

	for (auto item : result) {
		auto dat = calc.toWTm(item.second);

		std::cout << "Worktime was:  " << dat.hours << ":"
			  << dat.minutes << ":" << dat.seconds << std::endl;
	}

	return 0;
}
