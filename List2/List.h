#pragma once
#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;		// �������� ��������.
		Element* pNext;	// ��������� �� ��������� �������.
		Element* pPrev;	// ��������� �� ���������� �������.
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	//Element* Head;		// ��������� �� ��������� ������� ������.
	//Element* Tail;		// ��������� �� �������� ������� ������.
	size_t size;			// ������ ������.
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp);
		~BaseIterator();
		//			Operators:
		bool operator==(const BaseIterator& other)const;		// ��� ����� ����������� �����, ��������� �� �� �������� ������� ��� �������� ����������.
		bool operator!=(const BaseIterator& other)const;
		const int& operator*()const;
	};
public:
	class ConstIterator :public BaseIterator					// Iterator ����� ������� �������� ��� ���������.
	{
	public:
		ConstIterator(Element* Temp = nullptr);	// Iterator ��������� ��������� �� ������� Temp �� ��������� �� ��������� nullptr.
		~ConstIterator();
		ConstIterator& operator++();	// Prefix increment.
		ConstIterator operator++(int);	// Postfix increment. ���������� Iterator �� ��������.
		ConstIterator& operator--();	// Prefix decrement ����� ���������� �� ���������� �������
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		int& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		int& operator*();
	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	Iterator begin();
	Iterator end();

	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	size_t get_size()const;
	List();
	explicit List(size_t size, int value = int());
	List(const std::initializer_list<int>& il);
	List(const List& other);			// CopyConstructor ��������� ����������� ������ �� ������.
	List(List&& other);					// MoveConstructor
	~List();

	//			Operators:
	int& operator[](size_t index);

	//			Addidng elements:
	void push_front(int Data);
	void push_back(int Data);
	void insert(size_t index, int Data);

	//			Removing elements:
	void pop_front();
	void pop_back();

	//			Methods:
	void print()const;
	void reverse_print()const;
};

List operator+(const List& left, const List& right);