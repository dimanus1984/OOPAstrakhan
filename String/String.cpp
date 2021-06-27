#include"String.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////  CLASS DEFINITION - ОПРЕДЕЛЕНИЕ КЛАССА  /////////////////////////////////

unsigned int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}

//			Constructors:
String::String(unsigned int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "SizeConstructor:\t" << this << endl;
}

String::String(const char str[]) :String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++)
		this->str[i] = str[i];
	cout << "Constructor:\t\t" << this << endl;
}

String::String(const String& other) :String(other.str)
{
	//this->size = other.size;
	//this->str = other.str;	//Низя так делать с указателями!!! Shallow copy
	//this->str = new char[size] {};
	//for (int i = 0; i < size; i++)
		//this->str[i] = other.str[i];	//Побитовое (поэдементное, побайтовое) копирование
										//Deep copy.
	cout << "CopyConstructor:\t" << this << endl;
}

String::String(String&& other)
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


String::~String()
{
	delete[] this->str;
	cout << "Destructor:\t\t" << this << endl;
}

//			Operators:
String& String::operator=(const String& other)
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

String& String::operator=(String&& other)	//Этот объект на момент вызова уже занимает память.
{
	//Удаляем ту динамическую память, которую мы принимаем сейчас
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.str = nullptr;	//Зануляем, чтобы конструктор его не удалил.
	cout << "MoveAssignment:\t\t" << this << endl;
	return *this;
}

String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

const char& String::operator[](unsigned int i)const
{
	return str[i];
}
char& String::operator[](unsigned int i)
{
	return str[i];
}

//			Methods:
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

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

std::istream& operator>>(std::istream& is, String& obj)
{
	return is >> obj.get_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////  CLASS DEFINITION END (КОНЕЦ ОПРЕДЕЛЕНИЯ КЛАССА) ///////////////////////////