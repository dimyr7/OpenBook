#include "Amount.hpp"
#include <stdexcept>

Amount::Amount(double value, EntryType type) {
	if(value < 0){
		_value = static_cast<size_t>(value * -100);
		_type = !type;
	} else {
		_value = static_cast<size_t>(value * 100);
		_type = type;
	}
}
Amount::Amount(size_t value, EntryType type)
	: _value(value), _type(type) { }

double Amount::getValue() const {
	return (_value/100. + (_value%100));
}

EntryType Amount::getEntryType() const {
	return _type;
}


std::ostream& operator<<(std::ostream &os, const Amount &amount) {
	os << "$" << amount.getValue() << " " << (amount._type == iDEBIT ? "Dr" : "Cr");
	return os;
}
Amount Amount::operator*(double scalar) const {
	if(scalar < 0){
		return Amount(this->_value * scalar * -1., !(this->_type));
	}
	return Amount(this->_value * scalar, this->_type);
}

Amount Amount::operator/(double scalar) const {
	if(scalar == 0.){
		throw std::overflow_error("Divide by 0 not allowed");
	}
	return (*this)*(1./scalar);
}
Amount Amount::operator+(const Amount &other) const {
	if(this->_type == other._type) {
		return Amount(this->_value + other._value, this->_type);
	} else {
		if(this->_value > other._value) {
			return Amount(this->_value - other._value, this->_value);
		} else {
			return Amount(other._value - this->_value, other._value);
		}
	}
}
Amount Amount::operator-(const Amount &other) const{
	return ((*this) + (other * -1));
}

/*
bool operator>(const Amount &other) const;
bool operator<(const Amount &other) const;
bool operator>=(const Amount &other) const;
bool operator<=(const Amount &other) const;
bool operator==(const Amount &other) const;
bool operator!=(const Amount &other) const;
*/
