#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "Amount.hpp"
#include <string>
#include <iostream>
#include <map>

enum class AccountType {
	Asset = 1,
	Liability = 2,
	Equity = 3,
	Revenue = 4,
	Expense = 5,

	END
};
std::map<AccountType, EntryType> balanceSideDict = {
	{AccountType::Asset, iDEBIT},
	{AccountType::Liability, iCREDIT},
	{AccountType::Equity, iCREDIT},
	{AccountType::Revenue, iCREDIT},
	{AccountType::Expense, iDEBIT}
};
class Account{
	public:
		Account(const std::string &name, AccountType type);

		void process(const Amount &amount);
		void reverse() noexcept;


		std::string getName() const noexcept;
		AccountType getType() const noexcept;
		double getAmount() const noexcept;

		void print(std::ostream &os) const noexcept;

		friend std::ostream& operator<<(std::ostream& os, const Account &acct) noexcept;
	private:
		std::string _name;
		AccountType _type;
		Amount _amount;
		Amount _tempAmount;
};
#endif
