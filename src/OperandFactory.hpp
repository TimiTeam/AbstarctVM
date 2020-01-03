#ifndef __OPERANDFACTORY_HPP
# define __OPERANDFACTORY_HPP

# include <iostream>
# include <limits>
# include "OperandInt8.hpp"
# include "OperandInt16.hpp"
# include "OperandInt32.hpp"
# include "OperandFloat.hpp"
# include "OperandDouble.hpp"

class OperandAbstract;

class OperandFactory

{
private:
	double checkValueRangeF(double min, double max, std::string val) const;
	long long checkValueRange(long long min, long long max, std::string val) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
public:
	OperandFactory();
	OperandFactory(const OperandFactory& src);
	~OperandFactory();
	OperandFactory& operator=(const OperandFactory& src);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	class OverflowValueException : public std::exception
	{
	private:
	public:
		OverflowValueException() throw();
		OverflowValueException(const OverflowValueException& src);
		OverflowValueException& operator=(const OverflowValueException& src);
		~OverflowValueException() throw();
		const char* what() const throw ();
	};
	class UnderflowValueException : public std::exception
	{
	private:
	public:
		UnderflowValueException() throw();
		UnderflowValueException(const UnderflowValueException& src);
		UnderflowValueException& operator=(const UnderflowValueException& src);
		~UnderflowValueException() throw();
		const char* what() const throw ();
	};
};
#endif
