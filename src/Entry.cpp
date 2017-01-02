#include "Entry.hpp"

Entry::Entry(Account* account, Amount amount)
	: _account(account), _amount(amount) { }

void Entry::apply(){
	try{
		_account->process(_amount);
	} catch(const std::exception &e){
		throw e;
	}
}

void Entry::reverse() noexcept{
	_account->reverse();
}

double Entry::getAmount() const noexcept {
	return _amount.getValue();
}

EntryType Entry::getEntryType() const noexcept{
	return _amount.getEntryType();
}

std::string Entry::getAccountName() const noexcept {
	return _account->getName();
}

std::ostream& operator<<(std::ostream &os, const Entry &entry) noexcept {
	if(entry._amount.getEntryType() == iCREDIT) {
		os << "\t";
	}
	os << entry.getAccountName() << "\t" << entry._amount;
	return os;
}
