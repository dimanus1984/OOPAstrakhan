#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
#include<cmath>
using std::cout;
using std::cin;
using std::endl;
using std::string;

//typedef unsigned int Color;

namespace Geometry
{
	enum Color
	{
		console_black = 0x00,
		console_white = 0xFF,//15,//0xFFFFFF00,
		console_red = 0xCC,//12,//0xFF000000,
		console_green = 0xAA,//10,//0x00FF0000,
		console_blue = 0x99,//0x0000FF00
		default_console_color = 7,

		black = 0x00000000,
		red = 0x000000FF,
		green = 0x0000AA00,
		yellow = 0x0000FFFF,
		blue = 0x00FF0000,
		grey = 0x00555555,
		white = 0x00FFFFFF,
	};
	class Shape
	{
	protected:
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		virtual void info()const = 0;
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		double set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
			return this->side;
		}
		Square(Color color, double side) :Shape(color)/*, side(set_side(side))*/
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			unsigned int default_color;
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::default_console_color);
		}

		void info()const
		{
			cout << "???????:\n";
			cout << "????? ???????: " << side << endl;
			cout << "???????:		" << get_area() << endl;
			cout << "????????:		" << get_perimeter() << endl;
			draw();
		}
	};

	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		double get_length()const
		{
			return length;
		}
		double get_width()const
		{
			return width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 1;
			this->length = length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 1;
			this->width = width;
		}

		Rectangle(Color color, double length, double width) :Shape(color)
		{
			set_length(length);
			set_width(width);
		}
		~Rectangle() {}

		double get_area()const
		{
			return length * width;
		}
		double get_perimeter()const
		{
			return (length * width) * 2;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < length; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::default_console_color);
		}
		void info()const
		{
			cout << "?????????????:\n";
			cout << "?????:    " << length << endl;
			cout << "??????:   " << width << endl;
			cout << "???????:  " << get_area() << endl;
			cout << "????????: " << get_perimeter() << endl;
			draw();
		}
	};

	class Circle :public Shape
	{
		UINT start_x;
		UINT start_y;
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 1;
			this->radius = radius;
		}
		void set_start_x(UINT x)
		{
			if (x >= 1000)x = 1000;
			start_x = x;
		}
		void set_start_y(UINT y)
		{
			if (y >= 700)y = 700;
			start_y = y;
		}
		Circle(Color color, double radius, UINT start_x = 0, UINT start_y = 0) :Shape(color)
		{
			set_radius(radius);
			set_start_x(start_x);
			set_start_y(start_y);
		}
		~Circle() {}

		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			cout << "????? ?????? ???? ???? :-)" << endl;
			HWND hwnd = GetConsoleWindow();
			//1) ??????? ??????? ??????????, ??? ??, ?? ??? ?? ????? ????????:
			//hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);
			//2) ??????? ?????, ??????? ????? ????????:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			//PS_SOLID - ???????? ?????,
			//		 5 - ??????? ? 5 ????????,
			//color (?????? ???????? RGB(100, 200, 150))

			HBRUSH hBrush = CreateSolidBrush(color);

			//3) ???????? ?? ???, ? ??? ????? ????????:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//4) ??????:
			/*int x1 = 200;
			int y1 = 200;
			int x2 = x1 + get_diameter();
			int y2 = y1 + get_diameter();
			Ellipse(hdc, x1, y1, x2, y2);*/
			Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			// ????? ????, ??? ????? ?? ?????, ?? ????? ???????:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			// ????? ????, ??? ?? ??? ??????????, ????? ?????????? ???????, ?????????? ?????????? ??????????.
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << "????:\n";
			cout << "??????: " << radius << endl;
			cout << "???????: " << get_area() << endl;
			cout << "????????: " << get_perimeter() << endl;
			draw();
		}
	};

	class Triangle :public Shape
	{
	public:
		Triangle(Color color) :Shape(color) {}
		~Triangle() {}
	};

	class EquilateralTriangle :public Triangle
	{
		UINT start_x;
		UINT start_y;
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			return side * pow(3, .5) / 2;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		void set_start_x(UINT x)
		{
			if (x >= 1000)x = 1000;
			start_x = x;
		}
		void set_start_y(UINT y)
		{
			if (y >= 700)y = 700;
			start_y = y;
		}
		EquilateralTriangle(Color color, double side, UINT start_x = 0, UINT start_y = 0) :Triangle(color)//Shape(Color)
		{
			set_side(side);
			set_start_x(start_x);
			set_start_y(start_y);
		}
		~EquilateralTriangle() {}

		double get_area()const
		{
			return side * side * pow(3, 0.5) / 4;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HBRUSH hBrush = CreateSolidBrush(color);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);

			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);

			POINT points[] =
			{
				{start_x,start_y + side},
				{start_x + side,start_y + side},
				{start_x + side / 2,start_y + side - get_height()}
			};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << "?????????????? ???????????:\n";
			cout << "????? ???????: " << side << endl;
			cout << "??????:		" << get_height() << endl;
			cout << "???????:		" << get_area() << endl;
			cout << "????????:		" << get_perimeter() << endl;
			draw();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//			Set full screen
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 80,50 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN, &buffer);*/


	//Shape shape(0xFFFFFF00);
	Geometry::Square square(Geometry::Color::console_red, 3);
	square.info();

	Geometry::Rectangle rectangle(Geometry::Color::console_green, 2, 4);
	rectangle.info();

	Geometry::Circle circle(Geometry::Color::yellow, 100, 500, 300);
	circle.info();

	Geometry::EquilateralTriangle equil_triangle(Geometry::Color::green, 200, 200, 200);
	equil_triangle.info();
}
