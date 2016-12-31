#ifndef AMOUNT_HPP
#define AMOUNT_HPP
#include "Define.hpp"
#include <iostream>

class Amount{
	public:
		/**
		 * Standard Constructor for a new Amount object.
		 * Holds the value and the side to act on
		 * @param value in dollars and cents. If negative, the opposite type is used
		 * @type is either Debit or Credit
		 */
		Amount(double value, EntryType type);


		double getValue() const;
		EntryType getEntryType() const;
		friend std::ostream& operator<<(std::ostream &os, const Amount &amount);

		/**
		 * Multuplies or Divides the value by a scalar
		 * Any fractional cents are rounded down
		 * @param scalar multiple, if negative the EntryType is swithced
		 */
		Amount operator*(double scalar) const;
		Amount operator/(double scalar) const;

		/**
		 * Combines two amounts together
		 * If the resulting balance is negativeme EntryType is swithced
		 * If the resulting balance is 0 due to oppositve EntryType then *this*'s EntryType is used
		 */
		Amount operator+(const Amount &other) const;
		Amount operator-(const Amount &other) const;
		Amount operator+(double scalar) const;
		Amount operator-(double scalar) const;

/*
		bool operator>(const Amount &other) const;
		bool operator<(const Amount &other) const;
		bool operator>=(const Amount &other) const;
		bool operator<=(const Amount &other) const;
		bool operator==(const Amount &other) const;
		bool operator!=(const Amount &other) const;
		*/
	private:
		Amount(size_t value, EntryType type);
		size_t _value;
		EntryType _type;
};

#endif
