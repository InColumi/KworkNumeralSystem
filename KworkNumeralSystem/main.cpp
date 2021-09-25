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
	cout << "1) ��������� �������� �� ����� ����� (��������, �������) �� �������� ������� ��������� � ���������� ������� ���������.\n";
	cout << "2) ��������� �������������� �������� (+, -, *, /) � ��������� ������� ��������� ��� (��������, ��������) �������, ��������� �� �����.\n";
	cout << "2) ����� �� ���������.\n";
}

void ShowOparation()
{
	cout << "�������� ��������:\n";
	cout << "1) + (��������)\n";
	cout << "1) + (��������)\n";
	cout << "2) - (���������)\n";
	cout << "3) * (���������)\n";
	cout << "4) / (�������)\n";
}

void ShowNumericSystem()
{
	cout << "�������� ������� ���������:\n";
	cout << "1) 2-�\n";
	cout << "2) 8-�\n";
	cout << "3) 16-�\n";
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
			cout << "����������� �������.\n";
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
			cout << "�������� ������� ���������.\n";
			cout << number1 << '\n';
			//cout << number2 << '\n';
			break;
		}

		case 2:
		{
			cout << "����������� ������� ���������.\n";
			break;
		}

		case 3:
		{
			cout << "���������� ������� ���������.\n";
			break;
		}

		default:
		{
			cout << "����������� ������� ���������!\n";
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
			cout << "1) + (��������)\n";
			break;
		}
		case 2:
		{
			cout << "2) - (���������)\n";

			break;
		}
		case 3:
		{

			cout << "3) * (���������)\n";
			break;
		}
		case 4:
		{

			cout << "4) / (�������)\n";
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
	cout << "������� �������: ";
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
				cout << "��������������.\n";
				ShowNumericSystem();
				userInput = GetInput();
				cout << ConvertToDifferentNumericSystem(userInput) << '\n';
				break;
			}

			case 2:
			{
				cout << "�������������� ��������:\n";
				ShowNumericSystem();
				ShowOparation();
				cin >> userInput;
				cout << GetResultOperation(userInput) << '\n';
				break;
			}

			case 3:
			{
				isExit = true;
				cout << "��������� ��������� ���� ������!\n";
				break;
			}
			default:
			{
				cout << "����������� �������!\n";
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