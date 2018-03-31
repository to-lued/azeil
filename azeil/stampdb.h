#ifndef STAMPDB
#define STAMPDB
#include <string>
#include "sqlite3.h"
typedef enum { STAMP_START, STAMP_STOP = 1 } STAMP_TYPE;
class StampDB {
       public:
	static StampDB* getInstance() {
		static StampDB instance;
		return &instance;
	}
	bool open(std::string filepath, bool initialize=false);
	bool initialize();
	bool isOpen() { return isopen_; }
	bool stamp(STAMP_TYPE type);
	

       private:
	StampDB() {
		isopen_ = false; }
	~StampDB() {
		if (isopen_) sqlite3_close(database_);
	}
	bool executeNoAnswer(std::string sqlcommand);
	//Vars
	sqlite3* database_;
	bool isopen_;
};
#endif
