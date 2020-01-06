#include "OperandInt16.hpp"

OperandInt16::OperandInt16()
{
	
}

OperandInt16::OperandInt16(std::string s, eOperandType type) : OperandAbstract(s, type)
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
	(void)src;
	return *this;
}

std::string const & OperandInt16::toString( void ) const{
	return this->getValueAsString();
}