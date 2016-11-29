#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include <string>
#include <iostream>
class Account{
	public:
		Account(const std::string &name, Type type, Amount initAmount = 0);

		bool tryProcess(Type type, Amount amount) const ;
		bool process(Type type, Amount amount);

		std::string getName() const;
		Type getType() const;
		Amount getAmount() const;

		void print(std::ostream &os) const;
	private:
		std::string _name;
		Type _type;
		Amount _amount;
};
#endif
