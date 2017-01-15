#ifndef LEDGER_HPP
#define LEDGER_HPP

#include "Account.hpp"

#include "rapidjson/Document.h"

#include <vector>
#include <map>

class Ledger{
	public:
		explicit Ledger(const rapidjson::Document &acctDoc);
		explicit Ledger(const std::string &ledgerFilePath);
		~Ledger() noexcept;

		static void validateLedgerFile(const rapidjson::Document &acctDoc);

		Account* findAccount(const std::string &acctName) const;
		Account* findAccount(size_t acctNumber) const;
		Account* getEquityAcct() const;

		void balanceSheet(std::ostream &os) const noexcept;
		void incomeStatement(std::ostream &os) const noexcept;
		void closeAcctType(AccountType type) noexcept;

		void save(std::string &ledgerFilePath) const;
		bool saved() const noexcept;
	private:
		static rapidjson::Document openLedgerFile(const std::string &ledgerFilePath);
		static size_t getAcctType(size_t acctNumber) noexcept;

		std::map<AccountType, std::vector<Account*> > _accounts;
		bool _saved = true;
};
#endif
