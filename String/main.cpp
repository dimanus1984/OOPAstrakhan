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
	unsigned int size;	//Размер строки в байтах.
	char* str;			//Указатель на строку в динамической памяти.
public:
	unsigned int get_sizo
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
	//Если в одном конструкторе есть оператор new, то оператор new будет во всех конструкторах.
	//Обычно получается именно таким образом, если есть указатель - это как правило указатель
	//на динамическую память, значит каждый конструктор должен выделять память.
	explicit String(unsigned int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "SizeConstructor:\t" << this << endl;
	}

	String(const char str[])
	{
		this->size = strlen(str) + 1;	//Измеряем длину строки.
		this->str = new char[size] {};	//Выделяем память.
		for (int i = 0; str[i]; i++)	//Копируем, то что мы получили как параметр в нашу строку.
			this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}

	//Конструктор копирования принимает константную ссылку на объект.
	String(const String& other)
	{
		this->size = other.size;
		//this->str = other.str;	//Нельзя так делать с указателями!!! Shallow copy (мелкое копирование)
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];	//Побитовое (поэлементное, побайтовое) копирование
											//Deep copy (глубокое копирование).
		cout << "CopyConstructor:\t" << this << endl;
	}

	String(String&& other)
	{
		//MoveConstructor должен работать так, как НЕ должен работать CopyConstructor, то есть,
		//CopyConstructor должен выполнять DeepCopy
		//MoveConstructor должен выполнять ShallowCopy, т.е. копировать только адрес на уже выделенную память
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
		//0) Проверяем, не является ли this и other одним и тем же объектом:
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

	//Оператор '+=' перегружаем в классе потому-что он изменяет операнд слева
	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	//Оператор квадратные скобки '[]' возвращает указатель, значение по номеру или по индексу.
	//Оператор квадратные скобки '[]' принимает индекс
	//Константный оператор квадратные скобки '[]', который возвращает константную ссылку
	const char& operator[](unsigned int i)const
	{
		return str[i];
	}
	//Неконстантный оператор квадратные скобки '[]', который возвращает просто ссылку
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

//Оператор '+' перегружаем за классом, потому-что оператор '+' не должен изменять свои операнды.
String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);	//Size constructor
	//cat - локальный объект, он существует только в пределах функции operator+();
	for (int i = 0; i < left.get_size(); i++)
		//cat.get_str()[i] = left.get_str()[i];
		cat[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		//cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];
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
//#define OPERATOR_PLUS_CHECK
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
	//String str3;			//Default constructor
	//str3 = str1 + str2;	//Move assignment
	//cout << delimiter << endl;
	//cout << str3 << endl;

	str1 += str2;
	cout << str1 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef HOW_CAN_WE_CALL_CONSTRUCTORS
	String str1;			//Default constructor
	//"Hello" - строковая констаната преобразуется в объект класса string
	String str2 = "Hello";	//Single-argument constructor, он отвечает за преобразование других типов в наш тип.
	String str3 = str2;		//Copy constructor, потому-что мы создаем объект.
	String str4;
	str4.print();
	str4 = str3;			//Copy assignment (operator=). Copy constructor вызвать невозможно
							//поскольку объект str4 уже создан и мы присваиваем ему значение.
	//Объявление функции str5, которая ничего не принимает, и возвращает значение типа String.
	//String str(5); - вот так, явно конструктор по умолчанию вызвать НЕЛЬЗЯ.
	//В теле другой функции можно писать все что угодно, кроме реализации другой функции.
	//Мы даже можем объявить другую функцию, объявить можно функцию, но реализовать ее НЕЛЬЗЯ.
	String str(5);			//НЕ Default constructor, здесь вообще не создается объект
	String str6{};			//Default constructor - явный вызов конструктора по умолчанию.
#endif // HOW_CAN_WE_CALL_CONSTRUCTORS
}