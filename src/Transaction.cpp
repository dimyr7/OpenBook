#include "Transaction.hpp"

Transaction::Transaction(const std::time_t &dateTime, const std::string &note)
	: _dateTime(dateTime), _note(note) { }

void Transaction::addEntry(Account* account, const Amount &amount){
	_entries.push_back({account, amount});
}
void Transaction::apply(){
	int sum = 0;
	std::cout << _dateTime << std::endl;
	// Making sure Dr = Cr
	for(auto it = _entries.begin(); it != _entries.end(); it++){
		if(it->getEntryType() == iDEBIT){
			sum += (it->getAmount() * 100);
		} else{
			sum -= (it->getAmount() * 100);
		}
	}
	if(sum != 0){
		throw std::logic_error("debits do not equal the credits");
	}
	for(auto it = _entries.begin(); it != _entries.end(); it++){
		try{
			it->apply();
		} catch(std::exception &e){
			for(auto is = _entries.begin(); is != it; is++){
				is->reverse();
			}
			break;
		}
	}

}
