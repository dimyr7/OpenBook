#ifndef DEFINE_CPP
#define DEFINE_CPP
#include <string>

typedef Amount size_t

std::string toString(Amount amount){
	return std::string("$"  + amount/100 + "." + amount%100);
}

enum class AccountType {
	Asset = 1,
	Liability = 2,
	Equity = 3,
	Revenue = 4,
	Expenses = 5
}

enum class Type{
	Debit = 0,
	Credit = 1
};
#endif
