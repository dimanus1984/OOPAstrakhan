#include<iostream>
#include<string>
#include<regex>

using std::cout;
using std::cin;
using std::endl;

//#define NAME_CHECK
#define EMAIL_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef NAME_CHECK
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
#endif // NAME_CHECK

#ifdef EMAIL_CHECK
	std::string email;
		cout << "Type your E-mail: "; cin >> email;
	/*do
	{
		cout << "Type your E-mail: "; cin >> email;
		if (email.find('@') == std::string::npos || email.size() < 8)cout << "Not E-mail,try again. ";
	} while (email.find('@') == std::string::npos || email.size() < 8);*/
		try
		{
			//std::regex rgx("[A-Za-z.0-9]{3,30}@[A-Za-z]{1,20}(.[A-Za-z]{2,5}){1,2}");
			std::regex rgx("(\\w+)(\\.?)(\\w*)@(\\w+)(\\.)(\\w){2,5})+");
			/*std::regex rgx
			(
				"([\\w.]+)"
				"(@)"
				"([\\w.]+)"
				"(\.)"
				"([a-z]{2,5}){1,2}"
				"[\b\w\w\w\b]"
			);*/
			if (std::regex_match(email, rgx))
			{
				cout << "E-mail OK:" << email << endl;
			}
			else
			{
				cout << "Bad E-mail" << email << endl;
			}
		}
		catch (const std::exception&)
		{

		}
#endif // EMAIL_CHECK
	main();
}