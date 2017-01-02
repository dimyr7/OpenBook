#ifndef LEDGER_HPP
#define LEDGER_HPP

#include "Account.hpp"
#include <vector>
#include <map>

class Ledger{
	public:
		Ledger();
		//Ledger(rapidjson::Document);

		Account* createAccount(const std::string &accountName, AccountType type);
		Account* findAccount(const std::string &name) const;

		friend std::ostream operator<<(std::ostream &os, const Ledger &ledger);
		void print(std::ostream &os) const;
	private:
		std::map<AccountType, std::vector<Account*> > _accounts;
};
#endif
