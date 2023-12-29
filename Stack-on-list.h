#pragma once

#include <iostream>
#include "TStack.h"

using std::exception;

template <class T>
struct TNode {
	T value;
	TNode* pNext = nullptr;
};

template <class T>
class TStackOnList {
	TNode<T>* pFirst;
public:
	TStackOnList();									// ����������� �� ���������
	TStackOnList(const T& value);					// ����������� �������������� ����
	TStackOnList(const TStack<T>& ts);				// ����������� �������������� ����
	TStackOnList(const TStackOnList& ts);			// ����������� �����������
	~TStackOnList();								// ����������					

	void Clear(void);																	// ������� ��� ������ �� ������
	int GetCount() const;																// ���-�� �������
	int IsEmpty() const;																// �������� �� �������

	T Pop();
	void Push(const T& elem);
	T Top() const;

	TStackOnList& operator=(const TStackOnList& ts);									// �������� �����������

	friend std::ostream& operator<<(std::ostream& os, const TStackOnList& ts);			// �����
};

// ������������ � ����������

template <class T>																			// ����������� �� ���������
TStackOnList<T>::TStackOnList() : pFirst(nullptr) {}

template <class T>																			// ����������� �������������� ����
TStackOnList<T>::TStackOnList(const T& value) {
	pFirst = new TNode<T>;
	pFirst->value = value;
}

template <class T>																			// ����������� �������������� ����
TStackOnList<T>::TStackOnList(const TStack<T>& ts) {
	pFirst = nullptr;

	TStack<T> tmp = ts;
	TNode<T>* pointer = nullptr;

	if (!tmp.IsEmpty()) {
		pFirst = new TNode<T>;
		pFirst->value = tmp.Pop();
		pointer = pFirst;

		while (!tmp.IsEmpty()) {
			pointer->pNext = new TNode<T>;
			pointer->value = tmp.Pop();
			pointer = pointer->pNext;
		}
	}
}

template <class T>																			// ����������� �����������
TStackOnList<T>::TStackOnList(const TStackOnList& ts) {
	pFirst = nullptr;

	TNode<T>* tmp;
	TNode<T>* pointer;

	if (ts.pFirst != nullptr) {
		pFirst = new TNode<T>;
		pFirst->value = ts.pFirst->value;

		tmp = pFirst;
		pointer = ts.pFirst->pNext;

		while (pointer != nullptr) {
			tmp = tmp->pNext = new TNode<T>;
			tmp->value = pointer->value;

			pointer = pointer->pNext;
		}
	}
}

template <class T>																			// ����������
TStackOnList<T>::~TStackOnList() {
	TNode<T>* current = pFirst;
	TNode<T>* tmp;

	while (current != nullptr) {
		tmp = current;
		current = current->pNext;
		delete tmp;
	}
}

// CLEAR, GETCOUNT, ISEMPTY

template <class T>
void TStackOnList<T>::Clear() {
	TNode<T>* current = pFirst;
	TNode<T>* tmp;

	while (current != nullptr) {
		tmp = current;
		current = current->pNext;
		delete tmp;
	}

	pFirst = nullptr;
}

template <class T>
int TStackOnList<T>::GetCount() const {
	int count = 0;

	TNode<T>* pCurrent = pFirst;

	while (pCurrent != nullptr) {
		++count;
		pCurrent = pCurrent->pNext;
	}

	return count;
}

template <class T>
int TStackOnList<T>::IsEmpty() const { return pFirst == nullptr; }

// POP, PUSH, TOP

template <class T>
T TStackOnList<T>::Pop() {
	if (IsEmpty())										// 0 �������
		throw "Pop, is empty";

	T res;

	if (pFirst->pNext == nullptr) {						// 1 �����
		res = pFirst->value;
		delete pFirst;
		pFirst = nullptr;
	}
	else {												// >= 2 �������
		TNode<T>* pointer = pFirst;

		while (pointer->pNext->pNext != nullptr)		// ������� ������������� �����
			pointer = pointer->pNext;

		res = pointer->pNext->value;
		delete pointer->pNext;
		pointer->pNext = nullptr;
	}

	return res;
}

template <class T>
void TStackOnList<T>::Push(const T& val) {
	if (pFirst == nullptr) {
		pFirst = new TNode<T>;
		pFirst->value = val;
	}
	else {
		TNode<T>* pointer = pFirst;

		while (pointer->pNext != nullptr)
			pointer = pointer->pNext;

		pointer = pointer->pNext = new TNode<T>;
		pointer->value = val;
	}
}

template <class T>
T TStackOnList<T>::Top() const {
	if (IsEmpty())
		throw "Top, is empty";

	TNode<T>* pointer = pFirst;

	while (pointer->pNext != nullptr)
		pointer = pointer->pNext;

	return pointer->value;
}

// OPERATOR=

template <class T>
TStackOnList<T>& TStackOnList<T>::operator=(const TStackOnList<T>& ts) {
	this->Clear();

	if (ts.IsEmpty())
		return *this;

	pFirst = new TNode<T>;
	pFirst->value = ts.pFirst->value;

	TNode<T>* p1 = pFirst;
	TNode<T>* p2 = ts.pFirst->pNext;

	while (p2 != nullptr) {
		p1 = p1->pNext = new TNode<T>;
		p1->value = p2->value;

		p2 = p2->pNext;
	}

	return *this;
}

// �����

template <class T>
std::ostream& operator<<(std::ostream& os, const TStackOnList<T>& ts) {
	TNode<T> pointer = pFirst;

	while (pointer != nullptr) {
		os << pointer->value << " ";
		pointer = pointer->pNext;
	}
}