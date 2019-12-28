#include "OperandDouble.hpp"

OperandDouble::OperandDouble()
{
	
}

OperandDouble::OperandDouble(std::string s, eOperandType type, double v)  : OperandAbstract(s, type), _value(v)
{
	
}

OperandDouble::OperandDouble(const OperandDouble& src)
{
	*this = src;
}

OperandDouble::~OperandDouble()
{
	
}

OperandDouble& OperandDouble::operator=(const OperandDouble& src)
{
	return *this;
}


std::string const & OperandDouble::toString( void ) const{
	return this->getValueAsString();
}
