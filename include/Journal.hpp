#ifndef JOURNAL_HPP
#define JOURNAL_HPP
#include "Ledger.hpp"
#include <ctime>
class Journal{
	public:
		Journal(size_t month, size_t year, Ledger* ledger);

		void newTransaction(const std::time_t &dateTime, const std::string &note);
		bool close();

	private:

		Ledger* _ledger;
		size_t _month;
		size_t _year;
};
#endif
