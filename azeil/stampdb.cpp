#include "stampdb.h"
#include <chrono>
#include <unistd.h>

bool StampDB::open(std::string filepath, bool initialize) {
	int result = sqlite3_open_v2(filepath.c_str(), &database_,
				     SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
				     nullptr);
	if (result != 0) return false;
	isopen_ = true;
	if (initialize) this->initialize();
	return true;
}
bool StampDB::executeNoAnswer(std::string sqlcommand) {
	sqlite3_stmt* statement;
	int result = sqlite3_prepare_v2(database_, sqlcommand.c_str(), -1,
					&statement, nullptr);
	if (result != SQLITE_OK) return false;
	result = sqlite3_step(statement);
	sqlite3_finalize(statement);
	if (result < SQLITE_DONE) return false;
	return true;
}
bool StampDB::initialize() {
	return executeNoAnswer(
	    "CREATE TABLE IF NOT EXISTS stamps (stamp_type INT, stamp_time INT "
	    "PRIMARY KEY)");
}
bool StampDB::stamp(STAMP_TYPE type) {
	sqlite3_stmt* statement;
	int result = sqlite3_prepare_v2(
	    database_,
	    "INSERT INTO stamps (stamp_type, stamp_time) VALUES( ?1 , ?2 )",
	    -1, &statement, nullptr);
	if (result != SQLITE_OK) return false;

	result = sqlite3_bind_int(statement, 1, static_cast<int>(type));
	if (result != SQLITE_OK) {
		sqlite3_finalize(statement);
		return false;
	}

	auto now = std::chrono::system_clock::now();
	auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch();
	int seconds_int = seconds.count();

	result = sqlite3_bind_int(statement, 2, seconds_int);
	if (result != SQLITE_OK) {
		sqlite3_finalize(statement);
		return false;
	}

	result = sqlite3_step(statement);	
	bool retval = false;
	if(result == SQLITE_DONE) retval = true;
	sqlite3_finalize(statement);
	return retval;
}
