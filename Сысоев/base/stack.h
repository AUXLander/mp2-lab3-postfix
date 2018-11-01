#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;


//Первый вошел - последний вышел
template <class Type>
class TStack{
	Type *pMem;
	int size;
	int top;
public:
	TStack(int _size): size(_size), top(-1){
		if (size < 1 || (size > MaxStackSize)) {
			throw size;
		}
		pMem = new Type[size];
	}
	TStack(TStack& c): size(c.size),top(c.top) {
		pMem = new Type[size];
		for (size_t i = 0; i < size; i++) {
			pMem[i] = c.pMem[i];
		}
	}

	bool IsEmpty() {
		 return (top == -1);
	}
	bool IsFull() {
		return (top == size - 1);
	}
	Type pop() {
		return pMem[top--];
	}
	void push(Type v) {
		if (IsFull()) {
			return;
		}
		pMem[++top] = v;
	}
	int Size() {
		return size;
	}
	int Top() {
		return top;
	}

	TStack<Type>& operator=(TStack<Type> &c) {
		if (size != c.size) {
			size = c.size;
			delete[] pMem;
			pMem = new Type[size];
		}
		top = c.top;
		for (size_t i = 0; i < size; i++) {
			pMem[i] = c.pMem[i];
		}
		return (*this);
	}

	bool operator==(const TStack<Type> &c) {
		if (size != c.size) {
			return false;
		}
		if (top != c.top) {
			return false;
		}
		for (size_t i = 0; i < size; i++) {
			if (pMem[i] != c.pMem[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const TStack<Type> &c) {
		return !(this == c);
	}
	~TStack(){
		delete [] pMem;
	}
};
#endif