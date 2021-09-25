#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<string> GetTextFromFile(string fileName)
{
	ifstream in;
	in.open(fileName);
	if(in.is_open() == false)
	{
		cout << "File not fount\n";
		exit(0);
	}

	string line;
	vector<string> text;
	while(getline(in, line))
	{
		text.push_back(line);
	}
	in.close();
	return text;
}

void ShowMenuCommand()
{
	cout << "1) Перевести вводимые из файла числа (возможно, дробные) из заданной системы счисления в десятичную систему счисления.\n";
	cout << "2) Выполнить арифметические операции (+, -, *, /) в указанной системе счисления над (возможно, дробными) числами, вводимыми из файла.\n";
	cout << "2) Выйти из программы.\n";
}

void ShowOparation()
{
	cout << "Выберете действие:\n";
	cout << "1) + (сложение)\n";
	cout << "1) + (сложение)\n";
	cout << "2) - (вычитание)\n";
	cout << "3) * (умножение)\n";
	cout << "4) / (деление)\n";
}

void ShowNumericSystem()
{
	cout << "Выберете систему счисления:\n";
	cout << "1) 2-я\n";
	cout << "2) 8-я\n";
	cout << "3) 16-я\n";
}

string GetDesimalResultFromBinarySystem(string line)
{
	int number = 0;
	int index = 1;
	for(size_t i = 1; i < line.size(); i++)
	{
		if(line[line.size() - i - 1] != '0')
		{
			number += index;
		}		
		index *= 2;
	}

	return to_string(number);
}

string GetOctal(int number)
{
	vector<int> numberInOctal;
	int remainder;
	while(number > 8)
	{
		remainder = number / 8;
		numberInOctal.push_back(number - remainder * 8);
		number /= 8;
	}
	numberInOctal.push_back(remainder);

	string res = "";
	for(int i = numberInOctal.size() - 1; i >= 0; i--)
	{
		res += to_string(numberInOctal[i]);
	}
	return res;
}

string ConvertToDecimalSystem(string line)
{
	char typeOfSystem = line[line.size() - 1];
	string res;
	switch(typeOfSystem)
	{
		case 'b':
		{
			res = GetDesimalResultFromBinarySystem(line);
			break;
		}
		case 'd':
		{
			res = "";
			for(size_t i = 0; i < line.size() - 1; i++)
			{
				res += line[i];
			}
			break;
		}
		case 'h':
		{
			break;
		}
		case 'o':
		{
			break;
		}
		default:
		{
			cout << "Неизвестная система.\n";
			break;
		}
	}
	return res;
}

string ConvertToDifferentNumericSystem(int numericSystem)
{
	vector<string> numbers = GetTextFromFile("Input task 1.txt");
	string number1 = ConvertToDecimalSystem(numbers[0]);
	//string number2 = ConvertToDecimalSystem(numbers[1]);
	//double number2 = numbers[1];

	string res = "";
	switch(numericSystem)
	{
		case 1:
		{
			cout << "Двоичная система счисления.\n";
			cout << number1 << '\n';
			//cout << number2 << '\n';
			break;
		}

		case 2:
		{
			cout << "Восмиричная система счисления.\n";
			break;
		}

		case 3:
		{
			cout << "Десятичная система счисления.\n";
			break;
		}

		default:
		{
			cout << "Неизвестная система счисления!\n";
			break;
		}
	}

	return res;
}

string GetResultOperation(int numberOfOperation)
{
	string res;
	switch(numberOfOperation)
	{
		case 1:
		{
			cout << "1) + (сложение)\n";
			break;
		}
		case 2:
		{
			cout << "2) - (вычитание)\n";

			break;
		}
		case 3:
		{

			cout << "3) * (умножение)\n";
			break;
		}
		case 4:
		{

			cout << "4) / (деление)\n";
			break;
		}
		default:
			break;
	}
	return res;
}

int GetInput()
{
	int res;
	cout << "Введите команду: ";
	cin >> res;
	cout << "--------------\n";
	return res;
}

void ShowMenu()
{
	bool isExit = false;
	int userInput;
	while(isExit == false)
	{
		ShowMenuCommand();
		userInput = GetInput();
		switch(userInput)
		{
			case 1:
			{
				cout << "Преобразование.\n";
				ShowNumericSystem();
				userInput = GetInput();
				cout << ConvertToDifferentNumericSystem(userInput) << '\n';
				break;
			}

			case 2:
			{
				cout << "Математические действия:\n";
				ShowNumericSystem();
				ShowOparation();
				cin >> userInput;
				cout << GetResultOperation(userInput) << '\n';
				break;
			}

			case 3:
			{
				isExit = true;
				cout << "Программа закончила свою работу!\n";
				break;
			}
			default:
			{
				cout << "Неизвестная команда!\n";
				break;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	ShowMenu();
	system("pause");
	return 0;
}