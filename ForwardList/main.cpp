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

int Element::count = 0;			// Инициализация статической переменной.

class ForwardList
{
	Element* Head;
	size_t size;
public:
	ForwardList()				// Default constructor - создает пустой список.
	{
		this->Head = nullptr;	// Если голова указывает на 0, то список пуст.
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(size_t size) :ForwardList()
	{
		while (size--)push_front(0);
	}
	ForwardList(const ForwardList& other) :ForwardList()	// CopyConstructor
	{
		/*
		Element* Temp = other.Head;			// Чтобы скопировать список, нужно ходить по списку other и нужен итератор.
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		*/
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operator:
	ForwardList& operator=(const ForwardList& other)
	{
		// 0) Проверяем, НЕ является ли this и other одним и тем жеобъектом:
		if (this == &other)return *this;
		// 1) Удаляем старое значение объекта:
		while (Head)pop_front();
		// 2) Копируем ТОТ список в ЭТОТ список:
		
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		*/
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}

	int& operator[](size_t index)
	{
		if (index >= size) throw std::exception("Error: Out of range");	// бросаем исключение
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		/*
		// Добавление элемента в начало списка.
		// 1) Создаем элемент:
		Element* New = new Element(Data);
		// 2) Прикрепляем новый элемент к списку:
		New->pNext = Head;
		// 3) Адрес нового элемента помещаем в голову, после чего новый элемент является начальным элементом списка.
		Head = New;
		*/
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)	// Если список пуст, вызываем метод, который умеет добавлять элемент в пустой список.
		{
			return push_front(Data);
			//return;
		}
		// 1) Создаем новый элемент
		//Element* New = new Element(Data);
		// 2) Дойти до конца списка (до последнего элемента):
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;	// Переходим на следующий элемент.
		// 3) В pNext последнего элемента добавить адрес нового элемента:
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		// 1) Создаем новый элемент:
		Element* New = new Element(Data);
		// 2) Доходим до элемента, который находится перед добавляемым элементом:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		// 3) Вставляем новый элемент в список:
		// Temp - Предыдущий элемент, относительно того элемента, на место которого нужно сделать вставку.
		// Temp->pNext - это элемент на место которого мы вставляем новый элемент.
		// Temp->pNext и все последующие элементы будут сдвинуты на одну позицию в право.
		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//Removing elements:
	void pop_front()
	{
		// 1) Запоминаем адрес удаляемого элемента
		Element* Temp = Head;
		// 2) Смещаем голову на следующий элемент списка:
		Head = Head->pNext;
		// 3) Удаляем элемент из памяти:
		delete Temp;
		size--;
	}
	void pop_back()
	{
		// 1) Доходим до предпоследнего элемента:
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
			Temp = Temp->pNext;
		// 2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		// 3) Говорим, что это конец списка:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)									// Удаляет значение из списка по индексу, соответственно принамать он будет index.
	{
		if (index > size)return;
		if (index == 0)
		{
			pop_front();
			return;
		}
		// 1) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)					// index - 1 т.е. сделать на один переход меньше, чем индекс удаляемого элемента
			Temp = Temp->pNext;								// Дошли до нужного элемента
		// 2) Запоминаем адрес удаляемого элемента:			// Удаляем элемент из списка, если мы его исключим из списка, то мы НЕ сможем удалить его из памяти.
		Element* to_del = Temp->pNext;						// Сначало нужно исключить элемент из списка, только после этого мы можем удалить его из памяти.
		// 3) Исключаем удаляемый элемент из списка:		// Прежде чем исключить удаляемый элемент из списка, нужно сохранить его адрес куда-то,
		Temp->pNext = Temp->pNext->pNext;					// если этого не сделать, то потеряется доступ к этому элементу и удалить его из памяти не будет возможным.
		// 4) Удаляем элемент из памяти:
		delete to_del;
		size--;
	}

	//			Methods:
	void print()const
	{
		/*
		Element* Temp = Head;	// Temp - это итератор.
		while (Temp)			// Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	// Переход на следующий элемент.
		}
		*/
		//for(Start; Stop; Step)....;
		//for(Counter; Condition; Expression)....;
		//for(Iterator; Condition; Expression)....;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_SUBSCRIPT
//#define COPY_METHODS
//#define INIT_LIST_LIKE_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n; cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	int index;
	int value;
	cout << "Введедите индекс добавляемого элемента: "; cin >> index;
	cout << "Введедите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();

	ForwardList list2;
	list2.push_back(1024);
	list2.push_back(2048);
	list2.push_back(3072);
	list2.print();
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_SUBSCRIPT
	int n; cout << "Введите размер списка: "; cin >> n;
	ForwardList list(n);	// Создается список на n элементов
	for (int i = 0; i < list.get_size(); i++)cout << list[i] << tab;
	for (int i = 0; i < list.get_size(); i++)list[i] = rand() % 100;
	for (int i = 0; i < list.get_size(); i++)cout << list[i] << tab;

	int n; cout << "Введите размер списка: "; cin >> n;
	ForwardList list(n);
	try
	{
		for (int i = 0; i < n; i++)list[i] = rand() % 100;
		for (int i = 0; i < n * 2; i++)cout << list[i] << tab;
		cout << endl;
	}
	catch (const std::exception& e)	// cath - обработчик исключения
	{
		std::cerr << e.what() << endl;
	}
#endif // SIZE_CONSTRUCTOR_AND_SUBSCRIPT

#ifdef COPY_METHODS
	ForwardList list;
	list.push_back(3);
	list.push_back(5);
	list.push_back(8);
	list.push_back(13);
	list.push_back(21);

	list = list;

	list.print();

	ForwardList list2 = list;	// CopyConstructor
	list2.print();

	ForwardList list3;			// Default constructor
	list3 = list2;				// CopyAssignment
	list3.print();
#endif // COPY_METHODS

#ifdef INIT_LIST_LIKE_ARRAY
	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
#endif // INIT_LIST_LIKE_ARRAY

		/*ForwardList list;
		for (int i = 0; i < n; i++)
		{
			list.push_back(rand() % 100);
		}
		list.print();*/


	}