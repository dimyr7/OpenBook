#ifndef ENTRY_HPP
#define ENTRY_HPP
#include "Account.hpp"
#include "Amount.hpp"
#include <iostream>
class Entry{
	public:
		Entry(Account* account, Amount amount);
		void apply();
		void reverse() noexcept;


		double getAmount() const noexcept;
		EntryType getEntryType() const noexcept;
		std::string getAccountName() const noexcept;

		friend std::ostream& operator<<(std::ostream &os, const Entry &entry) noexcept;
	private:
		Account* _account;
		Amount _amount;

};
#endif
