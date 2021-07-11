#include<iostream>
using std::cout;
using std::cin;
using std::endl;

void main()
{
	setlocale(LC_ALL, "");
	const int n = 5;
	int arr[] = { 3,5,8,13,21 };
	cout << *arr << endl;
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
}