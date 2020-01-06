#ifndef __OPERANDINT16_HPP
# define __OPERANDINT16_HPP

# include <iostream>
# include "OperandAbstract.hpp"

class OperandInt16 : public OperandAbstract
{
private:
public:
	OperandInt16();
	OperandInt16(std::string s, eOperandType type);
	OperandInt16(const OperandInt16& src);
	~OperandInt16();
	OperandInt16& operator=(const OperandInt16& src);
	std::string const & toString( void ) const;
};
#endif
