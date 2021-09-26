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

string GetDesimalResultFromBinary(string line)
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
	while(number >= 8)
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

char GetSymbolByValue(int value)
{
	vector<int> values = {10,11,12,13,14,15};
	vector<int> symbols = {'A','B','C','D','E','F'};

	for(size_t i = 0; i < symbols.size(); i++)
	{
		if(values[i] == value)
		{
			return symbols[i];
		}
	}
}

int GetValueBySymbol(char symbol)
{
	vector<char> symbols = {'A','B','C','D','E','F'};
	int value = 10;
	for(size_t i = 0; i < symbols.size(); i++)
	{
		if(symbol == symbols[i])
		{
			return value;
		}
		value++;
	}
}

string GetDecimalFromHex(string line)
{
	vector<int> numberDegrees;
	for(int i = line.size() - 2; i >= 0; i--)
	{
		if(isdigit(line[i]) == 0)
		{
			numberDegrees.push_back(GetValueBySymbol(line[i]));
		}
		else
		{
			numberDegrees.push_back((int) line[i] - 48);
		}
	}

	int degree = 1;
	int res = 0;
	for(int i = 0; i < numberDegrees.size(); i++)
	{
		res += degree * numberDegrees[i];
		degree *= 16;
	}

	return to_string(res);
}

string GetDecimalFromOctal(string line)
{
	vector<int> numberDegrees;
	for(int i = line.size() - 2; i >= 0; i--)
	{
		numberDegrees.push_back((int) line[i] - 48);
	}

	int degree = 1;
	int res = 0;
	for(int i = 0; i < numberDegrees.size(); i++)
	{
		res += degree * numberDegrees[i];
		degree *= 8;
	}
	return to_string(res);
}

string ConvertToDecimal(string line)
{
	char typeOfSystem = line[line.size() - 1];
	string res;
	switch(typeOfSystem)
	{
		case 'b':
		{
			res = GetDesimalResultFromBinary(line);
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
			res = GetDecimalFromHex(line);
			break;
		}
		case 'o':
		{
			res = GetDecimalFromOctal(line);
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

vector<string> ConvertToDecimal(vector<string> inputLines)
{
	vector<string> res;
	for(size_t i = 0; i < inputLines.size(); i++)
	{
		res.push_back(ConvertToDecimal(inputLines[i]));
	}
	return res;
}

string ConvertFractionalPart(string line, int numericSystem)
{
	int countSymbolsAfterDot = 10;
	double integer;
	string result = "";
	double fractionalPart = stod(line);

	if(numericSystem == 16)
	{
		for(size_t i = 0; i < countSymbolsAfterDot; i++)
		{
			fractionalPart *= numericSystem;
			fractionalPart = modf(fractionalPart, &integer);
			if(integer > 10)
			{
				result.push_back(GetSymbolByValue(integer));
			}
			else
			{
				result += to_string((int) integer);
			}
		}
		return result;
	}

	for(size_t i = 0; i < countSymbolsAfterDot; i++)
	{
		fractionalPart *= numericSystem;
		fractionalPart = modf(fractionalPart, &integer);
		result += to_string((int)integer);
	}

	return result;
}

string GetBineryFromIntDedimal(int number)
{
	vector<int> reversNumber;
	int integerPart;
	while(number >= 2)
	{
		integerPart = number / 2;
		reversNumber.push_back(number - integerPart * 2);
		number /= 2;
	}
	reversNumber.push_back(number);

	string res = "";
	for(int i = reversNumber.size() - 1; i >= 0; i--)
	{
		res += to_string(reversNumber[i]);
	}
	return res;
}

vector<string> GetBinaryFromDoubleDedimal(vector<string> stringNumbers)
{
	double number;
	double integerPart;
	double fractionalPart;
	vector<string> results;
	string result = "";
	for(size_t i = 0; i < stringNumbers.size(); i++)
	{
		number = stod(stringNumbers[i]);
		fractionalPart = modf(number, &integerPart);
		result = GetBineryFromIntDedimal((int) integerPart);
		result += "," + ConvertFractionalPart(to_string(fractionalPart), 2);
		results.push_back(result);
		result.clear();
	}
	return results;
}

template <typename T>
void ShowVector(vector<T> lines)
{
	for(size_t i = 0; i < lines.size(); i++)
	{
		cout << lines[i] << '\n';
	}
}

void ConvertToDifferentNumericSystem(int numericSystem)
{
	vector<string> inputFromFile = GetTextFromFile("Input task 1.txt");
	vector<string> numbersInDecimal;
	vector<string> resultsConverts;

	switch(numericSystem)
	{
		case 1:
		{
			cout << "Двоичная система счисления.\n";
			numbersInDecimal = ConvertToDecimal(inputFromFile);
			resultsConverts = GetBinaryFromDoubleDedimal(numbersInDecimal);
			ShowVector(resultsConverts);
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
				//cout << ConvertFractionalPart("0,7", 16) << '\n';
				//ShowNumericSystem();
				//userInput = GetInput();
				ConvertToDifferentNumericSystem(userInput);
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
	return 0;
}