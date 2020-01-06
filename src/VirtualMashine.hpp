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
	std::map<std::string, fun> _functions;
	std::map<std::string, eOperandType> _types;
	std::string _errorFileName;
	std::string _output;
	void push(std::string);
	void pop(void);
	void dump(void);
	void add(void);
	void sub(void);
	void mul(void);
	void div(void);
	void mod(void);
	void doMathOperation(char op);
	void print(void);
	void assert(std::string);
	bool readLine(std::string line);
	void getTwoTopValue(const IOperand **op1, const IOperand **op2);
	void nextElem(MutantStack<const IOperand *>::iterator elem, MutantStack<const IOperand *>::iterator end);
	void printErrorToFile(std::string message);
public:
	VirtualMashine();
	VirtualMashine(const VirtualMashine& src);
	void read(std::istream &ss, bool std);
	~VirtualMashine();
	VirtualMashine& operator=(const VirtualMashine& src);
	class LexicalOrSyntacticException : public std::exception
	{
	private:
	public:
		LexicalOrSyntacticException() throw();
		LexicalOrSyntacticException(const LexicalOrSyntacticException& src);
		LexicalOrSyntacticException& operator=(const LexicalOrSyntacticException& src);
		~LexicalOrSyntacticException() throw();
		const char* what() const throw ();
	};
	class ToSmallStackException : public std::exception
	{
	private:
		std::string _additionamMessage;
	public:
		ToSmallStackException() throw();
		ToSmallStackException(std::string) throw();
		ToSmallStackException(const ToSmallStackException& src);
		ToSmallStackException& operator=(const ToSmallStackException& src);
		~ToSmallStackException() throw();
		const char* what() const throw ();
	};
	class AssertIsNotTrueException : public std::exception
	{
	private:
	public:
		AssertIsNotTrueException() throw();
		AssertIsNotTrueException(const AssertIsNotTrueException& src);
		AssertIsNotTrueException& operator=(const AssertIsNotTrueException& src);
		~AssertIsNotTrueException() throw();
		const char* what() const throw ();
	};
	class UnknownInstructionsException : public std::exception
	{
	private:
	public:
		UnknownInstructionsException() throw();
		UnknownInstructionsException(const UnknownInstructionsException& src);
		UnknownInstructionsException& operator=(const UnknownInstructionsException& src);
		~UnknownInstructionsException() throw();
		const char* what() const throw ();
	};
	class DontHaveExitInstructionsException : public std::exception
	{
	private:
	public:
		DontHaveExitInstructionsException() throw();
		DontHaveExitInstructionsException(const DontHaveExitInstructionsException& src);
		DontHaveExitInstructionsException& operator=(const DontHaveExitInstructionsException& src);
		~DontHaveExitInstructionsException() throw();
		const char* what() const throw ();
	};
};
#endif
