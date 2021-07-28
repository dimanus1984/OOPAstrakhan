#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

template<typename T>class List
{
	class Element
	{
		T Data;		// �������� ��������.
		Element* pNext;	// ��������� �� ��������� �������.
		Element* pPrev;	// ��������� �� ���������� �������.
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List<T>;
	}*Head, * Tail;
	//Element* Head;		// ��������� �� ��������� ������� ������.
	//Element* Tail;		// ��������� �� �������� ������� ������.
	size_t size;			// ������ ������.
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG

		}
		//			Operators:
		bool operator==(const BaseIterator& other)const		// ��� ����� ����������� �����, ��������� �� �� �������� ������� ��� �������� ����������.
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator :public BaseIterator					// Iterator ����� ������� �������� ��� ���������.
	{
	public:
		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)	// Iterator ��������� ��������� �� ������� Temp �� ��������� �� ��������� nullptr.
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator++()	// Prefix increment.
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)	// Postfix increment. ���������� Iterator �� ��������.
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()	// Prefix decrement ����� ���������� �� ���������� �������
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstReverseIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
	};
	size_t get_size()const
	{
		return size;
	}
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp){}
		~ReverseIterator(){}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ConstReverseIterator crbegin()const
	{
		return Tail;
	}
	ConstReverseIterator crend()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit List(size_t size, T value = T()) :List()
	{
		while (size--)push_back(value);
	}
	List(const std::initializer_list<T>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	List(const List<T>& other) :List()		//CopyConstructor ��������� ����������� ������ �� ������.
	{
		//for (int i : other)push_back(i);
		for (ConstIterator it = other.cbegin(); it != other.cend(); it++)
			push_back(*it);
		cout << "LCopyConstructor:" << this << endl;
	}
	List(List<T>&& other)					// MoveConstructor
	{
		this->size = other.size;
		this->Head = other.Head;
		this->Tail = other.Tail;
		other.Head = other.Tail = nullptr;
		cout << "LMoveConstructor:" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	T& operator[](size_t index)
	{
		Element* Temp;
		if (index >= size)throw std::exception("Error: out of range");
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;	//i < size - Index - 1; - ��� ������ ���������� ���������, ������ �� ���� ������� ������.
		}
		return Temp->Data;
	}

	//			Addidng elements:
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		//Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		//Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(size_t index, T Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		// 1) ������� �� �������, �� ������� ����� �������� �������:
		Element* Temp;
		if (index < size / 2)	// ���� index < size / 2, ����� ���� �������.
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;	// ������� ����� ������, � ���� �� ������ ������.
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;	// ��������� �� ���������� �������. i < size - Index - 1; - ��� ������ ���������� ���������.
		}
		// 2) ������� ������� � �������� ��� � ������:
		Element* New = new Element(Data);
		// 1) �������� ������� � ������:
		New->pPrev = Temp->pPrev;
		New->pNext = Temp;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		//Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//			Removing elements:
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		// 1) ��������� ������� �� ������:
		Head = Head->pNext;
		// 2) ������� ������� �� ������:
		delete Head->pPrev;
		// 3) "��������" �� ��������� ��������:
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			size--;
			return;
		}
		// 1) ��������� ������� �� ������:
		Tail = Tail->pPrev;
		// 2) ������� ������� �� ������:
		delete Tail->pNext;
		// 3) �������� �� ��������� ��������:
		Tail->pNext = nullptr;
		size--;
	}

	//			Methods:
	void print()const
	{
		cout << "Head:" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "���������� ��������� ������: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail:" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "���������� ��������� ������: " << size << endl;
	}
};

template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_SYBSCRIPT
//#define HARDCORE
//#define ITERATORS_CHECK
//#define COPY_CONSTRUCTOR_CHECK
//#define COPY_ASSIGNMENT_CHECK
//#define OPERATOR_PLUS

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK
	int n; cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}

	size_t index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(index, value);

	list.print();
	list.reverse_print();
	/*list.pop_front();
	list.print();
	list.reverse_print();*/
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_SYBSCRIPT
	int n; cout << "������� ������ ������: "; cin >> n;
	List list(n);
	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	for (int i = 0; i < list.get_size(); i++)
		cout << list[i] << tab;
	cout << endl;
	for (int i = list.get_size() - 1; i >= 0; i--)
		cout << list[i] << tab;
	cout << endl;
#endif // SIZE_CONSTRUCTOR_AND_SYBSCRIPT

#ifdef HARDCORE
	List list = { 3,5,8,13,21 };
	for (int i : list)
		cout << i << tab;
	cout << endl;
#endif // HARDCORE

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
		cout << *it << tab;
	cout << endl;

	/*for (List::Iterator it = list.end(); it != list.begin(); it--)	// ������� ������ � �������� �����������.
		cout << *it << tab;
	cout << endl;*/

	for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)	// ����� ����� ����� ReverseIterator.
		cout << *rit << tab;
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef COPY_CONSTRUCTOR_CHECK
	List list = { 3,5,8,13,21 };
	list.print();
	list.reverse_print();
	List list2 = list;
	list2.print();
	list2.reverse_print();
#endif // COPY_METHODS_CHECK

#ifdef COPY_ASSIGNMENT_CHECK
	List list = { 3,5,8,13,21 };
	list = list;
	list.print();
	list.reverse_print();
	List list2;
	list2 = list;
	list2.print();
	list2.reverse_print();
#endif // COPY_ASSIGNMENT_CHECK

#ifdef OPERATOR_PLUS
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	//list3.print();
	//for(List::ConstIterator)
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS

	List<std::string> list1 = { "������","�����","��","�����","�����-���" };
	list1.print();
	List<std::string> list2 = { "�","�������","�","������","� �����" };
	list2.print();

	List<std::string> list3 = list1 + list2;
	for (std::string i : list3)cout << i << tab; cout << endl;
}