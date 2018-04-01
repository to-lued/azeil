#ifndef WTIMECALCULATOR
#define WTIMECALCULATOR
#include "stampdb.h"
#include <chrono>
class WTCalculator{
	public:
		typedef struct WTRange {
			tp beg;
			tp end;
		} WTRange;
		WTCalculator(StampDB *database) : database_(database){}
		~WTCalculator(){}
		
		void worktimeToday();

	private:
		typedef enum { RANGE_DAY, RANGE_MONTH } RANGEDEF;
		StampDB *database_;

		WTRange getRange(tp anchor, RANGEDEF);
		
};
#endif
