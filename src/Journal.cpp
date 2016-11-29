#include "Journal.hpp"

Journal::Journal(size_t month, size_t year, Ledger* ledger)
	: _month(month), _year(year){ }


bool Journal::newTransaction(const std::time_t &dateTime, const std::string &note){
	Transaction* newTrans = new Transaction(dateTime
}
bool Journal::close(){
	// TODO print monthly report
}
