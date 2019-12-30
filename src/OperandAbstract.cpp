#include "OperandAbstract.hpp"
# include "OperandFactory.hpp"

OperandAbstract::OperandAbstract()
{
}

OperandAbstract::OperandAbstract(std::string v, eOperandType type) : _strValue(v), _type(type)
{

}

OperandAbstract::OperandAbstract(const OperandAbstract& src)
{
	*this = src;
}

OperandAbstract::~OperandAbstract()
{
	
}

std::string const & OperandAbstract::getValueAsString() const{
	return this->_strValue;
}

OperandAbstract& OperandAbstract::operator=(const OperandAbstract& src){
	return *this;
}

int OperandAbstract::getPrecision( void ) const{
	return static_cast<int>(this->_type);
}

eOperandType OperandAbstract::getType( void ) const {
	return this->_type;
}

std::string const OperandAbstract::getResultAsString(double val1, char op, double val2) const{
	double res;
	switch (op)
	{
	case '-':
		res = val1 - val2;
		break;
	case '+':
		res = val1 + val2;
		break;
	case '/':
		if (val2 == 0)
			throw DivisionOrModuloByZeroExcatrions("Division");
		res = val1 / val2;
		break;
	case '*':
		res = val1 * val2;
		break;
	case '%':
		if (static_cast<int>(val2) == 0)
			throw DivisionOrModuloByZeroExcatrions("Modulo");
		res = static_cast<int>(val1) % static_cast<int>(val2);
		break;
	default:
		res = 0;
		break;
	}
	return std::to_string(res);
}

IOperand const * OperandAbstract::makeOperation(char op, IOperand const & rhs) const{
	OperandFactory of;
	double v1 = std::stod(this->_strValue);
	double v2 = std::stod(rhs.getValueAsString());
	return of.createOperand(this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType(), this->getResultAsString(v1, op, v2));
}

IOperand const * OperandAbstract::operator+( IOperand const & rhs ) const{
	return this->makeOperation('+', rhs);
}

IOperand const * OperandAbstract::operator-( IOperand const & rhs ) const{
	return this->makeOperation('-', rhs);
}

IOperand const * OperandAbstract::operator*( IOperand const & rhs ) const{
	return this->makeOperation('*', rhs);

}

IOperand const * OperandAbstract::operator/( IOperand const & rhs ) const{
	return this->makeOperation('/', rhs);
}

IOperand const * OperandAbstract::operator%( IOperand const & rhs ) const{
	return this->makeOperation('%', rhs);
}



OperandAbstract::DivisionOrModuloByZeroExcatrions::DivisionOrModuloByZeroExcatrions() throw()
{
}

OperandAbstract::DivisionOrModuloByZeroExcatrions::DivisionOrModuloByZeroExcatrions(std::string mess) throw()
{
	this->_additionamMessage = mess;
}

const char *OperandAbstract::DivisionOrModuloByZeroExcatrions::what() const throw()
{
	return (_additionamMessage+" by Zero").c_str();
}

OperandAbstract::DivisionOrModuloByZeroExcatrions::~DivisionOrModuloByZeroExcatrions() throw()
{
}

OperandAbstract::DivisionOrModuloByZeroExcatrions::DivisionOrModuloByZeroExcatrions(const DivisionOrModuloByZeroExcatrions &src)
{
	*this = src;
}

OperandAbstract::DivisionOrModuloByZeroExcatrions &OperandAbstract::DivisionOrModuloByZeroExcatrions::operator=(const DivisionOrModuloByZeroExcatrions &src)
{
	this->_additionamMessage = src._additionamMessage;
	return *this;
}
