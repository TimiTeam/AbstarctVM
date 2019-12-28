#ifndef __MutantStack_HPP
# define __MutantStack_HPP

# include <iostream>
# include <stack>

template <typename T, typename Container = std::deque < T > >
class MutantStack : public std::stack<T, Container >
{
private:

public:
	typedef typename std::deque<T>::iterator iterator;

	MutantStack(){
	}

	MutantStack(const MutantStack& src){
		(void) src;
	}

	~MutantStack(){

	}

	MutantStack& operator=(const MutantStack& src){
		(void) src;
	}

	iterator end(){
		return this->c.end();
	}

	iterator begin(){
		return this->c.begin();
	}
};
#endif