#include <chrono>
#include <thread>
#include "stamp_handler.h"
#include "stamp_logfile.h"

int main() {
	auto start = stamp::start_now();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	auto end = stamp::stop_now();

	stamp::LogWriter writer("/home/torben/test.txt");
	if (!writer.open()) {
		std::cout << "Failed to open log" << std::endl;
		return -1;
	}
	
	writer << start << end;
	
	return 0;
}
