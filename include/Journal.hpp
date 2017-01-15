#ifndef JOURNAL_HPP
#define JOURNAL_HPP
#include "Ledger.hpp"
#include "Transaction.hpp"
#include <ctime>
#include <vector>
class Journal{
	public:
		explicit Journal(Ledger* ledger) ;
		~Journal() noexcept;

		void newTransaction(const std::time_t &dateTime, const std::string &note) noexcept;
		void close() noexcept;

	private:


		Ledger* _ledger;
		std::vector<Transaction*> _transactions;
};
#endif
