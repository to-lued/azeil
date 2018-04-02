#ifndef WTIMECALCULATOR
#define WTIMECALCULATOR
#include <chrono>
#include <exception>
#include "stampdb.h"
class InconsistencyException : public std::exception {
	const char *what() const throw() {
		return "inconsistency in workday detected!";
	}
};
class WTCalculator {
       public:
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

	std::chrono::duration<long, std::ratio<1, 1>> worktimeToday();
	std::chrono::duration<long, std::ratio<1, 1>> totalOf(tp anchor, WTCalcType type);

       private:
	typedef enum { RANGE_DAY, RANGE_MONTH } RANGEDEF;
	StampDB *database_;

	WTRange getRange(tp anchor, RANGEDEF);
	WTRange getRange(time_t anchor, RANGEDEF);
	int getDaysInMonth(time_t anchor);
};
#endif
