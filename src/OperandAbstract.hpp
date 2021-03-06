#ifndef __OPERANDABSTRACT_HPP
# define __OPERANDABSTRACT_HPP

# include <iostream>
# include <vector>
# include "IOperand.hpp"

class OperandAbstract : public IOperand
{
private:
	std::string _strValue;
	eOperandType _type;
	IOperand const * makeOperation(char op, IOperand const & rhs) const;
	std::string const getResultAsString(double val1, char op, double val2) const;
public:
	OperandAbstract();
	OperandAbstract(std::string v, eOperandType type);
	OperandAbstract(const OperandAbstract& src);
	~OperandAbstract();
	OperandAbstract& operator=(const OperandAbstract& src);
	virtual const std::string & getValueAsString() const;
	virtual int getPrecision( void ) const;
	virtual eOperandType getType( void ) const;
	virtual IOperand const * operator+( IOperand const & rhs ) const;
	virtual IOperand const * operator-( IOperand const & rhs ) const;
	virtual IOperand const * operator*( IOperand const & rhs ) const;
	virtual IOperand const * operator/( IOperand const & rhs ) const;
	virtual IOperand const * operator%( IOperand const & rhs ) const;
	virtual std::string const & toString( void ) const = 0; 
	class DivisionOrModuloByZeroException : public std::exception
	{
	private:
		std::string _additionamMessage;
	public:
		DivisionOrModuloByZeroException() throw();
		DivisionOrModuloByZeroException(std::string) throw();
		DivisionOrModuloByZeroException(const DivisionOrModuloByZeroException& src);
		DivisionOrModuloByZeroException& operator=(const DivisionOrModuloByZeroException& src);
		~DivisionOrModuloByZeroException() throw();
		const char* what() const throw ();
	};
};
#endif
