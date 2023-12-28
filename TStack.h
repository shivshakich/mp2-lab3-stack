#pragma once

#include <iostream>

static const int MAXMAXSIZE = 100000;

using std::exception;

template <class T>
class TStack {
	T* pMem;
	int MaxSize;
	int CurrentIndex;
public:
	TStack(int ms);
	TStack(const TStack& ts);
	~TStack();

	TStack& operator=(const TStack& ts);

	int IsFull() const;
	int IsEmpty() const;

	T Pop();
	void Push(const T& elem);
	T Top() const;

	void Clear(void) { CurrentIndex = -1; }

	int Get_MaxSize() const noexcept { return MaxSize; }
	int Get_MAXMAXSIZE() const noexcept { return MAXMAXSIZE; }
			
	friend std::ostream& operator<<(std::ostream& os, const TStack& ts);
};

template <class T>				// конструктор
TStack<T>::TStack(int ms) {
	if (ms <= 0 || ms > MAXMAXSIZE)
		throw exception("ms <= 0 || ms > MAXMAXSIZE");

	pMem = new T[ms];

	if (pMem == nullptr)
		throw exception("TStack(int), cant_allocate_memory");

	MaxSize = ms;
	CurrentIndex = -1;
}

template <class T>				// конструктор копирования
TStack<T>::TStack(const TStack& ts) {		
	pMem = new T[ts.MaxSize];

	if (pMem == nullptr)
		throw exception("TStack(const TStack&), cant_allocate_memory");

	MaxSize = ts.MaxSize;
	CurrentIndex = ts.CurrentIndex;

	for (int i = 0; i <= CurrentIndex; ++i)
		pMem[i] = ts.pMem[i];
}

template <class T>				// деструктор
TStack<T>::~TStack() {
	delete[] pMem;
}

template <class T>				// оператор присваивания
TStack<T>& TStack<T>::operator=(const TStack& ts) {
	if (this == &ts)
		return *this;

	if (MaxSize != ts.MaxSize) {
		T* pointer = new T[ts.MaxSize];

		if (pointer == nullptr)
			throw exception("operator=, cant_allocate_memory");

		delete[] pMem;
		pMem = pointer;
		MaxSize = ts.MaxSize;
	}
	CurrentIndex = ts.CurrentIndex;

	for (int i = 0; i <= CurrentIndex; ++i)
		this->pMem[i] = ts.pMem[i];

	return *this;
}

template <class T>				// проверка на полноту
int TStack<T>::IsFull() const {
	return (CurrentIndex == MaxSize - 1);
}

template <class T>				// проверкак на пустоту
int TStack<T>::IsEmpty() const {
	return (CurrentIndex == -1);
}

template <class T>				// забрать top-элемент из стека
T TStack<T>::Pop() {
	if (this->IsEmpty())
		throw exception("Pop(), IsEmpty");
	
	return pMem[CurrentIndex--];
}

template <class T>				// поместить на вершину стека входящий аргумент
void TStack<T>::Push(const T& elem) {
	if (this->IsFull())
		throw exception("Push(), StackOverFlow");

	pMem[++CurrentIndex] = elem;
}

template <class T>				// выдать значение top-элемента, не удаляя его из стека
T TStack<T>::Top() const {
	return pMem[CurrentIndex];
}

template <class T>				// вывод значений стека
std::ostream& operator<<(std::ostream& os, const TStack<T>& ts) {
	for (int i = 0; i <= ts.CurrentIndex; ++i)
		os << ts.pMem[i] << std::endl;

	return os;
}