#include "Ledger.hpp"

#include <iostream>
#include <string>

// TODO move these elsewhere
#define iASSETS "assets"
#define iLIABILITIES "liabilities"
#define iEQUITIES "equities"
#define iREVENUES "revenues"
#define iEXPENSES "expenses"

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
	AccountType type;
	int acctTypeCode = 0;
	// TODO clean up this code. there should not be a try block within a try block
	try{
		size_t acctNumber = std::stoi(name);
		acctTypeCode = std::stoi(name.substr(0,1));
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
	} catch(const std::exception &e) {
		// Ignore, try looking by account name
		for(auto it = _accounts.begin(); it != _accounts.end(); it++){
			for(auto is = it->second.begin(); is != it->second.end(); it++){
				if((*is)->getName() == name){
					return (*is);
				}
			}
		}
	}
	return nullptr;
}

Account* Ledger::findAccount(size_t acctNumber) const {
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

