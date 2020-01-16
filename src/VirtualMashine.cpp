#include "VirtualMashine.hpp"
#include <sstream>
#include <list>
#include <fstream>

VirtualMashine::VirtualMashine()
{
	this->_functions.insert(std::pair<std::string,fun>("pop", &VirtualMashine::pop));
	this->_functions.insert(std::pair<std::string,fun>("dump", &VirtualMashine::dump));
	this->_functions.insert(std::pair<std::string,fun>("add", &VirtualMashine::add));
	this->_functions.insert(std::pair<std::string,fun>("sub", &VirtualMashine::sub));
	this->_functions.insert(std::pair<std::string,fun>("mul", &VirtualMashine::mul));
	this->_functions.insert(std::pair<std::string,fun>("div", &VirtualMashine::div));
	this->_functions.insert(std::pair<std::string,fun>("mod", &VirtualMashine::mod));
	this->_functions.insert(std::pair<std::string,fun>("print", &VirtualMashine::print));
	this->_types.insert(std::pair<std::string, eOperandType>("int8", Int8));
	this->_types.insert(std::pair<std::string, eOperandType>("int16", Int16));
	this->_types.insert(std::pair<std::string, eOperandType>("int32", Int32));
	this->_types.insert(std::pair<std::string, eOperandType>("float", Float));
	this->_types.insert(std::pair<std::string, eOperandType>("double", Double));
	time_t now = time(0);
	tm *ltm = localtime(&now);
	this->_errorFileName = "ErrorOutputAt_"+std::to_string(1900 + ltm->tm_year)+"-"+std::to_string(ltm->tm_mon)+"-"+std::to_string(ltm->tm_mday)+"_"+std::to_string(ltm->tm_hour)+":"+std::to_string(ltm->tm_min)+":"+std::to_string(ltm->tm_sec);
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
	if (this != &src){
		this->_types = src._types;
		this->_stack = src._stack;
		this->_output = src._output;
		this->_functions = src._functions;
		this->_factory = src._factory;
		this->_errorFileName = src._errorFileName;
	}
	return *this;
}

void VirtualMashine::printErrorToFile(std::string message)
{
    std::ofstream out(this->_errorFileName, std::ios::app);
    if (out.is_open()){
        out << message << std::endl;
        out.close();
    }
}

bool is_number(const std::string &s, eOperandType type)
{
	int d = 0;
	std::string::const_iterator it = s.begin();
	if (*it == '-')
		++it;
	if (*it == '.')
		return false;
	while (it != s.end())
	{
		if (!std::isdigit(*it) && *it == '.')
			++d;
		else if (!std::isdigit(*it))
			break;
		++it;
	}
	if (type < Float && d > 0)
		return false;
	return (!s.empty() && it == s.end() && d <= 1);
}

void VirtualMashine::push(std::string ss)
{
	try{
		std::string type = ss.substr(ss.find(" ") + 1, ss.find("(") - 1);
		size_t end = ss.find_last_of(")");
		std::string val = ss.substr(type.length() + 2, end - type.length() - 2);
		if (this->_types[type] && is_number(val, this->_types[type]) && end != std::string::npos)
			this->_stack.push(this->_factory.createOperand(this->_types[type], val));
		else
			throw LexicalOrSyntacticException();
	}
	catch (const std::exception &e)
	{
		throw LexicalOrSyntacticException();
	}
}

void VirtualMashine::pop(void)
{
	if (this->_stack.size() > 0){
		const IOperand *del = this->_stack.top();
		this->_stack.pop();
		delete del;
	}
	else
		throw ToSmallStackException("to pop the element");
}

