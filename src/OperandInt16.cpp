#include "OperandInt16.hpp"

OperandInt16::OperandInt16()
{
	
}

OperandInt16::OperandInt16(std::string s, eOperandType type, int16_t v) : OperandAbstract(s, type), _value(v)
{
}

OperandInt16::OperandInt16(const OperandInt16& src)
{
	*this = src;
}

OperandInt16::~OperandInt16()
{
	
}

OperandInt16& OperandInt16::operator=(const OperandInt16& src)
{
	return *this;
}

std::string const & OperandInt16::toString( void ) const{
	return this->getValueAsString();
}