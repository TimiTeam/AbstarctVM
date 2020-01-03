#include "VirtualMashine.hpp"
#include <sstream>
#include <list>

VirtualMashine::VirtualMashine()
{
	this->_cmd.push_back("pop");
	this->_cmd.push_back("dump");
	this->_cmd.push_back("add");
	this->_cmd.push_back("sub");
	this->_cmd.push_back("mul");
	this->_cmd.push_back("div");
	this->_cmd.push_back("mod");
	this->_cmd.push_back("print");
	this->_functions.push_back(&VirtualMashine::pop);
	this->_functions.push_back(&VirtualMashine::dump);
	this->_functions.push_back(&VirtualMashine::add);
	this->_functions.push_back(&VirtualMashine::sub);
	this->_functions.push_back(&VirtualMashine::mul);
	this->_functions.push_back(&VirtualMashine::div);
	this->_functions.push_back(&VirtualMashine::mod);
	this->_functions.push_back(&VirtualMashine::print);
	this->_types.insert(std::pair<std::string, eOperandType>("int8", Int8));
	this->_types.insert(std::pair<std::string, eOperandType>("int16", Int16));
	this->_types.insert(std::pair<std::string, eOperandType>("int32", Int32));
	this->_types.insert(std::pair<std::string, eOperandType>("float", Float));
	this->_types.insert(std::pair<std::string, eOperandType>("double", Double));
}

VirtualMashine::VirtualMashine(const VirtualMashine &src)
{
	*this = src;
}

VirtualMashine::~VirtualMashine()
{
	MutantStack<const IOperand *>::iterator begin = this->_stack.begin();
	MutantStack<const IOperand *>::iterator end = this->_stack.end();
	while (begin != end)
	{
		delete *begin;
		++begin;
	}
}

VirtualMashine &VirtualMashine::operator=(const VirtualMashine &src)
{

	return *this;
}

bool is_number(const std::string &s)
{
	int d = 0;
	std::string::const_iterator it = s.begin();
	if (*it == '-')
		++it;
	while (it != s.end())
	{
		if (!std::isdigit(*it) && *it == '.')
			++d;
		else if (!std::isdigit(*it))
			break;
		++it;
	}
	return (!s.empty() && it == s.end() && d <= 1);
}

void VirtualMashine::push(std::string ss)
{
	try
	{
		std::string type = ss.substr(ss.find(" ") + 1, ss.find("(") - 1);
		std::string val = ss.substr(type.length() + 2, ss.find(")") - type.length() - 2);

		if (this->_types[type] && is_number(val))
			this->_stack.push(this->_factory.createOperand(this->_types[type], val));
		else
			throw LexicalOrSyntacticException();
	}
	catch (const OperandFactory::OverflowValueException &e)
	{
		throw e;
	}
	catch (const OperandFactory::UnderflowValueException &e)
	{
		throw e;
	}
	catch (const std::exception &e)
	{
		throw LexicalOrSyntacticException();
	}
}

void VirtualMashine::pop(void)
{
	if (this->_stack.size() > 0){
		this->_stack.pop();
	}
	else
		throw ToSmallStackException("to pop the element");
}

void nextElem(MutantStack<const IOperand *>::iterator elem, MutantStack<const IOperand *>::iterator end)
{
	if (elem != end)
	{
		nextElem((elem + 1), end);
		std::cout << (*elem)->toString() << std::endl;
	}
}

void VirtualMashine::dump(void)
{
	if(this->_stack.size() == 0)
		throw ToSmallStackException();
	MutantStack<const IOperand *>::iterator begin = this->_stack.begin();
	MutantStack<const IOperand *>::iterator end = this->_stack.end();
	nextElem(begin, end);
}

void VirtualMashine::getTwoTopValue(const IOperand **op1, const IOperand **op2)
{
	if (this->_stack.size() < 2)
		throw ToSmallStackException();
	*op1 = this->_stack.top();
	this->_stack.pop();
	*op2 = this->_stack.top();
	this->_stack.pop();
}

void VirtualMashine::doMathOperation(char op){
	const IOperand *op1;
	const IOperand *op2;
	getTwoTopValue(&op1, &op2);
	try{
		switch(op){
			case '+':
			this->_stack.push(*op1 + *op2);
			break ;
			case '-':
			this->_stack.push(*op1 - *op2);
			break ;
			case '/':
			this->_stack.push(*op1 / *op2);
			break ;
			case '*':
			this->_stack.push(*op1 * *op2);
			break ;
			case '%':
			this->_stack.push(*op1 % *op2);
			break ;
		}
	}
	catch (const ToSmallStackException &e){
		throw e;
	}
	catch (const std::exception &e){
		this->_stack.push(op2);
		this->_stack.push(op1);
		throw e;
	}
	delete op1;
	delete op2;
}

