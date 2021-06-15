#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"

class Fraction;	//Class declaration - ���������� ������
Fraction operator+(Fraction left, Fraction right);	//�������� ��������� +
Fraction operator-(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);	//�������� ��������� *
Fraction operator/(Fraction left, Fraction right);

class Fraction
{
	int integer;	//����� �����
	int numerator;	//���������
	int denominator;//�����������
public:	//get/set - ������
	int get_integer()const	//����������� ����� - ��� ����� ������� �� �������� ������ ��� �������� ����������
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{	//���������� ������
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//			Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:\t" << this << endl;
	}

	Fraction(double decimal) //��������� �������� ���� double
	{
		integer = decimal;	//��������� ����� �����
		decimal -= integer;	//� ���������� decimal ��� ��� �� �����, ������� �� decimal �������� integer,
							//� ������ � decimal �������� ������ ������� �����
		denominator = 1e+9;
		numerator = decimal * denominator;
		reduce();
	}

	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->set_integer(integer);
		this->set_numerator(numerator);
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//			Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		/*this->to_improper();
		other.to_improper();
		this->numerator *= other.numerator;
		this->denominator *= other.denominator;
		this->to_proper();
		return *this;*/
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//			Increment/Decriment
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)	//Postfix increment
	{
		Fraction old = *this;	//CopyConstructor
		integer++;
		return old;
	}

	//			Type-cast operators:
	//�������� �������������� � int
	explicit operator int()const
	{
		//����������� ����� � int � ���������� int
		return integer;
	}
	//�������� �������������� � double
	operator double()const
	{
		return integer + (double)numerator / denominator;
	}

	//			Methods:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()
	{
		to_improper();
		Fraction inverted(denominator, numerator);
		return inverted;
	}

	Fraction& reduce()		//��������� �����
	{
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		if (numerator == 0)

		{
			denominator = 1;
			return *this;
		}
		int more, less;
		int rest;	//������� �� �������
		//�������� ��� ������, ���������, ��� �����������:
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		//������� ���������� ����� ��������:
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		//� more ����������� GCD (Greatest Common Divider) - ���������� ����� ��������
		int GCD = more;
		//��������� �����
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}

	void print()
	{/*
		if (integer)cout << integer;
		if (integer && numerator)cout << "(";
		if (numerator)cout << numerator << "/" << denominator;
		if (integer && numerator)cout << ")";
		if (integer == 0 && numerator == 0)cout << 0;*/
		cout << integer << "(" << numerator << "/" << denominator << ")" << endl;
		cout << endl;
	}

	//��� ������� ���������� set-������, ������� ������ ������ �� ����� ������.
	//friend istream& operator>>(istream& is, Fraction& obj);

	/*friend istream& operator>>(istream& is, Fraction& obj)
	{
		int integer, numerator, denominator;
		is >> integer >> numerator >> denominator;
		obj.set_integer(integer);
		obj.set_numerator(numerator);
		obj.set_denominator(denominator);
		return is;
	}*/
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());
	result.to_proper();
	return result;*/
	return Fraction	//���� �������� ����������� � �������� � ���� ���������
	(				//���� ����������� ������� ��������� ���������� ������, ������� ����� �� ������������ return-�
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();
	Fraction result
	(
		left.get_numerator() * right.get_denominator(),
		right.get_numerator() * left.get_denominator()
	);
	return result;*/
	return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*if (left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator())
	{
		return true;
	}
	else
	{
		return false;
	}*/
	//return left.get_numerator() == right.get_numerator() && left.get_denominator() == right.get_denominator();
	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
}
bool operator!=(Fraction left, Fraction right)
{
	return !(left == right);
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())cout << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator())cout << "(";
	if (obj.get_numerator())cout << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_numerator())cout << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)cout << 0;
	return os;
}

istream& operator>>(istream& is, Fraction& obj)
{
	//return is >> obj.integer >> obj.numerator >> obj.get_denominator;

	int integer, numerator, denominator;
	integer = numerator = denominator = 0;
	char str[256]{};
	char* number[5]{};	//������ ���������� �� char
	is.getline(str, 256);	//getline ������ ������ � ���������
	const char* delimiters = " (/)";
	int i = 0;
	for (char* pch = strtok(str, delimiters); pch; pch = strtok(NULL, delimiters), i++)
	{
		//cout << pch << tab;
		number[i] = pch;
	}
	//for (number[i] = strtok(str, delimiters); number[i]; number[i++] = strtok(NULL, delimiters));	//???
	//for (int i = 0; i < 5; i++)cout << number[i] << tab; cout << endl;
	switch (i)
	{
	case 1:integer = atoi(number[0]); break;
	case 2:
		numerator = atoi(number[0]),
			denominator = atoi(number[1]); break;
	case 3:
		integer = atoi(number[0]);
		numerator = atoi(number[1]);
		denominator = atoi(number[2]); break;
	default:cout << "���-�� ����� �� ��� :-(" << endl;
	}
	//is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);
	return is;
}

