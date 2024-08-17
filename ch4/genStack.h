#ifndef GEN_STACK
#define GEN_STACK

#include <vector>
using std::vector;

template<class T, int capacity = 30>
class Stack
{
	private:
		vector<T> pool;

	public:
		Stack()
		{
			pool.reserve(capacity);
		}
		void clear() { pool.clear;}
		bool isEmpty() { return pool.empty();}
		T& topEl() { return pool.back();}
		T pop()
		{
			T tmp = pool.back();
			pool.pop_back();
			return tmp;
		}
		void push(const T &el) { pool.push_back(el);}
}

#endif
