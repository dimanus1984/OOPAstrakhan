#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"
#define HELLO(arg) "Hello "#arg

class Point //Описывает точку на плоскости
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//					Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		//Этот конструктор с параметрами является так же конструктором по умолчанию,
		//поскольку его можно вызвать без параметров, тогда оба его параметра примут
		//значение по умолчанию, т.е. 0.
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	Point(const Point& other) //Принимает другой существующий объект по константной ссылке
	{
		//other - это просто имя принимаемого параметра или имя другого объекта
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:" << this << endl;
	}

	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//					Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//Point operator+(const Point& other)const
	//{
	//	Point result;
	//	//this->x = 123;
	//	result.x = this->x + other.x;
	//	result.y = this->y + other.y;
	//	cout << "Operator+\t" << this << endl;
	//	return result;
	//}

	Point& operator++()    //Prefix increment
	{
		this->x++;
		this->y++;
		cout << "Prefix Increment:\t" << this << endl;
		return *this;
	}

	Point operator++(int) //Postfix increment
	{
		Point old = *this;
		this->x++;
		this->y++;
		cout << "Suffix Increment:\t" << this << endl;
		return old;
	}
	//					Methods:
	double distance(const Point& other)const
	{
		this;  //точка, в которой мы сейчас находимся        (this  - этот)
		other; //точка, до которой нужно вычислить расстояние (other - другой)
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance); //sart - Squarte Root вычислить квадратный корень
		return distance;
	}

	void print()
	{
		cout << "X = " << x << tab << "Y = " << y << endl;
	}
};
//После того, как мы создали структуру можно создавать её объекты.
//Создавая структуру или класс мы создаем новый тип данных.

double distance(const Point& A, const Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}

Point operator+(const Point& left, const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	cout << "Global Plus" << endl;
	return result;
}

//#define STRUCT
//#define DISTANCE_AND_CONSTRUCTORS
//#define ASSIGNMENT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT
	int a;		//Объявление (создание) переменной 'a' типа 'int'
	Point A;    //Объявление (создание) переменной 'a' типа 'Point'
				//Создание объекта структуры Point
				//Объявление объекта структуры Point
	//Объект - это самая обычная переменная, но не примитивного типа (char, int, double...)
	//а пользовательского.
	//Объект это переменная нашего типа.
	//Объекты еще называют экземплярами класса или структуры.
	//Структуры и классы еще называют пользовательскими типами данных.
	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;
	cout << pA->x << tab << pA->y << endl;
#endif // STRUCT

#ifdef DISTANCE_AND_CONSTRUCTORS
	Point A(2.3, 4.5); //Constructor
//A.set_x(2);
//A.set_y(3);
	cout << sizeof(A) << endl;
	cout << A.get_x() << tab << A.get_y() << endl;

	Point B;			//DefaultConstructor
	B.print();

	Point C = A;		//CopyConstructor

	Point D(6.7, 8.3);
	cout << delimiter << endl;
	cout << "Расстояние от точки A до точки D: " << A.distance(D) << endl; //A - this, D - other
	cout << "Расстояние от точки D до точки A: " << D.distance(A) << endl; //D - this, A - other
	cout << "Расстояние между точками A и D:   " << distance(A, D) << endl;
	cout << "Расстояние между точками D и A:   " << distance(D, A) << endl;
	cout << delimiter << endl;

	B = D;       //CopyAssignment

	/////////////////////////////////////////////////////////////////
	cout << delimiter << endl;
	Point E = A; //CopyConstructor
	Point F;	 //DefaultConstructor
	F = D;       //CopyAssigment
	cout << delimiter << endl;
	/////////////////////////////////////////////////////////////////  
#endif // DISTANCE_AND_CONSTRUCTORS

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << tab << b << tab << c << endl;
	Point A, B, C;
	cout << delimiter << endl;
	A = B = C = Point(2.3, 4.5);		//Point(2.3, 4.5) - явный вызов конструктора.
										//Создается временный безымянный объект,
										//который существует только в пределах этого выражения.
	cout << delimiter << endl;
	//l-value = r-value;
	//  Point
	A.print();
	B.print();
	C.print();
#endif // ASSIGNMENT_CHECK

	//cout << HELLO(guy) << endl;

	int a = 2;
	int b = 3;
	int c = a + b;

	Point A(2.3, 4.5);
	Point B(2.7, 3.14);
	cout << delimiter << endl;
	Point C = A + B;
	cout << delimiter << endl;
	C.print();
	++C;
	cout << delimiter << endl;
	C.print();
	cout << delimiter << endl;
	C++;
	C.print();
}