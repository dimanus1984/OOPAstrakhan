#include<iostream>
#include<string>
#include<regex>

using std::cout;
using std::cin;
using std::endl;

#define NAME_CHECK

void main()
{
	setlocale(LC_ALL, "");
	std::string last_name = "Tupenko";
	std::string first_name = "Vasya";
	//cout << "¬ведите фамилию, им€: "; cin >> last_name >> first_name;
	std::regex rgx("[A-Z][a-z]{1,15}");	//regex - class, rgx - object;
	if (std::regex_match(last_name.c_str(), rgx/*, std::regex_constants::match_any*/))
	{
		cout << "Surname OK:" << last_name << endl;
	}
	else
	{
		cout << "Bad surname!!!" << endl;
	}

	if (std::regex_match(first_name, rgx))
	{
		cout << "Surname OK:" << first_name << endl;
	}
	else
	{
		cout << "Bad name!!!" << endl;
	}
}