#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "Amount.hpp"

#include <string>
#include <iostream>

enum class AccountType {
	Asset = 1,
	Liability = 2,
	Equity = 3,
	Revenue = 4,
	Expense = 5,

	END
};
class Account{
	public:
		Account(const std::string &name, AccountType type, size_t id);

		void process(const Amount &amount);
		void reverse() noexcept;


		std::string getName() const noexcept;
		AccountType getType() const noexcept;
		size_t getNumber() const noexcept;
		double getAmount() const noexcept;

		void print(std::ostream &os) const noexcept;

		friend std::ostream& operator<<(std::ostream& os, const Account &acct) noexcept;
	private:
		std::string _name;
		AccountType _type;
		size_t _id;
		Amount _amount;
		Amount _tempAmount;
};
#endif
