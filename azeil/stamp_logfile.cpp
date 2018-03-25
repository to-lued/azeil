#include "stamp_logfile.h"

stamp::LogWriter::LogWriter(std::string path) : path_(path) {}
int32_t stamp::LogWriter::open() {
	out_.open(path_, std::ofstream::out | std::ofstream::app);
	if (!out_.is_open()) return -1;
	return 0;
}
