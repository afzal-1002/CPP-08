#include "MutantStack.hpp"

#include <iostream>
#include <list>
#include <stack>

int main()
{
	MutantStack<int> stack;
	stack.push(5);
	stack.push(17);
	std::cout << "Top: " << stack.top() << std::endl;
	stack.pop();
	std::cout << "Size after pop: " << stack.size() << std::endl;

	stack.push(3);
	stack.push(5);
	stack.push(737);
	stack.push(0);
	std::cout << "Forward:";
	for (MutantStack<int>::iterator it = stack.begin(); it != stack.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "Reverse:";
	for (MutantStack<int>::reverse_iterator it = stack.rbegin();
		it != stack.rend(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	const MutantStack<int> constStack(stack);
	std::cout << "Const iteration:";
	for (MutantStack<int>::const_iterator it = constStack.begin();
		it != constStack.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::stack<int> ordinaryStack(stack);
	std::cout << "Base stack size: " << ordinaryStack.size() << std::endl;
	return 0;
}
