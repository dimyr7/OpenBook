#include "Ledger.hpp"
#include "Transaction.hpp"
#include "Color.hpp"

#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/filewritestream.h"

#include <iostream>
#include <string>
#include <sstream>

Ledger::Ledger(const rapidjson::Document &acctDoc) {
	try{
		Ledger::validateLedgerFile(acctDoc);
	} catch(const std::exception &e) {
		std::cout << Color::RED << e.what() << Color::RESET << std::endl;
	}
	// For each account type
	for(auto it  = Account::iACCT_TYPE_STRING_DICT.cbegin();
		   	 it != Account::iACCT_TYPE_STRING_DICT.cend(); it++){
		const char* acctTypeStr = it->second.c_str();
		// For each account in account type
		for(rapidjson::SizeType i = 0; i < acctDoc[acctTypeStr].Size(); i++){
			auto& acctInfo = acctDoc[acctTypeStr].GetArray()[i];
			Account* newAcct = new Account(acctInfo["name"].GetString(),
					it->first, acctInfo["number"].GetInt(),
					acctInfo["amount"].GetDouble());

			_accounts[it->first].push_back(newAcct);
		}
	}
}

void Ledger::validateLedgerFile(const rapidjson::Document &acctDoc) {
	if(not acctDoc.IsObject()){
		throw std::runtime_error("Ledger file is not a valid JSON");
	}
	// For each account type
	for(auto it = Account::iACCT_TYPE_STRING_DICT.cbegin();
			it != Account::iACCT_TYPE_STRING_DICT.cend(); it++){
		const char* acctTypeStr = it->second.c_str();
		if(not acctDoc.HasMember(acctTypeStr)) {
			throw std::runtime_error("Ledger file doesn't have all types of accounts");
		} else if(not acctDoc[acctTypeStr].IsArray()) {
			throw std::runtime_error("Each type of account must be listed in array form");
		} else if(acctDoc[acctTypeStr].Size() < 1) {
			throw std::runtime_error("There must be at least 1 account for each type");
		}

		// For each account in account type
		for(rapidjson::SizeType i = 0; i < acctDoc[acctTypeStr].Size(); i++){
			auto& acctInfo = acctDoc[acctTypeStr].GetArray()[i];
			if(not acctInfo.HasMember("name")){
				throw std::runtime_error("Each account must have a name");
			} else if(not acctInfo.HasMember("number")) {
				throw std::runtime_error("Each account must have a number");
			} else if(not acctInfo.HasMember("amount")) {
				throw std::runtime_error("Each account must have a starting amount");
			}
		}
	}
}

Ledger::Ledger(const std::string &ledgerFilePath)
	: Ledger(Ledger::openLedgerFile(ledgerFilePath)){ }

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
	} catch(const std::exception &e) {
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
	size_t maxStringLength = 0;
	for(auto it = _accounts.begin(); it != _accounts.end(); it++){
		for(auto is = it->second.begin(); is != it->second.end(); is++){
			std::stringstream unpaddedString;
			unpaddedString << (*is)->getName() << (*is)->getAmount();
			if(unpaddedString.str().length() > maxStringLength){
				maxStringLength = unpaddedString.str().length();
			}
		}
	}
	maxStringLength += 5;
	for(auto it = _accounts.begin(); it != _accounts.end(); it++){
		os << "==== " << Color::WHITE << Account::iACCT_TYPE_STRING_DICT.at(it->first) << Color::RESET << std::endl;
		for(auto is = it->second.begin(); is != it->second.end(); is++){
			std::stringstream unpaddedString;
			unpaddedString << (*is)->getName() << (*is)->getAmount();
			size_t stringLength  = unpaddedString.str().length();
			os << "\t" << (*is)->getName();
			for(size_t i = stringLength; i < maxStringLength; i++){
				os << ".";
			}
			os << (*is)->getAmount() << std::endl;
		}
	}
}

void Ledger::incomeStatement(std::ostream &os) const noexcept {
	Amount revenues(0., Account::iACCT_TYPE_BALANCE_SIDE_DICT.at(AccountType::Revenue));
	for(auto it = _accounts.at(AccountType::Revenue).begin();
			it != _accounts.at(AccountType::Revenue).end(); it++){
		revenues += (*it)->getAmount();
		std::cout << "\t" << *(*it) << std::endl;
	}
	std::cout << "Total revenue:\t\t" << revenues << std::endl;

	Amount expenses(0., Account::iACCT_TYPE_BALANCE_SIDE_DICT.at(AccountType::Expense));
	for(auto it = _accounts.at(AccountType::Expense).begin();
			it != _accounts.at(AccountType::Expense).end(); it++){
		expenses += (*it)->getAmount();
		std::cout << "\t" << *(*it) << std::endl;
	}
	std::cout << "Total expense:\t\t" << expenses << std::endl;;
}


size_t Ledger::getAcctType(size_t acctNumber) noexcept {
	while(acctNumber > 9) {
		acctNumber/= 10;
	}
	return acctNumber;
}

void Ledger::closeAcctType(AccountType type) noexcept{
	_saved = false;
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

rapidjson::Document Ledger::openLedgerFile(const std::string &ledgerFilePath) {
	FILE* pFile = fopen(ledgerFilePath.c_str(), "r");
	char buffer[65536];
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	rapidjson::Document acctDoc;
	acctDoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
	fclose(pFile);

	return acctDoc;
}

void Ledger::save(std::string &ledgerFilePath) const {
	using namespace rapidjson;
	std::cout << "Saving" << std::endl;
	Document acctDoc = Ledger::openLedgerFile(ledgerFilePath);
	try{
		Ledger::validateLedgerFile(acctDoc);
	} catch(const std::exception &e) {
		std::cout << Color::RED << e.what() << Color::RESET << std::endl;
	}

	// For each account type
	for(auto it = Account::iACCT_TYPE_STRING_DICT.cbegin();
			it != Account::iACCT_TYPE_STRING_DICT.cend(); it++){
		const char* acctTypeStr = it->second.c_str();
		// For each account in account type
		if(acctDoc[acctTypeStr].Size() != _accounts.at(it->first).size()){
			throw std::logic_error("the accounst don't match up between ledger and ledger-file");
		}
		for(SizeType i = 0; i < acctDoc[acctTypeStr].Size(); i++){
			auto& acctInfo = acctDoc[acctTypeStr].GetArray()[i];
			Account* matchingAcct = findAccount(acctInfo["number"].GetInt());
			if(matchingAcct == nullptr){
				throw std::runtime_error("cannot find account in the ledger");
			}
			std::cout << "Setting value: " << matchingAcct->getAmount() << std::endl;
			acctInfo["amount"] = matchingAcct->getAmount().getValue();
			std::cout << "Set value: " << acctDoc[acctTypeStr].GetArray()[i]["amount"].GetDouble() << std::endl;
		}
	}
	FILE* wFile = fopen(ledgerFilePath.c_str(), "w");

	GenericStringBuffer< UTF8<> > buffer;
	Writer<GenericStringBuffer< UTF8<> > > writer(buffer);
	acctDoc.Accept(writer);
	const char* str = buffer.GetString();
	fprintf(wFile, "%s", str);
	fclose(wFile);
}

bool Ledger::saved() const noexcept {
	return _saved;
}

