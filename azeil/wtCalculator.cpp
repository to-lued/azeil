#include "wtCalculator.h"
#include <time.h>
#include <ctime>
#include <iostream>

std::vector<std::pair<tp, std::chrono::seconds>> WTCalculator::worktimeForMonth(
    tp anchor) {
	std::vector<std::pair<tp, std::chrono::seconds>> worktimes;
	auto range = getRange(anchor, RANGE_MONTH);

	auto beg = range.beg;
	while (beg != range.end) {
		time_t beg_t = std::chrono::system_clock::to_time_t(beg);
		struct tm beg_tm = *std::localtime(&beg_t);
		std::chrono::seconds wtime = worktimeForDay(beg);

		worktimes.push_back(
		    std::pair<tp, std::chrono::seconds>(beg, wtime));

		beg_tm.tm_mday += 1;
		beg = std::chrono::system_clock::from_time_t(mktime(&beg_tm));
	}

	return worktimes;
}
std::chrono::seconds WTCalculator::worktimeForDay(tp anchor) {
	auto wtime = totalOf(anchor, WTWorkTime);
	auto otime = totalOf(anchor, WTOffTime);

	auto sub = std::chrono::seconds(0);
	if (wtime >= std::chrono::hours(6)) sub += std::chrono::minutes(30);
	if (wtime >= std::chrono::hours(9)) sub += std::chrono::minutes(15);

	otime -= sub;
	if (otime.count() < 0) wtime += otime;

	return wtime;
}
std::chrono::seconds WTCalculator::totalOf(tp anchor, WTCalcType type) {
	auto range = getRange(std::chrono::system_clock::now(), RANGE_DAY);
	auto entrys = database_->readStampEntrys(range.beg, range.end);
	std::chrono::seconds cumulated_worktime(0);
	std::chrono::seconds cumulated_offtime(0);

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
	return std::chrono::seconds(0);
}
std::vector<tp> WTCalculator::getWorkDays(tp anchor) {
	std::vector<tp> days;
	return days;
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

	if (type == RANGE_DAY) {
		end.tm_sec = 59;
		end.tm_min = 59;
		end.tm_hour = 23;
	}
	if (type == RANGE_MONTH) {
		end.tm_sec = 0;
		end.tm_min = 0;
		end.tm_hour = 0;
		end.tm_mday = getDaysInMonth(anchor);
	}

	WTRange range;
	range.beg = std::chrono::system_clock::from_time_t(mktime(&start));
	range.end = std::chrono::system_clock::from_time_t(mktime(&end));

	return range;
}
int WTCalculator::getDaysInMonth(tp anchor) {
	return getDaysInMonth(std::chrono::system_clock::to_time_t(anchor));
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
WTCalculator::WTm WTCalculator::toWTm(std::chrono::seconds dat) {
	WTm t1;
	t1.seconds = dat.count() % 60;
	t1.minutes = (dat.count() / 60) % 60;
	t1.hours = (dat.count() / 60) / 60;
	return t1;
}
