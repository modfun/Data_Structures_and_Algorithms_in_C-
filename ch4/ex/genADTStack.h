#ifndef GEN_STACK
#define GEN_STACK

template<class T, class S>
class Stack
{
	private:
		S pool;

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
};

#endif
