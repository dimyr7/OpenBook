#include "Account.hpp"

Account::Account(const std::string &name, Type type, Amount initAmount)
	: _name(name), _type(type), _amount(initAmount){ }

bool Account::tryProcess(Type type, Amount amount) const {
	if(type == Type::Credit and _amount < amount) {
		return false;
	}
	return true;
}

bool Account::process(Type type, Amount amount){
	if(type == _type) {
		_amount += amount
	} else if(_amount < amount) {
		return false;
	} else {
		_amount -= amount;
	}
	return true;
}

std::string Account::getName() const {
	return _name;
}

Type Account::getType() const {
	return _type
}

Amount Account::getAmount() const {
	return _amount;
}

void Account::print(std::ostream &os) const {
	os << _name << " - ";
	if(Type == Type::Debit) {
		os << "Dr: ";
	} else {
		os << "Cr: ";
	}
	os << toString(_amount);
}
