#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;		// Значение элемента.
		Element* pNext;	// Указатель на следующий элемент.
		Element* pPrev;	// Указатель на предыдущий элемент.
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
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
		friend class List;
	}*Head, * Tail;
	//Element* Head;		// Указатель на начальный элемент списка.
	//Element* Tail;		// Указатель на конечный элемент списка.
	size_t size;			// Размер списка.
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
		bool operator==(const BaseIterator& other)const		// Это будет константный метод, поскольку он не изменяет олбъект для которого вызывается.
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator :public BaseIterator					// Iterator будет простой оберткой над элементом.
	{
	public:
		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)	// Iterator принимает указатель на элемент Temp со значением по умолчанию nullptr.
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
		ConstIterator& operator++()		// Prefix increment.
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)	// Postfix increment. Возвращает Iterator по значению.
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()		// Prefix decrement будет переходить на предыдущий элемент
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
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
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
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
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp){}
		~ReverseIterator(){}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	size_t get_size()const;

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	Iterator begin();
	Iterator end();

	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	explicit List(size_t size, int value = int());
	List(const std::initializer_list<int>& il);
	List(const List& other);			//CopyConstructor принимает константную ссылку на объект.
	List(List&& other);					// MoveConstructor
	~List();

	//			Operators:
	List& operator=(const List& other);	//CopyAssignment.
	List& operator=(List& other);
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

size_t List::get_size()const
{
	return size;
}
List::ConstIterator List::cbegin()const
{
	return Head;
}
List::ConstIterator List::cend()const
{
	return nullptr;
}
List::Iterator List::begin()
{
	return Head;
}
List::Iterator List::end()
{
	return nullptr;
}

List::ConstReverseIterator List::crbegin()const
{
	return Tail;
}
List::ConstReverseIterator List::crend()const
{
	return nullptr;
}
List::ReverseIterator List::rbegin()
{
	return Tail;
}
List::ReverseIterator List::rend()
{
	return nullptr;
}
List::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
List::List(size_t size, int value) :List()
{
	while (size--)push_back(value);
}
List::List(const std::initializer_list<int>& il) :List()
{
	cout << typeid(il.begin()).name() << endl;
	for (int const* it = il.begin(); it != il.end(); it++)
		push_back(*it);
}
List::List(const List& other) :List()		//CopyConstructor принимает константную ссылку на объект.
{
	//for (int i : other)push_back(i);
	for (ConstIterator it = other.cbegin(); it != other.cend(); it++)
		push_back(*it);
	cout << "LCopyConstructor:" << this << endl;
}
List::List(List&& other)					// MoveConstructor
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "LMoveConstructor:" << this << endl;
}
List::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//			Operators:
List& List::operator=(const List& other)		// CopyAssignment.
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "CopeAssignment:\t" << this << endl;
}
List& List::operator=(List& other)				// MoveAssignment.
{
	while (Head)pop_front();
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "MoveAssignment:\t" << this << endl;
	return *this;
}
int& List::operator[](size_t index)
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
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;	//i < size - Index - 1; - это просто количество переходов, делаем на один переход меньше.
	}
	return Temp->Data;
}

//			Addidng elements:
void List::push_front(int Data)
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
void List::push_back(int Data)
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
void List::insert(size_t index, int Data)
{
	if (index > size)return;
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);
	// 1) Доходим до позиции, на которую нужно вставить элемент:
	Element* Temp;
	if (index < size / 2)	// Если index < size / 2, тогда идем сначала.
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;	// Заходим через голову, и идем по списку вперед.
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;	// Переходим на предыдущий элемент. i < size - Index - 1; - это просто количество переходов.
	}
	// 2) Создаем элемент и включаем его в список:
	Element* New = new Element(Data);
	// 1) Включаем элемент в список:
	New->pPrev = Temp->pPrev;
	New->pNext = Temp;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	//Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//			Removing elements:
void List::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	// 1) Исключаем элемент из списка:
	Head = Head->pNext;
	// 2) Удаляем элемент из списка:
	delete Head->pPrev;
	// 3) "Забываем" об удаляемом элементе:
	Head->pPrev = nullptr;
	size--;
}
void List::pop_back()
{
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
		size--;
		return;
	}
	// 1) Исключаем элемент из списка:
	Tail = Tail->pPrev;
	// 2) Удаляем элемент из списка:
	delete Tail->pNext;
	// 3) Затираем об удаляемом элементе:
	Tail->pNext = nullptr;
	size--;
}

//			Methods:
void List::print()const
{
	cout << "Head:" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
void List::reverse_print()const
{
	cout << "Tail:" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_SYBSCRIPT
//#define HARDCORE
//#define ITERATORS_CHECK
//#define COPY_CONSTRUCTOR_CHECK
//#define COPY_ASSIGNMENT_CHECK
#define OPERATOR_PLUS

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK
	int n; cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}

	size_t index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);

	list.print();
	list.reverse_print();
	/*list.pop_front();
	list.print();
	list.reverse_print();*/
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_SYBSCRIPT
	int n; cout << "Введите размер списка: "; cin >> n;
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

	/*for (List::Iterator it = list.end(); it != list.begin(); it--)	// Выводит список в обратном направлении.
		cout << *it << tab;
	cout << endl;*/

	for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)	// Здесь нужен класс ReverseIterator.
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
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	list3.print();
	//for(List::ConstIterator)
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS

}