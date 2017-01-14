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
		Account* getEquityAcct() const;

		void balanceSheet(std::ostream &os) const noexcept;
		void incomeStatement(std::ostream &os) const noexcept;
		void closeAcctType(AccountType type) noexcept;
		void close();
	private:
		std::map<AccountType, std::vector<Account*> > _accounts;
		static size_t getAcctType(size_t acctNumber) noexcept;
};
#endif
