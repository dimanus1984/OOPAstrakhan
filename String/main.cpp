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
	unsigned int size;	//������ ������ � ������
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

	String(const char str[]) :size(strlen(str) + 1), str(new char[size] {})
	{
		//this->size = strlen(str) + 1;
		//this->str = new char[size] {};
		for (int i = 0; str[i]; i++)
			this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}

	String(const String& other) :size(other.size), str(new char[size] {})
	{
		//this->size = other.size;
		//this->str = other.str;	//���� ��� ������ � �����������!!! Shallow copy
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];	//��������� (������������, ����������) �����������
											//Deep copy.
		cout << "CopyConstructor:\t" << this << endl;
	}

	String(String&& other) :size(other.size), str(other.str)
	{
		//MoveConstructor ������ �������� ���, ��� �� ������ �������� CopyConstructor, �� ����,
		//MoveConstructor ������ ��������� DeepCopy
		//MoveConstructor ������ ��������� ShallowCopy,
		//�� ����� ���������� ������ ����� �� ��� ���������� ������
		//MoveConstructor �� ������ �������� ������������ ������!!!
		//�� ����� ������ ���������� ����������� �������, � �������� �� ������������ �������.
		//��� ����, ��������� ������ ������ �������� ������ � ������ ��������.
		//this->size = other.size;
		//this->str = other.str;
		other.str = nullptr;
		//����� �� ������ ������, ������� �� � ���� �����? ����������� �������� ������ �������� ���������
		//�� �� ������, ������� �� ���������, ��� ������� � ����������� �� ����������� ������� ������ �� ������ ������ ������.
		cout << "MoveConstructor:\t" << this << endl;
	}


	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:
	String& operator=(const String& other)// : size(other.size)	//������ ������������� ����� ������������ ������ � �������������
	{
		if (this == &other)return *this;
		//1) ������� ������ �������� �������:
		delete[] this->str;
		//2) ��������� �����������:
		this->size = other.size;		//�������� ������
		this->str = new char[size] {};	//�������� ������
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	String& operator=(String&& other)	//���� ������ �� ������ ������ ��� �������� ������.
	{
		//������� �� ������������ ������, ������� �� ��������� ������
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;	//��������, ����� ����������� ��� �� ������.
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
	String cat(left.get_size() + right.get_size() - 1);	//Size constructor //Default constructor ��������� ������ � ������� �� �������� ���������
	//cat - ��������� ������, �� ���������� ������ � �������� ������� operator+();
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
	cout << "������� ������: "; cin >> str;
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

	String str3 = str1;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef HOW_CAN_WE_CALL_CONSTRUCTORS
	String str1;	//Default constructor
	String str2 = "Hello";	//Single-argument constructor
	String str3 = str2;	//Copy constructor - ������-��� �� ������� �������
	String str4;
	str4.print();
	str4 = str3;	//Copy assignment (operator=). Copy constructor ������� ����������
					//��������� ������ str4 ��� ������.  
#endif // HOW_CAN_WE_CALL_CONSTRUCTORS


}