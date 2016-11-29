#include "Entry.hpp"

Entry::Entry(Account* accoumt. Type type, Amount amount)
	: _account(account), _type(type), _amount(amount) { }

bool Entry::tryApply() const {
	return _account->tryProcess(_type, _amount);
}
bool Entry::apply(){
	return _account->process(_type, _amount);
}

Type Entry::getType() const {
	return _type;
}

Amount Entry::getAmount() const {
	return _amount;
}

std::string Entry::getAccountName() const {
	return _account->getName();
}

void Entry::print(std::ostream &os) const {
	if(_type == Type::Credit) {
		os << "\t";
	}
	os << this->geAccountName() << "\t" << toString(this->getAmount()) << std::endl;
}
