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
		res = val1 / val2;
		break;
	case '*':
		res = val1 * val2;
		break;
	case '%':
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
