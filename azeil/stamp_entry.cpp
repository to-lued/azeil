#include "stamp_entry.h"
using namespace stamp;
StampEntry::StampEntry(StampType type)
    : timestamp_(std::chrono::system_clock::now()), type_(type) {}
StampEntry::StampEntry(std::chrono::system_clock::time_point timestamp,
		       StampType type)
    : timestamp_(timestamp), type_(type) {}

std::chrono::system_clock::time_point StampEntry::timestamp() {
	return timestamp_;
}
void StampEntry::timestamp(std::chrono::system_clock::time_point timestamp) {
	timestamp_ = timestamp;
}
StampType StampEntry::type() { return type_; }
void StampEntry::type(StampType type) { type_ = type; }
