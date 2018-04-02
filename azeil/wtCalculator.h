#ifndef WTIMECALCULATOR
#define WTIMECALCULATOR
#include <chrono>
#include <exception>
#include <map>
#include "stampdb.h"
class InconsistencyException : public std::exception {
	const char *what() const throw() {
		return "inconsistency in workday detected!";
	}
};
class WTCalculator {
       public:
	typedef struct WTm{
		int32_t hours;
		int32_t minutes;
		int32_t seconds;
	} WTm;
	typedef struct WTRange {
		tp beg;
		tp end;
	} WTRange;
	typedef enum {
		WTWorkTime,
		WTOffTime
	} WTCalcType;
	WTCalculator(StampDB *database) : database_(database) {}
	~WTCalculator() {}

	std::vector<std::pair<tp, std::chrono::seconds>> worktimeForMonth(tp anchor);
	std::chrono::seconds worktimeForDay(tp anchor);
	std::chrono::seconds totalOf(tp anchor, WTCalcType type);
	WTm toWTm(std::chrono::seconds);

       private:
	typedef enum { RANGE_DAY, RANGE_MONTH } RANGEDEF;
	StampDB *database_;

	WTRange getRange(tp anchor, RANGEDEF);
	WTRange getRange(time_t anchor, RANGEDEF);
	std::vector<tp> getWorkDays(tp anchor);
	int getDaysInMonth(tp anchor);
	int getDaysInMonth(time_t anchor);
};
#endif
