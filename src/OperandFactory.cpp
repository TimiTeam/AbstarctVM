#include "OperandFactory.hpp"

OperandFactory::OperandFactory()
{
	
}

OperandFactory::OperandFactory(const OperandFactory& src)
{
	*this = src;
}

OperandFactory::~OperandFactory()
{
	
}

OperandFactory& OperandFactory::operator=(const OperandFactory& src)
{
	return *this;
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const{
	IOperand const * (OperandFactory::*functions[])(std::string const & value) const = { &OperandFactory::createInt8, &OperandFactory::createInt16, &OperandFactory::createInt32, &OperandFactory::createFloat, &OperandFactory::createDouble};
	eOperandType types[] = {Int8, Int16, Int32, Float, Double};
	for (size_t i = 0; i < 5; ++i){
		if (types[i] == type){
			return (this->*functions[i])(value);
		}
	}
	return NULL;
}

void OperandFactory::cheakValueRange(double min, double max, double val) const{
	if (val < min)
		throw UnderflowValueException();
	else if (val > max)
		throw OverflowValueException();
}

void OperandFactory::cheakValueRange(int min, int max, int val) const{
	if (val < min)
		throw UnderflowValueException();
	else if (val > max)
		throw OverflowValueException();
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const{
	int32_t d = atoi(value.c_str());
	cheakValueRange(-128, 127, d);
	int8_t v = static_cast<int8_t>(d);
	return new const OperandInt8(std::to_string(v), Int8, v);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const{
	int32_t d = atoi(value.c_str());
	cheakValueRange(-32768, 32767, d);
	int16_t v = static_cast<int16_t>(d);
	return new const OperandInt16(std::to_string(d), Int16, v);
}

IOperand const * OperandFactory::createInt32(std::string const & value ) const{
	int32_t d = atoi(value.c_str());
	cheakValueRange(-2147483648, 2147483647, d);
	return new const OperandInt32(std::to_string(d), Int32, d);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const{
	float d = atof(value.c_str());
	cheakValueRange(-std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), d);
	return new const OperandFloat(value, Float, static_cast<float>(d));
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const{
	double d = stod(value);
	cheakValueRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), d);
	return new const OperandDouble(value, Double, d);
}

OperandFactory::OverflowValueException::OverflowValueException() throw()
{

}

const char* OperandFactory::OverflowValueException::what() const throw()
{
	return "Value Overflow";
}

OperandFactory::OverflowValueException::~OverflowValueException() throw()
{

}

OperandFactory::OverflowValueException::OverflowValueException(const OverflowValueException& src)
{
	(void)src;
	*this = src;
}

OperandFactory::OverflowValueException& OperandFactory::OverflowValueException::operator=(const OverflowValueException& src)
{
	(void)src;
	return *this;
}

OperandFactory::UnderflowValueException::UnderflowValueException() throw()
{

}

const char* OperandFactory::UnderflowValueException::what() const throw()
{
	return "Value Underflow";
}

OperandFactory::UnderflowValueException::~UnderflowValueException() throw()
{

}

OperandFactory::UnderflowValueException::UnderflowValueException(const UnderflowValueException& src)
{
	(void)src;
	*this = src;
}

OperandFactory::UnderflowValueException& OperandFactory::UnderflowValueException::operator=(const UnderflowValueException& src)
{
	(void)src;
	return *this;
}