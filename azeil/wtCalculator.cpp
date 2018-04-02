#include "wtCalculator.h"
#include <time.h>
#include <ctime>
#include <iostream>

std::chrono::duration<long, std::ratio<1, 1>> WTCalculator::worktimeToday() {
	auto wtime = totalOf(std::chrono::system_clock::now(), WTWorkTime);
	auto otime = totalOf(std::chrono::system_clock::now(), WTOffTime);
	std::cout << "Worktime: " << wtime.count() << std::endl;
	std::cout << "Offtime: " << otime.count() << std::endl;
	return wtime;
}
std::chrono::duration<long, std::ratio<1, 1>> WTCalculator::totalOf(
    tp anchor, WTCalcType type) {
	auto range = getRange(std::chrono::system_clock::now(), RANGE_DAY);
	auto entrys = database_->readStampEntrys(range.beg, range.end);
	std::chrono::seconds cumulated_worktime;
	std::chrono::seconds cumulated_offtime;

	enum StampingState { none, working, stopped };

	StampingState current_state = none;
	tp previous;

	for (auto item : entrys) {
		if (current_state == none || current_state == stopped) {
			if (item.type == STAMP_STOP) {
				throw InconsistencyException();
			}
			if (current_state == stopped) {
				cumulated_offtime += std::chrono::duration_cast<
				    std::chrono::seconds>(item.timestamp -
							  previous);
			}
			current_state = working;
			previous = item.timestamp;
		} else {
			if (item.type == STAMP_START) {
				throw InconsistencyException();
			}
			cumulated_worktime +=
			    std::chrono::duration_cast<std::chrono::seconds>(
				item.timestamp - previous);
			current_state = stopped;
			previous = item.timestamp;
		}
	}
	if (current_state == working) throw InconsistencyException();

	if (type == WTOffTime)
		return cumulated_offtime;
	else if (type == WTWorkTime)
		return cumulated_worktime;
}
WTCalculator::WTRange WTCalculator::getRange(tp anchor, RANGEDEF type) {
	time_t time = std::chrono::system_clock::to_time_t(anchor);
	return getRange(time, type);
}
WTCalculator::WTRange WTCalculator::getRange(time_t anchor, RANGEDEF type) {
	auto start = *std::localtime(&anchor);
	auto end = *std::localtime(&anchor);

	start.tm_sec = 0;
	start.tm_min = 0;
	start.tm_hour = 0;
	if (type == RANGE_MONTH) start.tm_mday = 1;

	end.tm_sec = 59;
	end.tm_min = 59;
	end.tm_hour = 23;
	if (type == RANGE_MONTH) end.tm_mday = getDaysInMonth(anchor);

	WTRange range;
	range.beg = std::chrono::system_clock::from_time_t(mktime(&start));
	range.end = std::chrono::system_clock::from_time_t(mktime(&end));

	return range;
}
int WTCalculator::getDaysInMonth(time_t anchor) {
	auto data = *std::localtime(&anchor);
	auto year = 1900 + data.tm_year;
	bool isleapyear = false;

	if (year % 4 == 0) {
		if (year % 100 == 0) {
			if (year % 400 == 0)
				isleapyear = true;
			else
				isleapyear = false;
		} else
			isleapyear = true;
	}

	switch (data.tm_mon) {
		case 2:
			return isleapyear ? 29 : 28;
		case 0:
		case 4:
		case 6:
		case 7:
		case 9:
		case 11:
			return 31;
		case 1:
		case 3:
		case 5:
		case 8:
		case 10:
			return 30;
	}
	return 31;
}
