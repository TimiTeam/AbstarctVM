#include "OperandInt32.hpp"

OperandInt32::OperandInt32()
{
	
}

OperandInt32::OperandInt32(std::string s, eOperandType type) : OperandAbstract(s, type)
{
	
}

OperandInt32::OperandInt32(const OperandInt32& src)
{
	*this = src;
}

OperandInt32::~OperandInt32()
{
	
}

OperandInt32& OperandInt32::operator=(const OperandInt32& src)
{

	(void)src;
	return *this;
}


std::string const & OperandInt32::toString( void ) const{
	return this->getValueAsString();
}
