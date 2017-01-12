#include "Ledger.hpp"

#include <iostream>
#include <string>

Ledger::Ledger(rapidjson::Document &acctDoc) {
	if(not acctDoc.IsObject()){
		throw std::logic_error("Ledger file is not a valid JSON");
	}
	for(auto it = Account::iACCT_TYPE_STRING_DICT.cbegin();
			it != Account::iACCT_TYPE_STRING_DICT.cend(); it++){
		const char* acctTypeStr = it->second.c_str();
		if(not acctDoc.HasMember(acctTypeStr)) {
			throw std::logic_error("Ledger file doesn't have all types of accounts");
		} else if(not acctDoc[acctTypeStr].IsArray()) {
			throw std::logic_error("Each type of account must be listed in array form");
		} else if(acctDoc[acctTypeStr].Size() < 1) {
			throw std::logic_error("There must be at least 1 account for each type");
		}

		for(rapidjson::SizeType i = 0; i < acctDoc[acctTypeStr].Size(); i++){
			auto& acctInfo = acctDoc[acctTypeStr].GetArray()[i];
			if(not acctInfo.HasMember("name")){
				throw std::logic_error("Each account must have a name");
			} else if(not acctInfo.HasMember("number")) {
				throw std::logic_error("Each account must have a number");
			}
			Account* newAcct = new Account(acctInfo["name"].GetString(),
					it->first, acctInfo["number"].GetInt());
			_accounts[it->first].push_back(newAcct);
		}
	}
}

Ledger::~Ledger() noexcept {
	for(auto it = _accounts.begin(); it != _accounts.end(); it++){
		for(auto is = it->second.begin(); is != it->second.end(); is++){
			delete (*is);
		}
	}
}


Account* Ledger::findAccount(const std::string &name) const{
	try{
		size_t acctNumber = std::stoi(name);
		Account* ret = this->findAccount(acctNumber);
		return ret;
	} catch(const std::invalid_argument &e) {
		// A number was not entered
		for(auto it = _accounts.begin(); it != _accounts.end(); it++){
			for(auto is = it->second.begin(); is != it->second.end(); it++){
				if((*is)->getName() == name){
					return (*is);
				}
			}
		}
	}
	catch(const std::logic_error &e) {
		// A number was enterered but it is illogical
		throw e;
	}
	return nullptr;
}

Account* Ledger::findAccount(size_t acctNumber) const {
	int acctTypeCode = 0;
	AccountType type;
	acctTypeCode = Ledger::getAcctType(acctNumber);
	std::cout << acctTypeCode << std::endl;
	try{
		type = Account::iCODE_ACCT_TYPE_DICT.at(acctTypeCode);
	} catch(std::exception &e) {
		throw std::logic_error("Incorrect account number");
	}
	for(auto it = _accounts.at(type).begin(); it != _accounts.at(type).end(); it++){
		if((*it)->getNumber() == acctNumber){
			return (*it);
		}
	}
	return nullptr;
}


void Ledger::printReports(std::ostream &os) const noexcept{
	for(auto it = _accounts.begin(); it != _accounts.end(); it++){
		os << "=== " << Account::iACCT_TYPE_STRING_DICT.at(it->first) << std::endl;
		for(auto is = it->second.begin(); is != it->second.end(); is++){
			os << *(*is) << std::endl;
		}
	}
}


size_t Ledger::getAcctType(size_t acctNumber) noexcept {
	while(acctNumber > 9) {
		acctNumber/= 10;
	}
	return acctNumber;
}

void Ledger::close(){ }
