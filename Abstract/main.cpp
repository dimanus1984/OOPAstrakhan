#include<iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Animal
{
	string name;
	double weight;
public:
	Animal(const string& name, double weight) :name(name), weight(weight) {}
	virtual ~Animal() {}

	virtual void sound()const = 0;	//„исто виртуальный метод.
	//Ётот метод делает класс абстрактным.
};

class Cat :public Animal
{
public:
	Cat(const string& name, double weight) :Animal(name, weight) {}
	~Cat() {}
	//Ётот тоже абстрактный кдасс, поскольку не определ€ет (не реализует) чисто виртуальный метод - sound().
};

class Tiger :public Cat
{
	unsigned int stripes;	//полоски.
public:
	Tiger(const string& name, double weight) : Cat(name, weight) {}
	~Tiger() {}
	void sound()const
	{
		cout << "Ppppppp....." << endl;
	}
};

class HomeCat :public Cat
{
public:
	HomeCat(const string& name, double weight) :Cat(name, weight) {}
	~HomeCat() {}
	void sound()const
	{
		cout << "ћ€у..." << endl;
	}
};

class Dog :public Animal
{
public:
	Dog(const string& name, double weight) :Animal(name, weight) {}
	~Dog() {}
	void sound()const
	{
		cout << "√ав..." << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal zverek("Tom", 3);	//Can not instantiate abstract class
	//Cat cat("Tom", 3);			//Can not instantiate abstract class
	Tiger tiger("Pushistik", 30);
	tiger.sound();
	HomeCat tom("Tom", 2);
	tom.sound();
	Dog dog("Tuzik", 15);
	dog.sound();
}