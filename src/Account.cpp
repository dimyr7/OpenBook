#include "Account.hpp"

Account::Account(const std::string &name, AccountType type)
	: _name(name), _type(type), _amount(0., balanceSideDict[type]),
	_tempAmount(0., balanceSideDict[type]){ }


void Account::process(const Amount &amount){
	try {
		_tempAmount = _amount;
		_amount+= amount;
	} catch(const std::exception &e) {
		std::cout << e.what() << std::endl;
		throw e;
	}
}

void Account::reverse() noexcept{
	_amount = _tempAmount;
}

std::string Account::getName() const noexcept{
	return _name;
}

AccountType Account::getType() const noexcept{
	return _type;
}

double Account::getAmount() const noexcept{
	return _amount.getValue();
}


std::ostream& operator<<(std::ostream &os, const Account &acct) noexcept{
	os << acct._name << " - " << (balanceSideDict[acct._type] == iDEBIT ? "Dr: " : "Cr: " ) << acct._amount;
	return os;
}
