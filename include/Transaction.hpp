#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include "Entry.hpp"
#include <vector>
class Transaction{
	public:
		Transaction(const std::time_t &dateTime, const std::string &note);
		void addEntry(Account* account, const Amount &amount);

		void apply();

	private:
		std::vector<Entry> _entries;
		std::time_t _dateTime;
		std::string _note;



};
#endif
