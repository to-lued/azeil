#ifndef STAMPDB
#define STAMPDB
#include <chrono>
#include <string>
#include <vector>
#include "sqlite3.h"
typedef enum { STAMP_START, STAMP_STOP = 1, STAMP_UNDEFINED = 2 } STAMP_TYPE;
typedef std::chrono::system_clock::time_point tp;
typedef struct StampEntry{
	STAMP_TYPE type;
	tp timestamp;
} StampEntry;
class StampDB {
       public:
	static StampDB* getInstance() {
		static StampDB instance;
		return &instance;
	}
	bool open(std::string filepath, bool initialize = false);
	bool initialize();
	bool isOpen() { return isopen_; }
	bool stamp(STAMP_TYPE type = STAMP_UNDEFINED);
	std::vector<StampEntry> readstamps(tp from, tp to);

       private:
	StampDB() { isopen_ = false; }
	~StampDB() {
		if (isopen_) sqlite3_close(database_);
	}
	bool executeNoAnswer(std::string sqlcommand);
	// Vars
	sqlite3* database_;
	bool isopen_;
};
#endif
