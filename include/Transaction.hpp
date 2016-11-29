#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include "Entry.hpp"
#include <vector>
class Transaction{
	public:
		Transaction(const std::time_t &dateTime, const std::string &note);
		void addDebit(Account* account, Amount amount);
		void addCredit(Account* accoumt, Amount amount);

		bool apply();

	private:
		std::vector<Entry> _debits;
		std::vector<Entry> _credits;
		std::time_t _dateTime;
		std::string _note;



};
#endif
