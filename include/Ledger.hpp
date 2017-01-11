#ifndef LEDGER_HPP
#define LEDGER_HPP

#include "Account.hpp"

#include "rapidjson/document.h"

#include <vector>
#include <map>

class Ledger{
	public:
		Ledger(rapidjson::Document &acctDoc);
		~Ledger() noexcept;

		Account* findAccount(const std::string &acctName) const;
		Account* findAccount(size_t acctNumber) const;

		void printReports(std::ostream &os) const noexcept;
	private:
		std::map<AccountType, std::vector<Account*> > _accounts;
};
#endif
