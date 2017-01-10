#include "Amount.hpp"

#include <stdexcept>

/*
 * Constructors
 */
Amount::Amount(double value, EntryType type) {
	if(value < 0){
		throw std::range_error("value cannot be negative");
	}
	_value = static_cast<size_t>(value * 100);
	_type = type;
}

Amount::Amount(size_t value, EntryType type) noexcept
	: _value(value), _type(type) { }

Amount::Amount(const Amount &other) noexcept{
	this->_value = other._value;
	this->_type = other._type;
}

Amount& Amount::operator=(const Amount& other) noexcept{
	this->_value = other._value;
	this->_type = other._type;
	return *this;
}
/*
 * Getters
 */

double Amount::getValue() const noexcept{
	return (_value/100. + (_value%100));
}

EntryType Amount::getEntryType() const noexcept{
	return _type;
}

/*
 * Printers
 */
std::ostream& operator<<(std::ostream &os, const Amount &amount) noexcept{
	os << "$" << amount.getValue() << " " << (amount._type == iDEBIT ? "Dr" : "Cr");
	return os;
}

/*
 * Scalar multiplication
 */
Amount Amount::operator*(double scalar) const {
	if(scalar < 0){
		throw std::range_error("scalar cannot be negative");
	}
	return Amount(this->_value * scalar, this->_type);
}
Amount& Amount::operator*=(double scalar) {
	if(scalar < 0) {
		throw std::range_error("scalar cannot be negative");
	}
	_value*=scalar;
	return *this;
}

Amount Amount::operator/(double scalar) const {
	if(scalar == 0.){
		throw std::overflow_error("Divide by 0 is not allowed");
	}
	return (*this)*(1./scalar);
}
Amount& Amount::operator/=(double scalar) {
	if(scalar == 0.){
		throw std::overflow_error("Divide by 0 is not allowed");
	}
	_value/=scalar;
	return *this;
}


Amount Amount::operator+(const Amount &other) const {
	if(this->_type == other._type) {
		return Amount(this->_value + other._value, this->_type);
	}
	if(other._value > this->_value){
		throw std::range_error("value of LHS may not be negative");
	}
	return Amount(this->_value - other._value, this->_value);
}

Amount& Amount::operator+=(const Amount &other) {
	if(this->_type == other._type) {
		this->_value+= other._value;
		return *this;
	}
	if(other._value > this->_value){
		throw std::range_error("value of LHS may not be negative");
	}
	this->_value-=other._value;
	return *this;
}

/*
bool operator>(const Amount &other) const;
bool operator<(const Amount &other) const;
bool operator>=(const Amount &other) const;
bool operator<=(const Amount &other) const;
bool operator==(const Amount &other) const;
bool operator!=(const Amount &other) const;
*/
