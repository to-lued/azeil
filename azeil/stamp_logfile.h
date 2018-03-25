#ifndef STAMP_LOGFILE
#define STAMP_LOGFILE
#include <fstream>
#include <string>
#include "stamp_entry.h"

namespace stamp {
class LogWriter : public std::basic_ostream{
       public:
	LogWriter(std::string path);
	~LogWriter();

	int32_t open();
	friend std::ostream& operator<<(std::ostream& strm,
					const EntryPtr& entry) {
		strm << "Es klappt" << std::endl;
		return strm;
	}
	friend std::ostream& operator<<(std::ostream& strm,
					const LogWriter& writer) {
		strm << "writer" << std::endl;
		return strm;
	}

       private:
	std::ofstream out_;
	std::string path_;
};
class LogReader {
       public:
	LogReader(std::string path);
	~LogReader();

       private:
};
}
#endif
