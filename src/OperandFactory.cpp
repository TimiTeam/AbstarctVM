#include "OperandFactory.hpp"
#include <sstream>

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

double OperandFactory::checkValueRangeF(double min, double max, std::string val) const{
	double d = std::stod(val);
	if (d < min)
		throw UnderflowValueException();
	else if (d > max)
		throw OverflowValueException();
	return d;
}

long long OperandFactory::checkValueRange(long long min, long long max, std::string val) const{
	long long intVal;

	std::istringstream is (val);
	is >> intVal;
	if (intVal < min)
		throw UnderflowValueException();
	if (intVal > max)
		throw OverflowValueException();
	return intVal;
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const{
	long long d = checkValueRange(-128, 127, value);
	int8_t v = static_cast<int8_t>(d);
	return new const OperandInt8(std::to_string(v), Int8, v);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const{
	long long d = checkValueRange(-32768, 32767, value);
	int16_t v = static_cast<int16_t>(d);
	return new const OperandInt16(std::to_string(d), Int16, v);
}

IOperand const * OperandFactory::createInt32(std::string const & value ) const{
	long long d = checkValueRange(-2147483648, 2147483647, value);
	d = static_cast<int32_t>(d);
	return new const OperandInt32(std::to_string(d), Int32, d);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const{
	float d = checkValueRangeF(-std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), value);
	return new const OperandFloat(value, Float, static_cast<float>(d));
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const{
	double d = checkValueRangeF(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), value);
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