void VirtualMashine::nextElem(MutantStack<const IOperand *>::iterator elem, MutantStack<const IOperand *>::iterator end)
{
	if (elem != end)
	{
		nextElem((elem + 1), end);
		this->_output += (*elem)->toString() + "\n";
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
			this->_stack.push(*op2 + *op1);
			break ;
			case '-':
			this->_stack.push(*op2 - *op1);
			break ;
			case '/':
			this->_stack.push(*op2 / *op1);
			break ;
			case '*':
			this->_stack.push(*op2 * *op1);
			break ;
			case '%':
			this->_stack.push(*op2 % *op1);
			break ;
		}
	}
	catch (const ToSmallStackException &e){
		throw e;
	}
	catch (const OperandFactory::UnderflowValueException &e){
		this->_stack.push(op2);
		this->_stack.push(op1);
		throw e;
	}
	catch (const OperandFactory::OverflowValueException &e){
		this->_stack.push(op2);
		this->_stack.push(op1);
		throw e;
	}
	catch (const OperandAbstract::DivisionOrModuloByZeroException &e){
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
			char ch = static_cast<char>(v);
			this->_output += ch;
			this->_output += "\n";
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
		size_t end = string.find_last_of(")");
		std::string val = string.substr(t.length() + 2, end - t.length() - 2);
		eOperandType type = _types[t];
		if (static_cast<int>(type) == 0)
			throw std::exception();
		const IOperand *top = this->_stack.top();
		if (top->getValueAsString() == val && top->getType() == type)
			return;
	}
	catch (const std::exception &e)
	{
		throw LexicalOrSyntacticException();
	}
	throw AssertIsNotTrueException();
}

bool VirtualMashine::readLine(std::string line)
{
	std::string tk = line.substr(0, line.find(" "));
	if (tk.at(0) == ';')
		return true;
	if (this->_functions.find(tk) != this->_functions.end()){
		(this->*_functions[tk])();
		return true;
	}
	if (tk == "push")
		this->push(line.substr(tk.length(), line.length()));
	else if (tk == "assert"){
		assert(line.substr(tk.length(), line.length()));
	}
	else
		throw UnknownInstructionsException();
	return true;
}

void VirtualMashine::read(std::istream &ss, bool std)
{
	bool run = true;
	try
	{
		while (run)
		{
			std::string line;
			if (!std::getline(ss, line))
				throw DontHaveExitInstructionsException();
			try
			{
				if (line == "exit" && !std)
					break ;
				else if (line == "exit")
					continue;
				if (line == ";;" && std)
					break ;
				else if (line == ";;")
					continue;
				if (line.length() > 1)
					run = readLine(line);
			}
			catch (const std::exception &e)
			{
				printErrorToFile(std::string(e.what()));
			}
		}
	}
	catch(const std::exception& e)
	{
		printErrorToFile(std::string(e.what()));
	}
	std::cout << this->_output;
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

VirtualMashine::UnknownInstructionsException::UnknownInstructionsException() throw()
{
}

const char *VirtualMashine::UnknownInstructionsException::what() const throw()
{
	return "An instruction is unknown.";
}

VirtualMashine::UnknownInstructionsException::~UnknownInstructionsException() throw()
{
}

VirtualMashine::UnknownInstructionsException::UnknownInstructionsException(const UnknownInstructionsException &src)
{
	*this = src;
}

VirtualMashine::UnknownInstructionsException &VirtualMashine::UnknownInstructionsException::operator=(const UnknownInstructionsException &src)
{
	(void)src;
	return *this;
}

VirtualMashine::DontHaveExitInstructionsException::DontHaveExitInstructionsException() throw()
{
}

const char *VirtualMashine::DontHaveExitInstructionsException::what() const throw()
{
	return "Don't have exit instructions";
}

VirtualMashine::DontHaveExitInstructionsException::~DontHaveExitInstructionsException() throw()
{
}

VirtualMashine::DontHaveExitInstructionsException::DontHaveExitInstructionsException(const DontHaveExitInstructionsException &src)
{
	*this = src;
}

VirtualMashine::DontHaveExitInstructionsException &VirtualMashine::DontHaveExitInstructionsException::operator=(const DontHaveExitInstructionsException &src)
{
	(void)src;
	return *this;
}
