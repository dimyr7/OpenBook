#include "Transaction.hpp"

Transaction::Transaction(const std::time_t &dateTime, const std::string &note)
	: _dateTime(dateTime), _note(note) { }

void Transaction::addDebit(Account* account, Amount amount){
	_debits.pushBack{account, Type::Debit, amount};
}
void Transaction::addCredit(Account* account, Amount amount){
	_debits.pushBack{account, Type::Credit, amount};
}
bool Transactions::apply(){
	for(auto it = _debits.begin(); it != _debits.end(); it++){
		if(not it->tryApply()){
			return false;
		}
	}
	for(auto it = _credits.begin(); it != _credits.end(); it++){
		if(not it->tryApply()){
			return false;
		}
	}
	for(auto it = _debits.begin(); it != _debits.end(); it++){
		it->apply();
	}
	for(auto it = _credits.begin(); it != _credits.end(); it++){
		it->apply();
	}

	return true;
}
