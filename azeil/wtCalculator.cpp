#include "wtCalculator.h"
#include <ctime>
#include <time.h>

void WTCalculator::worktimeToday(){
}
WTCalculator::WTRange WTCalculator::getRange(tp anchor, RANGEDEF type){

	auto today = std::chrono::system_clock::to_time_t(anchor);
	auto start = std::localtime(&today);
	auto end = std::localtime(&today);

	start->tm_sec = 0;
	start->tm_min = 0;
	start->tm_hour = 0;
	if(type == RANGE_MONTH)
		start->tm_mday = 0;

	end->tm_sec = 59;
	end->tm_min = 59;
	end->tm_hour = 23;
	if(type == RANGE_MONTH)
		end->tm_mday = 0;

	WTRange range;
	range.beg = std::chrono::system_clock::from_time_t(mktime(start));
	range.end = std::chrono::system_clock::from_time_t(mktime(end));

	return range;
}
