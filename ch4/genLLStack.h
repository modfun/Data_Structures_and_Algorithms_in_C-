#ifndef GEN_STACK
#define GEN_STACK

#include <list>
using std::list;

template<class T, int capacity = 30>
class Stack
{
	private:
		list<T> pool;

	public:
		Stack() {}
		void clear() { pool.clear;}
		bool isEmpty() { return pool.empty();}
		T &topEl() { return pool.back();}
		T pop()
		{
			T tmp = pool.back();
			pool.pop_back();
			return tmp;
		}
		void push(const T &el) { pool.push_back(el);}
}

#endif
