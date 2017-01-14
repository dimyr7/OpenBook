#include "Journal.hpp"

#include "color.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <sstream>


Journal::Journal(size_t month, size_t year, Ledger* ledger)
	: _month(month), _year(year), _ledger(ledger) { }

Journal::~Journal() noexcept{
	for(auto it = _transactions.begin(); it != _transactions.end(); it++) {
		delete *it;
	}
	_transactions.clear();
}

void Journal::newTransaction(const std::time_t &dateTime, const std::string &note) noexcept{
	Transaction* newTransaction = new Transaction(dateTime, note);
	// Proccess input from console for the new transaction
	// Form: <D|C> <number> <amount>
	while(true){
		std::cout << "entry> ";

		// Checking for emptyline meaning that no more entries in this transaction
		std::string entryInput;
		std::getline(std::cin, entryInput);
		if(entryInput == ""){
			break;
		}

		// Parse the input for the values
		char entryTypeChar ;
		std::string accountID;
		double amount;

		std::stringstream inputStream;
		inputStream << entryInput;
		inputStream >> entryTypeChar >> accountID >> amount;
		EntryType entryType = (std::tolower(entryTypeChar) == 'd' ? iDEBIT : iCREDIT);

		// Make a new entry
		Account* foundAccount = _ledger->findAccount(accountID);
		Amount entryAmount(amount, entryType);
		if(foundAccount == nullptr){
			std::cerr << "Account not found" << std::endl;
			continue;
		}

		newTransaction->addEntry(foundAccount, std::move(entryAmount));
	}
	_transactions.push_back(newTransaction);

	try{
		newTransaction->apply();
	} catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
	}
}

void Journal::close() noexcept{
	// print pre-balane sheet
	std::cout << Color::GREEN << "=== Balance Sheet ===" << Color::RESET << std::endl;
	_ledger->balanceSheet(std::cout);

	// print income statement
	std::cout << Color::GREEN << "=== Income Statement ===" << Color::RESET << std::endl;;
	_ledger->incomeStatement(std::cout);

	_ledger->closeAcctType(AccountType::Revenue);
	_ledger->closeAcctType(AccountType::Expense);

	// print post-balane sheet
	std::cout << Color::GREEN << "=== Balance Sheet ===" << Color::RESET << std::endl;
	_ledger->balanceSheet(std::cout);
}