//#define CONSTRUCTOR_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define INCREMENT_CHECK
//#define COMPARISON_OPERATORS_CHECK
#define TYPE_CONVERSIONS
//#define BASIC_TYPE_CONVERSIONS
//#define ISTREAM_OPERATOR
//#define OTHER_2_THIS_CONVERSIONS

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTOR_CHECK
	double a = 5; cout << a << endl;
	Fraction A = 5;
	A.print();
	Fraction B(2, 3, 4);
	B.print();
	Fraction C(1, 2);
	C.print();
	Fraction D;	//Default constructor
	D.print();
#endif // CONSTRUCTOR_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(1, 2, 3);
	/*A.to_improper();	A.print();*/
	Fraction B(19, 5);
	/*B.to_proper();	B.print();*/

	Fraction C = A * B;	C.print();
	Fraction D = A / B;	D.print();

	A *= B;	A.print();
	A /= B;	A.print();
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef INCREMENT_CHECK
	for (double i = .25; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	//for(Counter; Condition; Expression);
	//for (Fraction i(1, 4); i.get_integer() < 10; (++i).print());
	for (Fraction i(1, 4); i.get_integer() < 10; ++i)
	{
		//i.print();
		cout << i << "\t";
	}
#endif // INCREMENT_CHECK

#ifdef COMPARISON_OPERATORS_CHECK
	Fraction A(1, 2);
	Fraction B(5, 11);
	cout << (A != B) << endl;
#endif // COMPARISON_OPERATORS_CHECK

#ifdef ISTREAM_OPERATOR
	Fraction A;
	cout << "������� ����� �����, ��������� � ����������� ����� ������: ";
	cin >> A;
	cout << A << endl;
#endif // ISTREAM_OPERATOR

#ifdef TYPE_CONVERSIONS
	//https://www.cplusplus.com/doc/tutorial/typecasting/
	/*
	------------------------------------------------------
	Explicit conversions - ����� �������������� ��� ��������

	(type)value - C-like notation;
	type(value) - Functional style

	Implicit conversions - ������� ��������������
	------------------------------------------------------
	*/

#ifdef BASIC_TYPE_CONVERSIONS
	//l-value = r-value;
	int a = 2;		//No conversion
	double b = 3;	//From less to more
	int c = b;		//From more to less no data loss
	int d = 5.2;	//From more to less with data loss

	//��� ���� �� �������������
	//int* pa = a;	//cannot convert from int to int*

	cout << 2 + 3.5 << endl;		//������ double (2 ������ ����������� � double)
	cout << 5 / 2 << endl;			//������ int
	cout << double(5 / 2) << endl;	//������ int (Functional style)
	cout << (double)5 / 2 << endl;	//������ double (C-like notation)
#endif // BASIC_TYPE_CONVERSIONS

#endif // TYPE_CONVERSIONS

#ifdef OTHER_2_THIS_CONVERSIONS
	//����� ������������ - Implicit conversions
	int a = 2;			//No cenversion
	//Fraction A = a;	//From less to more
	Fraction A(a);		//explicit ����������� ����� ������� ������ ���,
						//��� ���������� ������� ���������� ���������,
						//��� ��� ������� ����������� � ����� ����������
	cout << A << endl;
	cout << \n====================================================\n << endl;
	Fraction B;			//Default constructor
	cout << delimiter << endl;
	B = (Fraction)5;
	cout << delimiter << endl;
	cout << B << endl;
	cout << \n====================================================\n << endl;
#endif // OTHER_2_THIS_CONVERSIONS

	Fraction A(2, 3, 4);
	//int a = (int)A;
	int a = A;	//���� � int ����� explicit ����������� ������� ��������������
				//������� �������������� �������� ��������� ����,
				//��� � ��� ���� ����������� � ����� ���������� ���� double
	cout << "a = " << a << endl;
	double b = A;
	cout << "b = " << b << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	Fraction C = 2.5;
	cout << C << endl;
	cout << (double)C << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	//��������� ����, ��� � ��� ���� ����������� � ����� ���������� ���� double
	//� �� �� explicit, �� '3' �.�. int ������������� ������� � double,
	//� ����� ������������� �� Fraction
	Fraction B = 3;
	B.print();
	cout << B << endl;
}