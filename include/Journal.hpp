#ifndef JOURNAL_HPP
#define JOURNAL_HPP
#include "Ledger.hpp"
class Journal{
	public:
		Journal(size_t month, size_t year, Ledger* ledger);

		bool newTransaction(const std::time_t &dateTime, const std::string &note);
		bool close();

	private:

		size_t _month;
		size_t _year;
		Ledger* ledger;
};
#endif
