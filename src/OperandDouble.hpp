#ifndef __OPERANDDOUBLE_HPP
# define __OPERANDDOUBLE_HPP

# include <iostream>
# include "OperandAbstract.hpp"

class OperandDouble : public OperandAbstract
{
private:
public:
	OperandDouble();
	OperandDouble(std::string s, eOperandType type);
	OperandDouble(const OperandDouble& src);
	~OperandDouble();
	OperandDouble& operator=(const OperandDouble& src);
	std::string const & toString( void ) const;
};
#endif
