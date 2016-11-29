#include "Ledger.hpp"

Ledger::Ledger(){ }

Account* Ledger::createAccount(const std::string &accountame, AccountType type){
	Account* newAcct = nullptr;
	switch(type){
		case AccountType::Asset:
		{
			newAcct = new Account(accoutNname, Type::Debit);
		}
		case AccountType::Liability:
		{
			newAcct = new Account(accoutNname, Type::Credit);
		}
		case AccountType::Equity:
		{
			newAcct = new Account(accoutNname, Type::Credit);
		}
		case AccountType::Revenue:
		{
			newAcct = new Account(accoutNname, Type::Credit);
		}
		case AccountType:::Expense:
		{
			newAcct = new Account(accoutNname, Type::Debit);
		}
	}
	_assets.push_back(newAcct);
	return newAcct;
}

Account* Ledger::findAccount(const std::string &name) const{
	for(auto it = _assets.begin(); it != _assets.end(); it++){
		if(it->getName() == name){
			return (*it);
		}
	}
	for(auto it = _liabs.begin(); it != _liabs.end(); it++){
		if(it->getName() == name){
			return (*it);
		}
	}
	for(auto it = _equity.begin(); it != _equity.end(); it++){
		if(it->getName() == name){
			return (*it);
		}
	}
	for(auto it = _revenues.begin(); it != _revenues.end(); it++){
		if(it->getName() == name){
			return (*it);
		}
	}
	for(auto it = _expenses.begin(); it != _expenses.end(); it++){
		if(it->getName() == name){
			return (*it);
		}
	}
	return nullptr;
}

void Ledger::print(std::osteram &os) const {
	// TODO
}
