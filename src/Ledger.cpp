#include "Ledger.hpp"
#include <iostream>

Ledger::Ledger(){ }

Account* Ledger::createAccount(const std::string &accountName, AccountType type){
	Account* newAcct = new Account(accountName, type);
	_accounts[type].push_back(newAcct);
	return newAcct;
}

Account* Ledger::findAccount(const std::string &name) const{
	for(auto it = _accounts.begin(); it != _accounts.end(); it++){
		for(auto is = it->second.begin(); is != it->second.end(); it++){
			if((*is)->getName() == name){
				return (*is);
			}
		}
	}
	return nullptr;
}

void Ledger::print(std::ostream &os) const {
	// TODO
}
