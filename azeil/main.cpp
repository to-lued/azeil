#include <unistd.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "stampdb.h"

int main() {
	auto wrapper = StampDB::getInstance();
	wrapper->open("testing.db", true);
	if (!wrapper->isOpen()) return -1;

	auto start = std::chrono::system_clock::now() - std::chrono::hours(2);
	auto end = std::chrono::system_clock::now();

	auto res = wrapper->readstamps(start, end);

	for (auto item : res) {
		std::cout << "<" << item.type << ">"
			  << std::chrono::time_point_cast<std::chrono::seconds>(
				 item.timestamp)
				 .time_since_epoch()
				 .count()
			  << std::endl;
	}

	return 0;
}
