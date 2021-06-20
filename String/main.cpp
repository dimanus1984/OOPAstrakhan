#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"

class String;
String operator+(const String& left, const String& right);

class String
{
	unsigned int size;	//Размер строки в байтах
	char* str;			//
public:
	unsigned int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	//			Constructors:
	explicit String(unsigned int size = 80) :size(size), str(new char[size] {})
	{
		//this->size = size;
		//this->str = new char[size] {};
		cout << "SizeConstructor:\t" << this << endl;
	}

	String(const char str[]) :String(strlen(str) + 1)
	{
		for (int i = 0; str[i]; i++)
			this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}

	String(const String& other) :String(other.str)
	{
		//this->size = other.size;
		//this->str = other.str;	//Низя так делать с указателями!!! Shallow copy
		//this->str = new char[size] {};
		//for (int i = 0; i < size; i++)
			//this->str[i] = other.str[i];	//Побитовое (поэдементное, побайтовое) копирование
											//Deep copy.
		cout << "CopyConstructor:\t" << this << endl;
	}

	String(String&& other)
	{
		//MoveConstructor должен работать так, как НЕ должен работать CopyConstructor, то есть,
		//MoveConstructor должен выполнять DeepCopy
		//MoveConstructor должен выполнять ShallowCopy,
		//то естоь копировать только адрес на уже выделенную память
		//MoveConstructor НЕ ДОЛЖЕН ВЫДЕЛЯТЬ ДИНАМИЧЕСКУЮ ПАМЯТЬ!!!
		//он берет память временного безымянного объекта, и передает ее создаваемому объекту.
		//При этом, временный объект должен потерять доступ к своему значению.
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		//чтобы не удалял память, которую мы у него взяли? конструктор переноса должен занулить указатель
		//на ту память, которую мы переносим, вот поэтому и принимается не константная двойная ссылка на объект нашего класса.
		cout << "MoveConstructor:\t" << this << endl;
	}


	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		//1) Удаляем старое значение объекта:
		delete[] this->str;
		//2) Выполняем копирование:
		this->size = other.size;		//Копируем размер
		this->str = new char[size] {};	//Выделяем память
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	String& operator=(String&& other)	//Этот объект на момент вызова уже занимает память.
	{
		//Удаляем ту динамическую память, которую мы принимаем сейчас
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;	//Зануляем, чтобы конструктор его не удалил.
		cout << "MoveAssignment:\t\t" << this << endl;
		return *this;
	}

	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	const char& operator[](unsigned int i)const
	{
		return str[i];
	}
	char& operator[](unsigned int i)
	{
		return str[i];
	}

	//			Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);	//Size constructor //Default constructor создается объект в который мы поместим результат
	//cat - локальный объект, он существует только в пределах функции operator+();
	for (int i = 0; i < left.get_size(); i++)
		//cat.get_str()[i] = left.get_str()[i];
		cat[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		//cat.get_str()[i + left.get_size() -1] = right.get_str()[i];
		cat[i + left.get_size() - 1] = right[i];
	return cat;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//std::istream& operator>>(std::istream& is, String& obj)
//{
//	return is >> obj.get_str();
//}

//#define CONSTRUCTORS_CHECK
//#define INPUT_CHECK
#define OPERATOR_PLUS_CHECK
//#define HOW_CAN_WE_CALL_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str;
	str.print();
	String str1 = "Hello";
	str1 = str1;
	str1.print();
	cout << str1 << endl;
	String str2 = str1;	//CopyConstructor
	str2.print();
	String str3;
	str3 = str2;		//CopyAssignment
	cout << str3 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef INPUT_CHECK
	String str;
	cout << "Введите строку: "; cin >> str;
	cout << str << endl;
#endif // INPUT_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	//cout << delimiter << endl;
	//String str3;		//Default constructor
	//str3 = str1 + str2;	//Move assignment
	//cout << delimiter << endl;
	//cout << str3 << endl;

	str1 += str2;
	cout << str1 << endl;
	cout << delimiter << endl;
	String str3 = str1;
	cout << delimiter << endl;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef HOW_CAN_WE_CALL_CONSTRUCTORS
	String str1;	//Default constructor
	String str2 = "Hello";	//Single-argument constructor
	String str3 = str2;	//Copy constructor - потому-что мы создаем объектю
	String str4;
	str4.print();
	str4 = str3;	//Copy assignment (operator=). Copy constructor вызвать невозможно
					//поскольку объект str4 уже создан.  
#endif // HOW_CAN_WE_CALL_CONSTRUCTORS


}