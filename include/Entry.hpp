#ifndef ENTRY_HPP
#define ENTRY_HPP
#include "Account.hpp"
#include <iostream>
class Entry{
	public:
		Entry(Account* account, Type, type, Amount amount);
		bool tryApply() const;
		bool apply();

		Type getType() const;
		Amount getAmount() const;
		std::string getAccountName() const;

		void print(std::ostream &os) const;


	private:
		Account* _account;
		Type _type;
		Amount _amount;

};
#endif
