#include "Journal.hpp"
#include "Ledger.hpp"
#include "Color.hpp"

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>
#include <sstream>

// TODO imporive UI so that command line is more readable
int main(int argc, char** argv){
	sql::Driver *driver = get_driver_instance();

	std::cout << driver << std::endl;
	// Pre-condition testing
	if(argc > 2){
		std::cerr << Color::RED << "Too many arguments" << Color::RESET << std::endl;
		std::cout << "$ openbook <ledger file>" << std::endl;
		exit(1);
	}
	std::string ledgerFile =  "./assets/accounts.json";
	if(argc == 1){
		std::cout << Color::YELLOW << "Using default ledger file: " << Color::BOLD << ledgerFile << Color::RESET << std::endl;
	} else if(argc == 2){
		ledgerFile = argv[1];
	}
	std::cout << "Welcome to OpenBook" << std::endl;
	std::cout << "Reading ledger file: " << Color::GREEN << Color::BOLD<< ledgerFile  << Color::RESET << std::endl;
	// Set up
	Ledger* ledger = nullptr;
	bool savedLedger = true;
	try{
		ledger = new Ledger(ledgerFile);
	} catch (const std::logic_error &e) {
		std::cout << Color::RED << "A termilal error accured while parsing the ledger file" << Color::RESET << std::endl;
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	Journal* journal = new Journal(ledger);
	std::cout << Color::GREEN << "Instructions:" << Color::RESET << std::endl;
	std::cout << Color::YELLOW << "<p | print>" << Color::RESET << " - print the balance sheet" << std::endl;
	std::cout << Color::YELLOW << "<t | trans | transaction>" << Color::RESET << " - create a new transaction" << std::endl;
	std::cout << Color::YELLOW << "<c | close>" << Color::RESET << " - close the journal with the month and year" << std::endl;
	std::cout << Color::YELLOW << "<s | save>" << Color::RESET << " - save the journal to file" << std::endl;
	std::cout << Color::YELLOW << "<q | quit>" << Color::RESET << " - quit" << std::endl;

	while(true){
		std::cout << Color::WHITE <<  "openbook> " << Color::RESET;
		std::string command;
		std::getline(std::cin, command);
		std::stringstream commandStream(command);
		std::vector<std::string> inputCommands;
		do {
			std::string token;
			commandStream >> token;
			inputCommands.push_back(std::move(token));
		} while(commandStream);

		if(inputCommands[0] == "p" or
				inputCommands[0] == "print") {
			// Printing information of all accounts
			if(journal == nullptr){
				// No journal is open
				std::cout << Color::RED << "Please open a journal before printing"  << Color::RESET << std::endl;
				continue;
			}
			ledger->balanceSheet(std::cout);
		} else if(inputCommands[0] == "t" or
				inputCommands[0] == "trans" or
				inputCommands[0] == "transaction") {
			savedLedger = false;
			if(journal == nullptr){
				// No journal is open
				std::cout << Color::RED << "Please open a journal before entering a transactions" << Color::RESET << std::endl;
				continue;
			}
			while(true){
				std::cout << Color::BOLD << Color::GREEN << "New Transaction" << Color::RESET << std::endl;
				std::string note;
				std::cout << "\tnote> ";
				std::getline(std::cin, note);
				if(note == ""){
					break;
				}
				journal->newTransaction(std::time(nullptr), note);
			}
		} else if(inputCommands[0] == "c" or
				inputCommands[0] == "close") {
			// Close existing jounral, requires a journal to be already open
			// <c> <month> <year> : close the open jounral and create a new journal with <month> <year>

			if(journal == nullptr){
				std::cout << Color::RED << "A journal must be open before it can be closed" << Color::RESET << std::endl;
			}
			journal->close();
		} else if(inputCommands[0] == "s" or
				inputCommands[0] == "save") {
			savedLedger = true;
			try{
				ledger->save(ledgerFile);
			} catch(const std::exception &e) {
				std::cout << Color::RED << e.what() << Color::RESET << std::endl;
			}
		} else if(inputCommands[0] == "q" or
				inputCommands[0] == "quit") {
			if(not savedLedger){
				std::cout << Color::RED << "You haven't saved the ledger." << Color::RESET << std::endl;
				std::cout << "Do you want to save? [y/n] ";
				std::string saveQ;
				std::cin >> saveQ;
				if(saveQ == "y"){
					ledger->save(ledgerFile);
				}
			}
			delete journal;
			delete ledger;
			break;
		} else {
			std::cerr << Color::RED << "Not recognized command" << Color::RESET << std::endl;
		}
	}

}
