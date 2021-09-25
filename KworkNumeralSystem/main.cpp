#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<double> GetTextFromFile(string fileName)
{
	ifstream in;
	in.open(fileName);
	if(in.is_open() == false)
	{
		cout << "File not fount\n";
		exit(0);
	}

	string line;
	vector<double> text;
	while(getline(in, line))
	{
		text.push_back(stod(line));
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

string ConvertToDifferentNumericSystem(int numericSystem)
{
	string res = "";
	switch(numericSystem)
	{
		case 1:
		{
			cout << "�������� ������� ���������.\n";
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