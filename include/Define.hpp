#ifndef DEFINE_CPP
#define DEFINE_CPP
#include <string>
#include <map>

typedef bool EntryType;
static const bool iDEBIT = true;
static const bool iCREDIT = false;

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

#endif
