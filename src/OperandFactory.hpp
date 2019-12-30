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
	void cheakValueRange(double min, double max, double val) const;
	void cheakValueRange(int min, int max, int val) const;
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
	class OverflowValueExcatrions : public std::exception
	{
	private:
	public:
		OverflowValueExcatrions() throw();
		OverflowValueExcatrions(const OverflowValueExcatrions& src);
		OverflowValueExcatrions& operator=(const OverflowValueExcatrions& src);
		~OverflowValueExcatrions() throw();
		const char* what() const throw ();
	};
	class UnderflowValueExcatrions : public std::exception
	{
	private:
	public:
		UnderflowValueExcatrions() throw();
		UnderflowValueExcatrions(const UnderflowValueExcatrions& src);
		UnderflowValueExcatrions& operator=(const UnderflowValueExcatrions& src);
		~UnderflowValueExcatrions() throw();
		const char* what() const throw ();
	};
};
#endif
