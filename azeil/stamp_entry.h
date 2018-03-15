#ifndef STAMP_ENTRY
#define STAMP_ENTRY

#include <cstdint>
#include <chrono>

namespace stamp {

typedef enum StampType { start, end } StampType;

class StampEntry {
       public:
	StampEntry(StampType type);
	StampEntry(std::chrono::system_clock::time_point timestamp, StampType type);

	std::chrono::system_clock::time_point timestamp();
	void timestamp(std::chrono::system_clock::time_point timestamp);

	StampType type();
	void type(StampType type);

       private:
	std::chrono::system_clock::time_point timestamp_;
	StampType type_;
};
}

#endif
