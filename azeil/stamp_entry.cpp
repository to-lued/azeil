#include "stamp_entry.h"
using namespace stamp;
Entry::Entry(StampType type)
    : timestamp_(std::chrono::system_clock::now()), type_(type) {}
Entry::Entry(std::chrono::system_clock::time_point timestamp,
		       StampType type)
    : timestamp_(timestamp), type_(type) {}

std::chrono::system_clock::time_point Entry::timestamp() {
	return timestamp_;
}
void Entry::timestamp(std::chrono::system_clock::time_point timestamp) {
	timestamp_ = timestamp;
}
StampType Entry::type() { return type_; }
void Entry::type(StampType type) { type_ = type; }
