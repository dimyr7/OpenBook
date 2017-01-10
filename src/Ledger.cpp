#include "Ledger.hpp"

#include <iostream>
#include <string>

// TODO move these elsewhere
#define iASSETS "assets"
#define iLIABILITIES "liabilities"
#define iEQUITIES "equities"
#define iREVENUES "revenues"
#define iEXPENSES "expenses"

Ledger::Ledger(rapidjson::Document &acctDoc){
	// Assets
	assert(acctDoc.IsObject());
	assert(acctDoc[iASSETS].IsArray());
	for(rapidjson::SizeType i = 0; i < acctDoc[iASSETS].Size(); i++){
		auto& acctInfo = acctDoc[iASSETS].GetArray()[i];
		assert(acctInfo.HasMember("name"));
		assert(acctInfo.HasMember("number"));
		Account* newAcct = new Account(acctInfo["name"].GetString(), AccountType::Asset, acctInfo["number"].GetInt());
		_accounts[AccountType::Asset].push_back(newAcct);
	}
	// Liabilities
	assert(acctDoc.HasMember(iLIABILITIES));
	assert(acctDoc[iLIABILITIES].IsArray());
	for(rapidjson::SizeType i = 0; i < acctDoc[iLIABILITIES].Size(); i++){
		auto& acctInfo = acctDoc[iLIABILITIES].GetArray()[i];
		assert(acctInfo.HasMember("name"));
		assert(acctInfo.HasMember("number"));
		Account* newAcct = new Account(acctInfo["name"].GetString(), AccountType::Liability, acctInfo["number"].GetInt());
		_accounts[AccountType::Liability].push_back(newAcct);
	}

	// Equities
	assert(acctDoc.HasMember(iEQUITIES));
	assert(acctDoc[iEQUITIES].IsArray());
	for(rapidjson::SizeType i = 0; i < acctDoc[iEQUITIES].Size(); i++){
		auto& acctInfo = acctDoc[iEQUITIES].GetArray()[i];
		assert(acctInfo.HasMember("name"));
		assert(acctInfo.HasMember("number"));
		Account* newAcct = new Account(acctInfo["name"].GetString(), AccountType::Equity, acctInfo["number"].GetInt());
		_accounts[AccountType::Equity].push_back(newAcct);
	}

	// Revenues
	assert(acctDoc.HasMember(iREVENUES));
	assert(acctDoc[iREVENUES].IsArray());
	for(rapidjson::SizeType i = 0; i < acctDoc[iREVENUES].Size(); i++){
		auto& acctInfo = acctDoc[iREVENUES].GetArray()[i];
		assert(acctInfo.HasMember("name"));
		assert(acctInfo.HasMember("number"));
		Account* newAcct = new Account(acctInfo["name"].GetString(), AccountType::Revenue, acctInfo["number"].GetInt());
		_accounts[AccountType::Revenue].push_back(newAcct);
	}

	// Expenses
	assert(acctDoc.HasMember(iEXPENSES));
	assert(acctDoc[iEXPENSES].IsArray());
	for(rapidjson::SizeType i = 0; i < acctDoc[iEXPENSES].Size(); i++){
		auto& acctInfo = acctDoc[iEXPENSES].GetArray()[i];
		assert(acctInfo.HasMember("name"));
		assert(acctInfo.HasMember("number"));
		Account* newAcct = new Account(acctInfo["name"].GetString(), AccountType::Expense, acctInfo["number"].GetInt());
		_accounts[AccountType::Expense].push_back(newAcct);
	}
}


Account* Ledger::findAccount(const std::string &name) const{
	AccountType type;
	int acctTypeCode = 0;
	try{
		size_t acctNumber = std::stoi(name);
		acctTypeCode = std::stoi(name.substr(0,1));
		switch (acctTypeCode){
			case 1:
				type = AccountType::Asset;
				break;
			case 2:
				type = AccountType::Liability;
				break;
			case 3:
				type = AccountType::Equity;
				break;
			case 4:
				type = AccountType::Revenue;
				break;
			case 5:
				type = AccountType::Expense;
				break;
			default:
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

void Ledger::print(std::ostream &os) const {
	// TODO
}
