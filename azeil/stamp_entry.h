#ifndef STAMP_ENTRY
#define STAMP_ENTRY

#include <cstdint>
#include <chrono>
#include <memory>

namespace stamp {

typedef enum StampType { start, end } StampType;

class Entry {
       public:
	Entry(StampType type);
	Entry(std::chrono::system_clock::time_point timestamp, StampType type);

	std::chrono::system_clock::time_point timestamp();
	void timestamp(std::chrono::system_clock::time_point timestamp);

	StampType type();
	void type(StampType type);

       private:
	std::chrono::system_clock::time_point timestamp_;
	StampType type_;
};

typedef std::shared_ptr<Entry> EntryPtr;
}

#endif
