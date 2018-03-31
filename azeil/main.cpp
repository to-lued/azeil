#include <chrono>
#include <thread>
#include <iostream>
#include "stampdb.h"
#include <unistd.h>

int main() {
	auto wrapper = StampDB::getInstance();
	wrapper->open("testing.db", true);
	if(!wrapper->isOpen())return -1;

	wrapper->stamp(STAMP_START);
	sleep(5);
	wrapper->stamp(STAMP_STOP);

	return 0;
}
