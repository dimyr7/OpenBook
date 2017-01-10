#ifndef LEDGER_HPP
#define LEDGER_HPP

#include "Account.hpp"

#include "rapidjson/document.h"

#include <vector>
#include <map>

class Ledger{
	public:
		Ledger(rapidjson::Document &acctDoc);

		Account* findAccount(const std::string &acctName) const;
		Account* findAccount(size_t acctNumber) const;

		friend std::ostream operator<<(std::ostream &os, const Ledger &ledger);
		void print(std::ostream &os) const;
	private:
		std::map<AccountType, std::vector<Account*> > _accounts;
};
#endif
