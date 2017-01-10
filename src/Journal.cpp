#include "Journal.hpp"
#include "Transaction.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <sstream>


Journal::Journal(size_t month, size_t year, Ledger* ledger)
	: _month(month), _year(year){ }


void Journal::newTransaction(const std::time_t &dateTime, const std::string &note){
	Transaction* newTransaction = new Transaction( dateTime, note);
	// Proccess input from console for the new transaction
	// Form: <D|C> <number> <amount>
	std::cout << "### New Transcation" << std::endl;
	while(true){
		std::cout << "## New Entry" << std::endl;
		std::cout << "> ";

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

	try{
		newTransaction->apply();
	} catch(const std::exception &e){
		std::cout << e.what() << std::endl;
	}
}
bool Journal::close(){
	// TODO print monthly report
	return false;
}
