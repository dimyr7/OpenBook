#include "Ledger.hpp"
#include "Transaction.hpp"

#include <iostream>
#include <string>

Ledger::Ledger(rapidjson::Document &acctDoc) {
	if(not acctDoc.IsObject()){
		throw std::logic_error("Ledger file is not a valid JSON");
	}
	// For each account type
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

		// For each account in account type
		for(rapidjson::SizeType i = 0; i < acctDoc[acctTypeStr].Size(); i++){
			auto& acctInfo = acctDoc[acctTypeStr].GetArray()[i];
			if(not acctInfo.HasMember("name")){
				throw std::logic_error("Each account must have a name");
			} else if(not acctInfo.HasMember("number")) {
				throw std::logic_error("Each account must have a number");
			} else if(not acctInfo.HasMember("amount")) {
				throw std::logic_error("Each account must have a starting amount");
			}

			Account* newAcct = new Account(acctInfo["name"].GetString(),
					it->first, acctInfo["number"].GetInt(),
					acctInfo["amount"].GetDouble());
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

Account* Ledger::getEquityAcct() const {
	return _accounts.at(AccountType::Equity)[0];
}


void Ledger::balanceSheet(std::ostream &os) const noexcept{
	for(auto it = _accounts.begin(); it != _accounts.end(); it++){
		os << "= " << Account::iACCT_TYPE_STRING_DICT.at(it->first) << std::endl;
		for(auto is = it->second.begin(); is != it->second.end(); is++){ os << *(*is) << std::endl;
		}
	}
}

void Ledger::incomeStatement(std::ostream &os) const noexcept {
	Amount revenues(0., Account::iACCT_TYPE_BALANCE_SIDE_DICT.at(AccountType::Revenue));
	for(auto it = _accounts.at(AccountType::Revenue).begin();
			it != _accounts.at(AccountType::Revenue).end(); it++){
		revenues += (*it)->getAmount();
	}
	std::cout << "Total revenue: " << revenues << std::endl;

	Amount expenses(0., Account::iACCT_TYPE_BALANCE_SIDE_DICT.at(AccountType::Expense));
	for(auto it = _accounts.at(AccountType::Expense).begin();
			it != _accounts.at(AccountType::Expense).end(); it++){
		expenses += (*it)->getAmount();
	}
	std::cout << "Total expense: " << expenses << std::endl;;
}


size_t Ledger::getAcctType(size_t acctNumber) noexcept {
	while(acctNumber > 9) {
		acctNumber/= 10;
	}
	return acctNumber;
}

void Ledger::closeAcctType(AccountType type) noexcept{
	Account* equityAcct = getEquityAcct();
	for(auto it = _accounts.at(type).begin();
			it != _accounts.at(type).end(); it++){
		Amount acctBalance = (*it)->getAmount();
		Amount reverseTempBalance(acctBalance.getValue(), not acctBalance.getEntryType());

		Transaction* closingTrans = new Transaction(std::time(nullptr), "Closing transaction");
		closingTrans->addEntry(equityAcct, acctBalance);
		closingTrans->addEntry(*it, reverseTempBalance);
		try{
			closingTrans->apply();
		} catch(const std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

void Ledger::close(){
	// TODO create new transactions

}
