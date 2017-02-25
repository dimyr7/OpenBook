#include "Account.hpp"

const std::map<AccountType, EntryType> Account::iACCT_TYPE_BALANCE_SIDE_DICT = {
	{AccountType::Asset, iDEBIT},
	{AccountType::Liability, iCREDIT},
	{AccountType::Equity, iCREDIT},
	{AccountType::Revenue, iCREDIT},
	{AccountType::Expense, iDEBIT}
};

const std::map<AccountType, std::string> Account::iACCT_TYPE_STRING_DICT = {
	{AccountType::Asset, "asset"},
	{AccountType::Liability, "liability"},
	{AccountType::Equity, "equity"},
	{AccountType::Revenue, "revenue"},
	{AccountType::Expense, "expense"}
};

const std::map<size_t, AccountType> Account::iCODE_ACCT_TYPE_DICT= {
	{1, AccountType::Asset},
	{2, AccountType::Liability},
	{3, AccountType::Equity},
	{4, AccountType::Revenue},
	{5, AccountType::Expense}
};

Account::Account(const std::string &name, const AccountType type, size_t id, double amount)
	: _name(name), _type(type), _id(id),
	_amount(amount, iACCT_TYPE_BALANCE_SIDE_DICT.at(type)),
	_tempAmount(amount, iACCT_TYPE_BALANCE_SIDE_DICT.at(type)){ }


void Account::process(const Amount &amount){
	try {
		_tempAmount = _amount;
		_amount+= amount;
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
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

Amount Account::getAmount() const noexcept{
	return _amount;
}


std::ostream& operator<<(std::ostream &os, const Account &acct) noexcept{
	os << acct._name << " " << acct._amount;
	return os;
}
