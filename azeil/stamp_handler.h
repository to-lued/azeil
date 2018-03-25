#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "stamp_entry.h"

namespace stamp {

void print_something() { std::cout << "It works" << std::endl; }

/**! \brief get Entry with timepoint now and custom type
 */
EntryPtr now(StampType type) {
	EntryPtr entry = std::make_shared<Entry>(type);
	return entry;
}
/**! \brief get Entry with timepoint now and type start
 */
EntryPtr start_now() { return now(StampType::start); }
/**! \brief get Entry with timepoint now and type end
 */
EntryPtr stop_now() { return now(StampType::end); }
/**! \brief simple to string method
 */
std::string toString(EntryPtr entry) {
	std::time_t t =
	    std::chrono::system_clock::to_time_t(entry->timestamp());
	std::stringstream strm;
	strm << std::ctime(&t);
	return strm.str();
}
}
