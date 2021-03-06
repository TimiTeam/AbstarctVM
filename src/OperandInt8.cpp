#include "OperandInt8.hpp"

OperandInt8::OperandInt8()
{
	
}

OperandInt8::OperandInt8(std::string s, eOperandType type) : OperandAbstract(s, type)
{
}

OperandInt8::OperandInt8(const OperandInt8& src)
{
	*this = src;
}

OperandInt8::~OperandInt8()
{
	
}

OperandInt8& OperandInt8::operator=(const OperandInt8& src)
{
	(void)src;
	return *this;
}

std::string const & OperandInt8::toString( void ) const{
	return this->getValueAsString();
}