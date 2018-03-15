#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "stamp_entry.h"

namespace stamp {
typedef std::shared_ptr<StampEntry> StampEntrySHP;

void print_something() { std::cout << "It works" << std::endl; }

/**! \brief get StampEntry with timepoint now and custom type
 */
StampEntrySHP now(StampType type) {
	StampEntrySHP entry = std::make_shared<StampEntry>(type);
	return entry;
}
/**! \brief get StampEntry with timepoint now and type start
 */
StampEntrySHP start_now() { return now(StampType::start); }
/**! \brief get StampEntry with timepoint now and type end
 */
StampEntrySHP stop_now() { return now(StampType::end); }
/**! \brief simple to string method
 */
std::string toString(StampEntrySHP entry) {
	std::time_t t =
	    std::chrono::system_clock::to_time_t(entry->timestamp());
	std::stringstream strm;
	strm << std::ctime(&t);
	return strm.str();
}
}
