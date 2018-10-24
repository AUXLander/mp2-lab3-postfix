//#ifndef __STACK_H__
//#define __STACK_H__

const int MaxStackSize = 100;

template <class Type>
class TStack{
  Type *pMem;
  int size;
  int top;
public:
	TStack(int _size): size(_size), top(-1){
		if (size < 1 || size > MaxStackSize) {
			throw size;
		}
		pMem = new Type[size];
	 }
	bool IsEmpty() {
		 return (top == -1);
	}
	bool IsFull() {
		return (top == size - 1);
	}
	Type pop() {
		return mem[t--];
	}
	void push(Type v) {
		if (IsFull()) {
			return;
		}
		return (pMem[++top] = v);
	}
	~TStack(){
		delete [] pMem;
	}
};
//#endif
