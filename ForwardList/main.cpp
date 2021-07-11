#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;			//������������� ����������� ����������.

class ForwardList
{
	Element* Head;
	size_t size;
public:
	ForwardList()				//Default constructor - ������� ������ ������.
	{
		this->Head = nullptr;	//���� ������ ��������� �� 0, �� ������ ����.
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	int operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		/*
		// ���������� �������� � ������ ������.
		// 1) ������� �������:
		Element* New = new Element(Data);
		// 2) ����������� ����� ������� � ������:
		New->pNext = Head;
		// 3) ����� ������ �������� �������� � ������, ����� ���� ����� ������� �������� ��������� ��������� ������.
		Head = New;
		*/
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)	//���� ������ ����, �������� �����, ������� ����� ��������� ������� � ������ ������.
		{
			return push_front(Data);
			//return;
		}
		// 1) ������� ����� �������
		//Element* New = new Element(Data);
		// 2) ����� �� ����� ������ (�� ���������� ��������):
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;	// ��������� �� ��������� �������.
		// 3) � pNext ���������� �������� �������� ����� ������ ��������:
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		// 1) ������� ����� �������:
		Element* New = new Element(Data);
		// 2) ������� �� ��������, ������� ��������� ����� ����������� ���������:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		// 3) ��������� ����� ������� � ������:
		// Temp - ���������� �������, ������������ ���� ��������, �� ����� �������� ����� ������� �������.
		// Temp->pNext - ��� ������� �� ����� �������� �� ��������� ����� �������.
		//Temp->pNext � ��� ����������� �������� ����� �������� �� ���� ������� � �����.
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//Removing elements:
	void pop_front()
	{
		// 1) ���������� ����� ���������� ��������
		Element* Temp = Head;
		// 2) ������� ������ �� ��������� ������� ������:
		Head = Head->pNext;
		// 3) ������� ������� �� ������:
		delete Temp;
		size--;
	}
	void pop_back()
	{
		// 1) ������� �� �������������� ��������:
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
			Temp = Temp->pNext;
		// 2) ������� ��������� ������� �� ������:
		delete Temp->pNext;
		// 3) �������, ��� ��� ����� ������:
		Temp->pNext = nullptr;
		size--;
	}

	//			Methods:
	void print()const
	{
		Element* Temp = Head;	// Temp - ��� ��������.
		while (Temp)	// �������� - ��� ��������� ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	// ������� �� ��������� �������.
		}
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ���������: " << Element::count << endl;
	}
};

//#define BASE_CHECK
#define SIZE_CONSTRUCTOR_AND_SUBSCRIPT
#define COPY_METHODS
#define INIT_LIST_LIKE_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	int index;
	int value;
	cout << "��������� ������ ������������ ��������: "; cin >> index;
	cout << "��������� �������� ������������ ��������: "; cin >> value;
	list.insert(index, value);
	list.print();

	ForwardList list2;
	list2.push_back(1024);
	list2.push_back(2048);
	list2.push_back(3072);
	list2.print();
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_SUBSCRIPT
	int n; cout << "������� ������ ������: "; cin >> n;
	ForwardList list(n);	// ��������� ������ �� n ���������
	for (int i = 0; i < list.get_size(); i++)cout << list[i] << tab;
	for (int i = 0; i < list.get_size(); i++)list[i] = rand() % 100;
	for (int i = 0; i < list.get_size(); i++)cout << list[i] << tab;
#endif // SIZE_CONSTRUCTOR_AND_SUBSCRIPT

#ifdef COPY_METHODS
	ForwardList list;
	list.push_back(3);
	list.push_back(5);
	list.push_back(8);
	list.push_back(13);
	list.push_back(21);
	//list.print();

	ForwardList list2 = list;
	list2.print();


#endif // COPY_METHODS

#ifdef INIT_LIST_LIKE_ARRAY
	ForwardList list = { 3,5,8,13,21 };
	for(int i :list)
#endif // INIT_LIST_LIKE_ARRAY

}