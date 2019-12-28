#ifndef __OPERANDINT32_HPP
# define __OPERANDINT32_HPP

# include <iostream>
# include "OperandAbstract.hpp"

class OperandInt32 : public OperandAbstract
{
private:
	int32_t _value;
public:
	OperandInt32();
	OperandInt32(std::string s, eOperandType type, int32_t v);
	OperandInt32(const OperandInt32& src);
	~OperandInt32();
	OperandInt32& operator=(const OperandInt32& src);
	std::string const & toString( void ) const;
};
#endif
