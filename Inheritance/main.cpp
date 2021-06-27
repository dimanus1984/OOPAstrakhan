#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"

class Box
{
	double height, width, depth;
	string material;
public:
	Box(string material, double height, double width, double depth, string conver)
	{
		this->material = material;
		this->height = height;
		this->width = width;
		this->depth = depth;
		cout << "BConstructor:\t" << this << endl;
	}
	~Box()
	{
		cout << "BDestructor:\t" << this << endl;
	}
	void print()
	{
		cout << "Materrial:	" << material << endl;
		cout << "Dimensions:	" << height << "x" << width << "x" << depth << endl;
		cout << "Volume:		" << height * width * depth << endl;
	}
};

class GiftBox :public Box
{
	string cover;
public:
	GiftBox(string material, double height, double width, double depth, string conver):
		Box(material, height, width, depth, conver)
	{
		this->cover = cover;
		cout << "GBConstructor:\t" << this << endl;
	}
	~GiftBox()
	{
		cout << "GBDestructor:\t" << this << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Box box("Картон", 3, 4, 5,"???");
	box.print();
	
	GiftBox gift_box("Cardboard", 3, 4, 5, "With roses");
	gift_box.print();
}