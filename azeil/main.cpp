#include <unistd.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "wtCalculator.h"
#include "stampdb.h"

int main() {
	auto database = StampDB::getInstance();
	database->open("/home/void/.stamping/database", true);

	WTCalculator calc(database);
	calc.worktimeToday();

	return 0;
}
