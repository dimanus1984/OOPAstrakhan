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

int Element::count = 0;			//Инициализация статической переменной.

class ForwardList
{
	Element* Head;
	size_t size;
public:
	ForwardList()				//Default constructor - создает пустой список.
	{
		this->Head = nullptr;	//Если голова указывает на 0, то список пуст.
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
		if (Head == nullptr)	//Если список пуст, вызываем метод, который умеет добавлять элемент в пустой список.
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
		//Temp->pNext и все последующие элементы будут сдвинуты на одну позицию в право.
		New->pNext = Temp->pNext;
		Temp->pNext = New;
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

	//			Methods:
	void print()const
	{
		Element* Temp = Head;	// Temp - это итератор.
		while (Temp)	// Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	// Переход на следующий элемент.
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
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