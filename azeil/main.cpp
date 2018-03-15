#include "stamp_handler.cpp"
#include <thread>
#include <chrono>

int main() {
	auto start = stamp::start_now();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	auto end = stamp::stop_now();

	std::cout << "Start: " << stamp::toString(start) << std::endl;
	std::cout << "Stop: " << stamp::toString(end) << std::endl;
	return 0;
}
