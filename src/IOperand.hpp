#ifndef __IOPERAND_HPP
# define __IOPERAND_HPP

# include <iostream>

enum eOperandType{
	Int8 = 1,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand
{
private:

protected:

public:
	virtual const std::string & getValueAsString() const = 0;
	virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
	virtual eOperandType getType( void ) const = 0; // Type of the instance
	virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient	
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
	virtual std::string const & toString( void ) const = 0; // String representation of the instance
	virtual	~IOperand() {};
};
#endif
