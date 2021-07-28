#include"List.h"

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////			CLASS DEFINITION			//////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// 

/*==================================================================================================================*/

List::Element::Element(int Data, List::Element* pNext, List::Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
List::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}

/*==================================================================================================================*/

List::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG
}
List::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG
}
//			Operators:
bool List::BaseIterator::operator==(const BaseIterator& other)const		// ��� ����� ����������� �����, ��������� �� �� �������� ������� ��� �������� ����������.
{
	return this->Temp == other.Temp;
}
bool List::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
const int& List::BaseIterator::operator*()const
{
	return Temp->Data;
}

/*==================================================================================================================*/

List::ConstIterator::ConstIterator(Element* Temp) :BaseIterator(Temp)	// Iterator ��������� ��������� �� ������� Temp �� ��������� �� ��������� nullptr.
{
#ifdef DEBUG
	cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
}
List::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
}
List::ConstIterator& List::ConstIterator::operator++()		// Prefix increment.
{
	Temp = Temp->pNext;
	return *this;
}
List::ConstIterator List::ConstIterator::operator++(int)	// Postfix increment. ���������� Iterator �� ��������.
{
	ConstIterator old = *this;
	Temp = Temp->pNext;
	return old;
}
List::ConstIterator& List::ConstIterator::operator--()		// Prefix decrement ����� ���������� �� ���������� �������
{
	Temp = Temp->pPrev;
	return *this;
}
List::ConstIterator List::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}

/*==================================================================================================================*/

List::ConstReverseIterator::ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG
}
List::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG
}
List::ConstReverseIterator& List::ConstReverseIterator::operator++()
{
	Temp = Temp->pPrev;
	return *this;
}
List::ConstReverseIterator List::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}
List::ConstReverseIterator& List::ConstReverseIterator::operator--()
{
	Temp = Temp->pNext;
	return *this;
}
List::ConstReverseIterator List::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	Temp = Temp->pNext;
	return old;
}

/*==================================================================================================================*/

List::Iterator::Iterator(Element* Temp) :ConstIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
List::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}
int& List::Iterator::operator*()
{
	return Temp->Data;
}

/*==================================================================================================================*/

List::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
List::ReverseIterator::~ReverseIterator() {}
int& List::ReverseIterator::operator*()
{
	return Temp->Data;
}

/*==================================================================================================================*/

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////			List member functions			//////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////// 

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
size_t List::get_size()const
{
	return size;
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
List::List(const std::initializer_list<int>& il) : List()
{
	cout << typeid(il.begin()).name() << endl;
	for (int const* it = il.begin(); it != il.end(); it++)
		push_back(*it);
}
List::List(const List& other) :List()		//CopyConstructor ��������� ����������� ������ �� ������.
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
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;	//i < size - Index - 1; - ��� ������ ���������� ���������, ������ �� ���� ������� ������.
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
void List::pop_front()
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
void List::pop_back()
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
void List::print()const
{
	cout << "Head:" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "���������� ��������� ������: " << size << endl;
}
void List::reverse_print()const
{
	cout << "Tail:" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "���������� ��������� ������: " << size << endl;
}

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	return cat;
}