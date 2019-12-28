#include "OperandFloat.hpp"

OperandFloat::OperandFloat()
{
	
}

OperandFloat::OperandFloat(std::string s, eOperandType type, float v) : OperandAbstract(s, type), _value(v)
{

}

OperandFloat::OperandFloat(const OperandFloat& src)
{
	*this = src;
}

OperandFloat::~OperandFloat()
{
	
}

OperandFloat& OperandFloat::operator=(const OperandFloat& src)
{
	return *this;
}


std::string const & OperandFloat::toString( void ) const{
	return this->getValueAsString();
}