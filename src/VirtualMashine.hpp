#ifndef __VIRTUALMASHINE_HPP
# define __VIRTUALMASHINE_HPP

# include <iostream>
# include "Mutantstack.hpp"
# include "OperandFactory.hpp"
# include <map>

class VirtualMashine
{
	typedef void (VirtualMashine::*fun)(void);
private:
	MutantStack<const IOperand*> _stack;
	OperandFactory	_factory;
	std::vector<std::string> _cmd;
	std::vector<fun> _functions;
	std::map<std::string, eOperandType> _types;
	void push(std::string);
	void pop(void);
	void dump(void);
	void add(void);
	bool readLine(std::string line);
public:
	VirtualMashine();
	VirtualMashine(const VirtualMashine& src);
	void readFromFile(std::string fileName);
	void readFromConsole();
	~VirtualMashine();
	VirtualMashine& operator=(const VirtualMashine& src);
};
#endif