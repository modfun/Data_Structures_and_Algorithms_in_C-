#ifndef GEN_QSTACK
#define GEN_QSTACK

#include<queue.h>
using std::queue;

template<class T>
class QStack
{
	private:
		queue<T> pool;
	
	public:
		QStack() {}
		void clear() { pool.clear;}
		bool isEmpty() { return pool.empty();}
		T &topEl() { return pool.back();}
		T pop()
		{
			for (int i = 0; i < pool.size() -1; i++)
			{
				pool.push(pool.front());
				pool.pop();
			}
			return pool.pop();
		}
		void push(const T &el) { pool.push(el);}
};

#endif
