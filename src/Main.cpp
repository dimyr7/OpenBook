#include "Journal.hpp"
#include "Ledger.hpp"
#include "rapidjson/Document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>
int main(int argc, char** argv){
	if(argc != 2){
		std::cerr << "Not enough arguments" << std::endl;
		std::cout << "$ openbook <accountDocument>" << std::endl;
		exit(1);
	}
	FILE* pFile = fopen(argv[1], "rb");
	char buffer[65536];
	rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
	rapidjson::Document acctDoc;
	acctDoc.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
	Ledger* ledger = new Ledger(acctDoc);
	Account* acct = ledger->findAccount("1100");
	if(acct == nullptr){
		std::cout << "No such account" << std::endl;
	} else {
		std::cout << acct->getName() << std::endl;
	}

}
