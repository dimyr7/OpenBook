#include "Account.hpp"
#include <map>

const std::map<AccountType, EntryType> iBALANCE_SIDE_DICT = {
	{AccountType::Asset, iDEBIT},
	{AccountType::Liability, iCREDIT},
	{AccountType::Equity, iCREDIT},
	{AccountType::Revenue, iCREDIT},
	{AccountType::Expense, iDEBIT}
};

Account::Account(const std::string &name, const AccountType type, size_t id)
	: _name(name), _type(type), _id(id),
	_amount(0., iBALANCE_SIDE_DICT.at(type)),
	_tempAmount(0., iBALANCE_SIDE_DICT.at(type)){ }


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

size_t Account::getNumber() const noexcept{
	return _id;
}

double Account::getAmount() const noexcept{
	return _amount.getValue();
}


std::ostream& operator<<(std::ostream &os, const Account &acct) noexcept{
	os << acct._name << " - " << (iBALANCE_SIDE_DICT.at(acct._type) == iDEBIT ? "Dr: " : "Cr: " ) << acct._amount;
	return os;
}
