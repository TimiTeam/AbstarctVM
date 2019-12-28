#ifndef __OPERANDINT16_HPP
# define __OPERANDINT16_HPP

# include <iostream>
# include "OperandAbstract.hpp"

class OperandInt16 : public OperandAbstract
{
private:
	int16_t _value;
public:
	OperandInt16();
	OperandInt16(std::string s, eOperandType type, int16_t v);
	OperandInt16(const OperandInt16& src);
	~OperandInt16();
	OperandInt16& operator=(const OperandInt16& src);
	std::string const & toString( void ) const;
};
#endif
