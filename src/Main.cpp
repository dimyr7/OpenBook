#include "Journal.hpp"
#include "Ledger.hpp"
#include "Color.hpp"
#include "rapidjson/Document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>
#include <sstream>


Journal* openJournal(size_t month, size_t year, Ledger* ledger){
	return new Journal(month, year, ledger);
}


int main(int argc, char** argv){
	// Pre-condition testing
	if(argc > 2){
		std::cerr << Color::RED << "Not enough arguments" << Color::RESET << std::endl;
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
	// Reading config file
	FILE* pFile = fopen(ledgerFile.c_str(), "rb");
	char buffer[65536];
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	rapidjson::Document acctDoc;
	acctDoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

	// Set up
	Ledger* ledger = nullptr;
	try{
		ledger = new Ledger(acctDoc);
	} catch (const std::logic_error &e) {
		std::cout << Color::RED << "A termilal error accured while parsing the ledger file" << Color::RESET << std::endl;
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	Journal* journal = nullptr;
	while(true){
		std::cout << "openbook> ";
		std::string command;
		std::getline(std::cin, command);
		std::stringstream commandStream(command);
		std::vector<std::string> inputCommands;
		do {
			std::string token;
			commandStream >> token;
			inputCommands.push_back(std::move(token));
		} while(commandStream);

		if(inputCommands[0] == "n"){
			// Create new journal
			// <n> <month> <year> : create new journal with month and year
			if(journal != nullptr){
				// Another journal is already open
				std::cout << Color::RED << "Please close the open journal before creating a new one"<< Color::RESET << std::endl;
				continue;
			}

			if(inputCommands.size() != 4){
				std::cout << Color::RED << "form: <n> <month> <year>" << Color::RESET << std::endl;
				continue;
			}
			size_t journalMonth = 0;
			size_t journalYear  = 0;
			try{
				journalMonth = std::stoi(inputCommands[1]);
				journalYear  = std::stoi(inputCommands[2]);
			} catch(const std::invalid_argument &e) {
				std::cout << Color::RED << "<month> and <year> must be integers" << Color::RESET<< std::endl;
				continue;
			}
			journal = new Journal(journalMonth, journalYear, ledger);
		} else if(inputCommands[0] == "o"){
			// TODO connect to DB
			std::cout << Color::RED << "This function not yet implemented. Come back later" << Color::RESET << std::endl;
			continue;	
			// Open existing jounral
			// <o> <month> <year> : open journal with month year, requires DB access

			if(journal != nullptr){
				// Another journal is already open
				std::cout << Color::RED << "Please close the open journal before opening a new one" << Color::RESET << std::endl;
				continue;
			}
			if(inputCommands.size() != 4){
				std::cout << "form: <o> <month> <year>" << std::endl;
				continue;
			}
			size_t journalMonth = 0;
			size_t journalYear  = 0;
			try{
				journalMonth = std::stoi(inputCommands[1]);
				journalYear  = std::stoi(inputCommands[2]);
			} catch(const std::exception &e) {
				std::cout << Color::RED << "<month> and <year> must be integers" << Color::RESET<< std::endl;
				continue;
			}

			journal = openJournal(journalMonth, journalYear, ledger);
		} else if(inputCommands[0] == "p"){
			// Printing information of all accounts
			if(journal == nullptr){
				// No journal is open
				std::cout << Color::RED << "Please open a journal before printing"  << Color::RESET << std::endl;
				continue;
			}
			ledger->balanceSheet(std::cout);
		} else if(inputCommands[0] == "t"){
			if(journal == nullptr){
				// No journal is open
				std::cout << Color::RED << "Please open a journal before entering a transactions" << Color::RESET << std::endl;
				continue;
			}
			while(true){
				std::cout << Color::BOLD << Color::GREEN << "New Transaction" << Color::RESET << std::endl;
				std::string note;
				std::cout << "note> ";
				std::getline(std::cin, note);
				if(note == ""){
					break;
				}
				journal->newTransaction(std::time(nullptr), note);
			}
		} else if(inputCommands[0] == "c"){
			// Close existing jounral, requires a journal to be already open
			// <c> <month> <year> : close the open jounral and create a new journal with <month> <year>
			// TODO how to pull balance from 1 journal to the next

			if(journal == nullptr){
				std::cout << Color::RED << "A journal must be open before it can be closed" << Color::RESET << std::endl;
			}
			journal->close();
			delete journal;
			journal = nullptr;

		} else if(inputCommands[0] == "q"){
			// TODO quit safely
			delete journal;
			delete ledger;
			break;
		} else {
			std::cerr << Color::RED << "Not recognized command" << Color::RESET << std::endl;
		}
	}

}