void VirtualMashine::add(void)
{
	doMathOperation('+');
}

void VirtualMashine::sub(void)
{
	doMathOperation('-');
}

void VirtualMashine::mul(void)
{
	doMathOperation('*');
}

void VirtualMashine::div(void)
{
	doMathOperation('/');
}

void VirtualMashine::mod(void)
{
	doMathOperation('%');
}

void VirtualMashine::print(void)
{
	if (this->_stack.size() > 0)
	{
		const IOperand *op = this->_stack.top();
		if (op->getType() == Int8)
		{
			int v = atoi(op->getValueAsString().c_str());
			std::cout << static_cast<char>(v) << std::endl;
			return ;
		}
		else
			throw AssertIsNotTrueException();
	}
	throw ToSmallStackException();
}

void VirtualMashine::assert(std::string string)
{
	if (this->_stack.size() < 1)
		throw ToSmallStackException();
	try
	{
		std::string t = string.substr(string.find(" ") + 1, string.find("(") - 1);
		std::string val = string.substr(t.length() + 2, string.find(")") - t.length() - 2);
		eOperandType type = _types[t];
		if (static_cast<int>(type) == 0)
			throw std::exception();
		const IOperand *top = this->_stack.top();
		if (top->getValueAsString() == val && top->getType() == type)
		{
			return;
		}
	}
	catch (const std::exception &e)
	{
		throw LexicalOrSyntacticException();
	}
	throw AssertIsNotTrueException();
}

bool VirtualMashine::readLine(std::string line)
{
	if (line == "exit")
		return false;

	std::string tk = line.substr(0, line.find(" "));
	if (tk == ";;")
		return false;
	else if (tk == ";")
		return true;
	for (size_t i = 0; i < this->_cmd.size(); ++i){
		if (tk == this->_cmd[i]){
			(this->*_functions[i])();
			return true;
		}
	}
	if (tk == "push")
		this->push(line.substr(tk.length(), line.length()));
	else if (tk == "assert"){
		assert(line.substr(tk.length(), line.length()));
	}
	else
		throw LexicalOrSyntacticException();
	return true;
}

void VirtualMashine::read(std::istream &ss)
{
	bool run = true;
	while (run)
	{
		std::string line;
		if (!std::getline(ss, line))
			throw std::exception();
		try
		{
			run = readLine(line);
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

VirtualMashine::LexicalOrSyntacticException::LexicalOrSyntacticException() throw()
{
}

const char *VirtualMashine::LexicalOrSyntacticException::what() const throw()
{
	return "Lexical or syntactic errors.";
}

VirtualMashine::LexicalOrSyntacticException::~LexicalOrSyntacticException() throw()
{
}

VirtualMashine::LexicalOrSyntacticException::LexicalOrSyntacticException(const LexicalOrSyntacticException &src)
{
	*this = src;
}

VirtualMashine::LexicalOrSyntacticException &VirtualMashine::LexicalOrSyntacticException::operator=(const LexicalOrSyntacticException &src)
{
	(void)src;
	return *this;
}

VirtualMashine::ToSmallStackException::ToSmallStackException() throw()
{
}

VirtualMashine::ToSmallStackException::ToSmallStackException(std::string mess) throw()
{
	this->_additionamMessage = mess;
}

const char *VirtualMashine::ToSmallStackException::what() const throw()
{
	return ("Too small stack");
}

VirtualMashine::ToSmallStackException::~ToSmallStackException() throw()
{
}

VirtualMashine::ToSmallStackException::ToSmallStackException(const ToSmallStackException &src)
{
	*this = src;
}

VirtualMashine::ToSmallStackException &VirtualMashine::ToSmallStackException::operator=(const ToSmallStackException &src)
{
	this->_additionamMessage = src._additionamMessage;
	return *this;
}


VirtualMashine::AssertIsNotTrueException::AssertIsNotTrueException() throw()
{
}

const char *VirtualMashine::AssertIsNotTrueException::what() const throw()
{
	return "Assert is not true";
}

VirtualMashine::AssertIsNotTrueException::~AssertIsNotTrueException() throw()
{
}

VirtualMashine::AssertIsNotTrueException::AssertIsNotTrueException(const AssertIsNotTrueException &src)
{
	*this = src;
}

VirtualMashine::AssertIsNotTrueException &VirtualMashine::AssertIsNotTrueException::operator=(const AssertIsNotTrueException &src)
{
	(void)src;
	return *this;
}
