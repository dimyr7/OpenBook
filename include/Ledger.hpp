#ifndef LEDGER_HPP
#define LEDGER_HPP

class Ledger{
	public:
		Ledger();

		Account* createAccount(const std::string &accountName, AccountType type);
		Account* findAccount(const std::string &name) const;

		void print(std::ostream &os) const;
	private:
		std::vector<Account*> _assets;
		std::vector<Account*> _liabs;
		std::vector<Account*> _equity;
		std::vector<Account*> _revenues;
		std::vector<Account*> _expenses;
};
#endif
