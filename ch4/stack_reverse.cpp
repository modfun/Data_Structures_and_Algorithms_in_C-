#include <iostream>
#include <stack>
#include <cstddef>

using std::cout; using std::cin; using std::endl;
using std::stack;

int main(void)
{
	return (EXIT_SUCCESS);
}

template<typename T>
void invert(stack<T> sk, stack<T> temp, int count)
{ 
	if (count <= 0)
		return; 
// stack, and temp cannot be reinitialized at any point, and the result must 
// be on stack. 
//grab the first item 
	T tempItem = sk.Pop(); 
// move count - 1 items to the temp stack. On the first pass, this is all of stack 
	for (int i = 0; i < count - 1; i++)
		temp.Push(sk.Pop()); 
// put the item that was on the top on the bottom, above previously inverted items 
	sk.Push(tempItem); 
// move everything back 
	while (temp.Count > 0)
		sk.Push(temp.Pop()); 
	invert(sk, temp, count-1); 
}

template<typename T>
void invertIterative(stack<T> sk, stack<T> temp)
{
	for (int i = sk.Count; i > 0; i--)
	{
		T tempItem = sk.Pop(); 
		for (int subCount = 0; subCount < i - 1; subCount++)
			temp.Push(sk.Pop()); 
		sk.Push(tempItem); 
		while (temp.Count > 0)
			sk.Push(temp.Pop()); 
	}
}
