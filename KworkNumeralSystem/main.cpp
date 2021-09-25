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

void ShowMenu()
{
	cout << "1) Перевести вводимые из файла числа (возможно, дробные) из заданной системы счисления в десятичную систему счисления.\n";
	cout << "2) Выполнить арифметические операции (+, -, *, /) в указанной системе счисления над (возможно, дробными) числами, вводимыми из файла.\n";
	cout << "2) Выйти из программы.\n";
}

int main()
{
	setlocale(LC_ALL, "rus");
	bool isExit = false;
	while(isExit == false)
	{
		cout
	}
	vector<string> inputTask1 = GetTextFromFile("Input task 1.txt");
	vector<string> inputTask2 = GetTextFromFile("Input task 2.txt");

	for(size_t i = 0; i < inputTask1.size(); i++)
	{
		cout << inputTask1[i] << endl;

	}

	cout << "-----------------------------------------------------" << endl;

	for(size_t i = 0; i < inputTask2.size(); i++)
	{
		cout << inputTask2[i] << endl;

	}

	system("pause");
	return 0;
}