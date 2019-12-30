#ifndef __VIRTUALMASHINE_HPP
# define __VIRTUALMASHINE_HPP

# include <iostream>
# include "Mutantstack.hpp"
# include "OperandFactory.hpp"
# include <map>
# include <istream>

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
	void sub(void);
	void mul(void);
	void div(void);
	void mod(void);
	void print(void);
	void assert(std::string);
	bool readLine(std::string line);
	void getTwoTopValue(const IOperand **op1, const IOperand **op2);
public:
	VirtualMashine();
	VirtualMashine(const VirtualMashine& src);
	void read(std::istream &ss);
	~VirtualMashine();
	VirtualMashine& operator=(const VirtualMashine& src);
	class LexicalOrSyntacticExcatrions : public std::exception
	{
	private:
	public:
		LexicalOrSyntacticExcatrions() throw();
		LexicalOrSyntacticExcatrions(const LexicalOrSyntacticExcatrions& src);
		LexicalOrSyntacticExcatrions& operator=(const LexicalOrSyntacticExcatrions& src);
		~LexicalOrSyntacticExcatrions() throw();
		const char* what() const throw ();
	};
	class ToSmallStackExcatrions : public std::exception
	{
	private:
		std::string _additionamMessage;
	public:
		ToSmallStackExcatrions() throw();
		ToSmallStackExcatrions(std::string) throw();
		ToSmallStackExcatrions(const ToSmallStackExcatrions& src);
		ToSmallStackExcatrions& operator=(const ToSmallStackExcatrions& src);
		~ToSmallStackExcatrions() throw();
		const char* what() const throw ();
	};
	class AssertIsNotTrueExcatrions : public std::exception
	{
	private:
	public:
		AssertIsNotTrueExcatrions() throw();
		AssertIsNotTrueExcatrions(const AssertIsNotTrueExcatrions& src);
		AssertIsNotTrueExcatrions& operator=(const AssertIsNotTrueExcatrions& src);
		~AssertIsNotTrueExcatrions() throw();
		const char* what() const throw ();
	};
};
#endif
