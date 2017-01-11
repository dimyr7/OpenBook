#ifndef AMOUNT_HPP
#define AMOUNT_HPP

#include <iostream>

typedef bool EntryType;
static const bool iDEBIT = true;
static const bool iCREDIT = false;
class Amount{
	public:
		/**
		 * Standard Constructor for a new Amount object.
		 * Holds the value and the side to act on
		 * @param value in dollars and cents. If negative, exception is thrown
		 * @type is either Debit or Credit
		 */
		Amount(double value, EntryType type);

		double getValue() const noexcept;
		EntryType getEntryType() const noexcept;
		friend std::ostream& operator<<(std::ostream &os, const Amount &amount) noexcept;

		/**
		 * Multuplies or Divides the value by a scalar
		 * Any fractional cents are rounded down
		 * @param scalar multiple, if negative excpetion is thrown
		 */
		Amount operator*(double scalar) const;
		Amount& operator*=(double scalar);

		Amount operator/(double scalar) const;
		Amount& operator/=(double scalar);
;
		/**
		 * Combines two amounts together
		 * The type is that of LHS
		 * If the two amounts are of different type, subtraction is preformed
		 * Value must stay positive
		 */
		Amount operator+(const Amount &other) const;
		Amount& operator+=(const Amount &other);


/*
		Amount operator-(const Amount &other) const;
		Amount operator+(double scalar) const;
		Amount operator-(double scalar) const;

		bool operator>(const Amount &other) const;
		bool operator<(const Amount &other) const;
		bool operator>=(const Amount &other) const;
		bool operator<=(const Amount &other) const;
		bool operator==(const Amount &other) const;
		bool operator!=(const Amount &other) const;
		*/
	private:
		Amount(size_t value, EntryType type) noexcept;
		size_t _value;
		EntryType _type;
};

#endif
