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
	cout << "1) Перевести вводимые из файла числа (возможно, дробные) из заданной системы счисления в десятичную систему счисления.\n\n";
	cout << "2) Выполнить арифметические операции (+, -, *, /) в указанной системе счисления над (возможно, дробными) числами, вводимыми из файла.\n\n";
	cout << "3) Выйти из программы.\n\n";
}

void ShowOparation()
{
	cout << "Выберете действие:\n";
	cout << "1) + (сложение)\n";
	cout << "2) - (вычитание)\n";
	cout << "3) * (умножение)\n";
	cout << "4) / (деление)\n";
}

void ShowNumericSystem()
{
	cout << "Выберете систему счисления:\n";
	cout << "b)  2-я\n";
	cout << "o)  8-я\n";
	cout << "h)  16-я\n";
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

string GetDecimalFromDiffentSystem(string line, int numericalSystem)
{
	vector<string> integerPartBinary;
	size_t indexDot;
	string itemLine = "";
	for(size_t i = 0; i < line.size(); i++)
	{
		if(line[i] != ',')
		{
			itemLine += line[i];
			integerPartBinary.push_back(itemLine);
			itemLine.clear();
		}
		else
		{
			indexDot = i;
			break;
		}
	}

	vector<string> fractionalPartBinary;
	for(size_t i = indexDot + 1; i < line.size(); i++)
	{
		itemLine += line[i];
		fractionalPartBinary.push_back(itemLine);
		itemLine.clear();
	}

	double integerPartDecimal = 0;
	double fractionalPartDecimal = 0;
	double degree = 1;
	if(numericalSystem == 16)
	{
		double number = 0;
		for(int i = integerPartBinary.size() - 1; i >= 0; i--)
		{
			if(isdigit(integerPartBinary[i][0]) == 0)
			{
				number = GetValueBySymbol(integerPartBinary[i][0]);
			}
			else
			{
				number = ((int) line[i] - 48);
			}
			integerPartDecimal += degree * number;
			degree *= numericalSystem;
		}
		degree = 1.0 / numericalSystem;
		for(int i = 0; i < fractionalPartBinary.size(); i++)
		{
			if(isdigit(fractionalPartBinary[i][0]) == 0)
			{
				number = GetValueBySymbol(fractionalPartBinary[i][0]);
			}
			else
			{
				number = ((int) line[i] - 48);
			}
			fractionalPartDecimal += degree * number;
			degree /= numericalSystem;
		}
	}
	else
	{
		for(int i = integerPartBinary.size() - 1; i >= 0; i--)
		{
			integerPartDecimal += degree * stoi(integerPartBinary[i]);
			degree *= numericalSystem;
		}
		degree = 1.0 / numericalSystem;
		for(int i = 0; i < fractionalPartBinary.size(); i++)
		{
			fractionalPartDecimal += degree * stoi(fractionalPartBinary[i]);
			degree /= numericalSystem;
		}
	}

	return to_string(integerPartDecimal + fractionalPartDecimal);
}

string ConvertToDecimal(string line)
{
	char typeOfSystem = line[line.size() - 1];
	string newLine = "";
	for(size_t i = 0; i < line.size() - 1; i++)
	{
		newLine += line[i];
	}
	string res;
	switch(typeOfSystem)
	{
		case 'b':
		{
			res = GetDecimalFromDiffentSystem(newLine, 2);
			break;
		}
		case 'd':
		{
			res = "";
			for(size_t i = 0; i < newLine.size(); i++)
			{
				res += line[i];
			}
			break;
		}
		case 'h':
		{
			res = GetDecimalFromDiffentSystem(newLine, 16);
			break;
		}
		case 'o':
		{
			res = GetDecimalFromDiffentSystem(newLine, 8);
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

string ConvertDecimalFractionalPartTo(string line, int numericSystem)
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
		result += to_string((int) integer);
	}

	return result;
}

string GetDifferentSystemFromIntDecimal(int number, int numericSystem)
{
	vector<int> reversNumber;
	int integerPart;
	while(number >= numericSystem)
	{
		integerPart = number / numericSystem;
		reversNumber.push_back(number - integerPart * numericSystem);
		number /= numericSystem;
	}
	reversNumber.push_back(number);

	string res = "";

	if(numericSystem == 16)
	{
		for(int i = reversNumber.size() - 1; i >= 0; i--)
		{
			if(reversNumber[i] > 10)
			{
				res += GetSymbolByValue(reversNumber[i]);
			}
			else
			{
				res += to_string(reversNumber[i]);
			}
		}
	}
	else
	{
		for(int i = reversNumber.size() - 1; i >= 0; i--)
		{
			res += to_string(reversNumber[i]);
		}
	}


	return res;
}

vector<string> GetFromDoubleDedimal(vector<string> stringNumbers, string(*getConvertFromIntDecimal)(int, int), int numericSystem)
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
		result = getConvertFromIntDecimal((int) integerPart, numericSystem);
		result += "," + ConvertDecimalFractionalPartTo(to_string(fractionalPart), numericSystem);
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

void ConvertToDifferentNumericSystem(char numericSystem, vector<string> inputFromFile)
{
	vector<string> numbersInDecimal;
	vector<string> resultsConverts;

	switch(numericSystem)
	{
		case 'b':
		{
			cout << "Двоичная система счисления.\n";
			numbersInDecimal = ConvertToDecimal(inputFromFile);
			resultsConverts = GetFromDoubleDedimal(numbersInDecimal, GetDifferentSystemFromIntDecimal, 2);

			break;
		}

		case 'o':
		{
			cout << "Восмиричная система счисления.\n";
			numbersInDecimal = ConvertToDecimal(inputFromFile);
			resultsConverts = GetFromDoubleDedimal(numbersInDecimal, GetDifferentSystemFromIntDecimal, 8);
			break;
		}

		case 'h':
		{
			cout << "Шестнадцатеричная система счисления.\n";
			numbersInDecimal = ConvertToDecimal(inputFromFile);
			resultsConverts = GetFromDoubleDedimal(numbersInDecimal, GetDifferentSystemFromIntDecimal, 16);
			break;
		}

		default:
		{
			cout << "Неизвестная система счисления!\n";
			break;
		}
	}
	ShowVector(resultsConverts);
}

//string ConvertToDifferentNumericSystem(char symbolNumericSystem, vector)
//{
//	string res;
//	switch(symbolNumericSystem)
//	{
//		case '1':
//		{
//			res = GetDifferentSystemFromIntDecimal(number, 2);
//			res = GetFromDoubleDedimal(numbersInDecimal, GetDifferentSystemFromIntDecimal, 2);
//			break;
//		}
//		case '2':
//		{
//			res = GetDifferentSystemFromIntDecimal(number, 16);
//			break;
//		}
//		case '3':
//		{
//			res = GetDifferentSystemFromIntDecimal(number, 8);
//			break;
//		}
//		default:
//		{
//			cout << "Неизвестная система.\n";
//			break;
//		}
//	}
//	return res;
//}

void ShowResultOperation(int numberOfOperation)
{
	vector<string> inputFromFile = GetTextFromFile("Input task 2.txt");
	vector<string> numbersInDecimal = ConvertToDecimal(inputFromFile);;

	vector<string> resultsConverts;

	double number1 = stod(numbersInDecimal[0]);
	double number2 = stod(numbersInDecimal[1]);

	//resultsConverts.push_back();
	char numericNumer;
	switch(numberOfOperation)
	{
		case 1:
		{
			cout << "1) + (сложение)\n";
			ShowNumericSystem();
			cin >> numericNumer;
			resultsConverts.push_back(to_string(number1 + number2) + 'd');
			ConvertToDifferentNumericSystem(numericNumer, resultsConverts);
			break;
		}
		case 2:
		{
			cout << "2) - (вычитание)\n";
			ShowNumericSystem();
			cin >> numericNumer;
			resultsConverts.push_back(to_string(number1 - number2) + 'd');
			ConvertToDifferentNumericSystem(numericNumer, resultsConverts);
			break;
		}
		case 3:
		{
			cout << "3) * (умножение)\n";
			ShowNumericSystem();
			cin >> numericNumer;
			resultsConverts.push_back(to_string(number1 * number2) + 'd');
			ConvertToDifferentNumericSystem(numericNumer, resultsConverts);
			break;
		}
		case 4:
		{
			cout << "4) / (деление)\n";
			ShowNumericSystem();
			cin >> numericNumer;
			resultsConverts.push_back(to_string(number1 / number2) + 'd');
			ConvertToDifferentNumericSystem(numericNumer, resultsConverts);
			break;
		}
		default:
			break;
	}
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
	
	while(isExit == false)
	{
		ShowMenuCommand();
		char userInput;
		userInput = GetInput();
		switch(userInput)
		{
			case 1:
			{
				cout << "Преобразование.\n";
				ShowNumericSystem();
				char userInput;
				cin >> userInput;
				vector<string> inputFromFile = GetTextFromFile("Input task 1.txt");
				ConvertToDifferentNumericSystem(userInput, inputFromFile);
				break;
			}

			case 2:
			{
				cout << "Математические действия:\n";
				ShowOparation();
				int userInput;
				cin >> userInput;
				ShowResultOperation(userInput);
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
		cout << "--------------\n";
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	ShowMenu();
	return 0;
}