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
			throw LexicalOrSyntacticExcatrions();
	}
	catch (const OperandFactory::OverflowValueExcatrions &e)
	{
		throw e;
	}
	catch (const OperandFactory::UnderflowValueExcatrions &e)
	{
		throw e;
	}
	catch (const std::exception &e)
	{
		throw LexicalOrSyntacticExcatrions();
	}
}

void VirtualMashine::pop(void)
{
	if (this->_stack.size() == 0)
		throw ToSmallStackExcatrions("to pop the element");
	this->_stack.pop();
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
	MutantStack<const IOperand *>::iterator begin = this->_stack.begin();
	MutantStack<const IOperand *>::iterator end = this->_stack.end();
	nextElem(begin, end);
}

void VirtualMashine::getTwoTopValue(const IOperand **op1, const IOperand **op2)
{
	*op1 = this->_stack.top();
	this->_stack.pop();
	*op2 = this->_stack.top();
	this->_stack.pop();
}

void VirtualMashine::add(void)
{
	const IOperand *op1;
	const IOperand *op2;
	getTwoTopValue(&op1, &op2);
	const IOperand *res = *op1 + *op2;
	delete op1;
	delete op2;
	this->_stack.push(res);
}

void VirtualMashine::sub(void)
{
	const IOperand *op1;
	const IOperand *op2;
	getTwoTopValue(&op1, &op2);
	const IOperand *res = *op1 - *op2;
	delete op1;
	delete op2;
	this->_stack.push(res);
}

void VirtualMashine::mul(void)
{
	const IOperand *op1;
	const IOperand *op2;
	getTwoTopValue(&op1, &op2);
	const IOperand *res = *op1 * *op2;
	delete op1;
	delete op2;
	this->_stack.push(res);
}

void VirtualMashine::div(void)
{
	const IOperand *op1;
	const IOperand *op2;
	getTwoTopValue(&op1, &op2);
	try {
		const IOperand *res = *op1 / *op2;
		this->_stack.push(res);
		delete op1;
		delete op2;
	}
	catch (const OperandAbstract::DivisionOrModuloByZeroExcatrions &e)
	{
		this->_stack.push(op2);
		this->_stack.push(op1);
		throw e;
	}
}

void VirtualMashine::mod(void)
{
	const IOperand *op1;
	const IOperand *op2;
	getTwoTopValue(&op1, &op2);
	try {
		const IOperand *res = *op1 % *op2;
		this->_stack.push(res);
		delete op1;
		delete op2;
	}
	catch (const OperandAbstract::DivisionOrModuloByZeroExcatrions &e)
	{
		this->_stack.push(op2);
		this->_stack.push(op1);
		throw e;
	}
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
		}
		else
		throw AssertIsNotTrueExcatrions();
	}
}

void VirtualMashine::assert(std::string string)
{
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
		throw LexicalOrSyntacticExcatrions();
	}
	throw AssertIsNotTrueExcatrions();
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
			if (this->_stack.size() > 1 || tk == "pop" || tk == "print" || tk == "dump"){
				(this->*_functions[i])();
				return true;
			}
			throw ToSmallStackExcatrions("to execute an arithmetic instruction");
		}
	}
	if (tk == "push")
		this->push(line.substr(tk.length(), line.length()));
	else if (tk == "assert"){
		assert(line.substr(tk.length(), line.length()));
	}
	else
		throw LexicalOrSyntacticExcatrions();
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

VirtualMashine::LexicalOrSyntacticExcatrions::LexicalOrSyntacticExcatrions() throw()
{
}

const char *VirtualMashine::LexicalOrSyntacticExcatrions::what() const throw()
{
	return "Lexical or syntactic errors.";
}

VirtualMashine::LexicalOrSyntacticExcatrions::~LexicalOrSyntacticExcatrions() throw()
{
}

VirtualMashine::LexicalOrSyntacticExcatrions::LexicalOrSyntacticExcatrions(const LexicalOrSyntacticExcatrions &src)
{
	*this = src;
}

VirtualMashine::LexicalOrSyntacticExcatrions &VirtualMashine::LexicalOrSyntacticExcatrions::operator=(const LexicalOrSyntacticExcatrions &src)
{
	(void)src;
	return *this;
}

VirtualMashine::ToSmallStackExcatrions::ToSmallStackExcatrions() throw()
{
}

VirtualMashine::ToSmallStackExcatrions::ToSmallStackExcatrions(std::string mess) throw()
{
	this->_additionamMessage = mess;
}

const char *VirtualMashine::ToSmallStackExcatrions::what() const throw()
{
	return ("Too small stack " + _additionamMessage).c_str();
}

VirtualMashine::ToSmallStackExcatrions::~ToSmallStackExcatrions() throw()
{
}

VirtualMashine::ToSmallStackExcatrions::ToSmallStackExcatrions(const ToSmallStackExcatrions &src)
{
	*this = src;
}

VirtualMashine::ToSmallStackExcatrions &VirtualMashine::ToSmallStackExcatrions::operator=(const ToSmallStackExcatrions &src)
{
	this->_additionamMessage = src._additionamMessage;
	return *this;
}


VirtualMashine::AssertIsNotTrueExcatrions::AssertIsNotTrueExcatrions() throw()
{
}

const char *VirtualMashine::AssertIsNotTrueExcatrions::what() const throw()
{
	return "Assert is not true";
}

VirtualMashine::AssertIsNotTrueExcatrions::~AssertIsNotTrueExcatrions() throw()
{
}

VirtualMashine::AssertIsNotTrueExcatrions::AssertIsNotTrueExcatrions(const AssertIsNotTrueExcatrions &src)
{
	*this = src;
}

VirtualMashine::AssertIsNotTrueExcatrions &VirtualMashine::AssertIsNotTrueExcatrions::operator=(const AssertIsNotTrueExcatrions &src)
{
	(void)src;
	return *this;
}
