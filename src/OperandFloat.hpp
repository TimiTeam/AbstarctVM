#ifndef __OPERANDFLOAT_HPP
# define __OPERANDFLOAT_HPP

# include <iostream>
# include "OperandAbstract.hpp"

class OperandFloat : public OperandAbstract
{
private:
	float _value;
public:
	OperandFloat();
	OperandFloat(std::string s, eOperandType type, float v);
	OperandFloat(const OperandFloat& src);
	~OperandFloat();
	OperandFloat& operator=(const OperandFloat& src);
	std::string const & toString( void ) const;
};
#endif
