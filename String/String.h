#pragma once
#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------------------\n"

////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////  CLASS DECLARATION - ОБЪЯВЛЕНИЕ КЛАССА  ////////////////////////////////

class String;
String operator+(const String& left, const String& right);
std::ostream& operator<<(std::ostream& os, const String& obj);
std::istream& operator>>(std::istream& is, String& obj);

class String
{
	unsigned int size;	//Размер строки в байтах.
	char* str;			//Указатель на строку в динамической памяти.
public:
	unsigned int get_size()const;
	const char* get_str()const;
	char* get_str();

	//			Constructors:
	explicit String(unsigned int size = 80);
	String(const char str[]);
	String(const String& other);
	String(String&& other);
	~String();

	//			Operators:
	String& operator=(const String& other);
	String& operator=(String&& other);	//Этот объект на момент вызова уже занимает память.
	String& operator+=(const String& other);
	const char& operator[](unsigned int i)const;
	char& operator[](unsigned int i);

	//			Methods:
	void print()const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  CLASS DECLARATION END  /////////////////////////////////////////
