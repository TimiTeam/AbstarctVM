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
    this->_functions.push_back(&VirtualMashine::pop);
    this->_functions.push_back(&VirtualMashine::dump);
    this->_functions.push_back(&VirtualMashine::add);
    this->_functions.push_back(&VirtualMashine::sub);
    this->_functions.push_back(&VirtualMashine::mul);
    this->_functions.push_back(&VirtualMashine::div);
    this->_functions.push_back(&VirtualMashine::mod);
    this->_types.insert(std::pair<std::string, eOperandType>("Int8", Int8));
    this->_types.insert(std::pair<std::string, eOperandType>("Int16", Int16));
    this->_types.insert(std::pair<std::string, eOperandType>("Int32", Int32));
    this->_types.insert(std::pair<std::string, eOperandType>("Float", Float));
    this->_types.insert(std::pair<std::string, eOperandType>("Double", Double));
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
        try
        {
            if (this->_types[type] && is_number(val))
                this->_stack.push(this->_factory.createOperand(this->_types[type], val));
        }
        catch (const OperandFactory::OverflowValueExcatrions &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const OperandFactory::UnderflowValueExcatrions &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
    }
}

void VirtualMashine::pop(void)
{
    MutantStack<const IOperand *>::iterator last = this->_stack.end();
    this->_stack.pop();
}

void nextElem(MutantStack<const IOperand *>::iterator elem, MutantStack<const IOperand *>::iterator end){
    if (elem != end){
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

void VirtualMashine::getTwoTopValue(const IOperand **op1, const IOperand **op2){
    *op1 = this->_stack.top();
    this->_stack.pop();
    *op2 = this->_stack.top();
    this->_stack.pop();
}


void VirtualMashine::add(void)
{
    if (this->_stack.size() > 1)
    {
        const IOperand *op1;
        const IOperand *op2;
        getTwoTopValue(&op1, &op2);
        const IOperand *res = *op1 + *op2;
        delete op1;
        delete op2;
        this->_stack.push(res);
    }
}

void VirtualMashine::sub(void){
    if (this->_stack.size() > 1)
    {
        const IOperand *op1;
        const IOperand *op2;
        getTwoTopValue(&op1, &op2);
        const IOperand *res = *op1 - *op2;
        delete op1;
        delete op2;
        this->_stack.push(res);
    }
}

void VirtualMashine::mul(void){
    if (this->_stack.size() > 1)
    {
        const IOperand *op1;
        const IOperand *op2;
        getTwoTopValue(&op1, &op2);
        const IOperand *res = *op1 * *op2;
        delete op1;
        delete op2;
        this->_stack.push(res);
    }
}

void VirtualMashine::div(void){
    if (this->_stack.size() > 1)
    {
        const IOperand *op1;
        const IOperand *op2;
        getTwoTopValue(&op1, &op2);
        const IOperand *res = *op1 / *op2;
        delete op1;
        delete op2;
        this->_stack.push(res);
    }
}

void VirtualMashine::mod(void){
    if (this->_stack.size() > 1)
    {
        const IOperand *op1;
        const IOperand *op2;
        getTwoTopValue(&op1, &op2);
        const IOperand *res = *op1 % *op2;
        delete op1;
        delete op2;
        this->_stack.push(res);
    }
}



bool VirtualMashine::readLine(std::string line)
{
    if (line == "exit")
        return false;
    std::string tk = line.substr(0, line.find(" "));
    if (tk == "push")
        this->push(line.substr(tk.length(), line.length()));
    for (size_t i = 0; i < this->_cmd.size(); ++i)
    {
        if (tk == this->_cmd[i])
        {
            (this->*_functions[i])();
            break;
        }
    }
    return true;
}

void VirtualMashine::readFromFile(std::string fileName)
{
}

void VirtualMashine::readFromConsole()
{
    bool run = true;
    while (run)
    {
        std::string line;
        std::getline(std::cin, line);
        run = readLine(line);
    }
}
