#ifndef JOURNAL_HPP
#define JOURNAL_HPP
#include "Ledger.hpp"
#include "Transaction.hpp"
#include <ctime>
#include <vector>
class Journal{
	public:
		Journal(size_t month, size_t year, Ledger* ledger);
		~Journal() noexcept;

		void newTransaction(const std::time_t &dateTime, const std::string &note) noexcept;
		void close() noexcept;

	private:


		size_t _month;
		size_t _year;
		Ledger* _ledger;
		std::vector<Transaction*> _transactions;
};
#endif
