#ifndef __OPERANDINT8_HPP
# define __OPERANDINT8_HPP

# include <iostream>
# include "OperandAbstract.hpp"

class OperandInt8 : public OperandAbstract
{
private:
public:
	OperandInt8();
	OperandInt8(std::string s, eOperandType type);
	OperandInt8(const OperandInt8& src);
	~OperandInt8();
	OperandInt8& operator=(const OperandInt8& src);
	std::string const & toString( void ) const;
};
#endif
