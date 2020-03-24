/*Вычесть из каждого числа сумму всех чисел (vector). Попов И.В.*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Gener.h"

using namespace std;

//Глобальная переменная, хранящая сумму всех элементов вектора
int sumCounElInVector = 0;

//Вспомогательная функция, для вывода меню с выбором варианта записи в файл
int selectMenuTypeWriteToFile()
{
	int select = 0;
	cout << "Выберите вариант записи в файл:" << endl;
	cout << "1. Генерация чисел с использованием цикла" << endl;
	cout << "2. Генерация чисел с использованием generate" << endl;
	cout << "Введите номер пункта меню --> ";
	cin >> select;
	return select;
}

//Функция для заполнения текстового файла случайными числами
ofstream FillTextFile(string fileName, int rangeNumber, int countNumber)
{
	ofstream out(fileName); //Поток для записи в файл
	out.clear();
	int M = (rangeNumber * 2) + 1;
	if (!out.is_open())
	{
		cout << "Не удалось открыть файл!";
	}
	else
	{
		if (selectMenuTypeWriteToFile() == 1)
		{
			for (int i = 0; i < countNumber; ++i)
			{
				out << rand() % M - rangeNumber;
				out << " ";
			}
		}
		else
		{
			vector<int>vect(countNumber);
			generate(vect.begin(), vect.end(), Gener(rangeNumber));
			for (int v : vect)
			{
				out << v;
				out << " ";
			}
		}
		out.close();
	}
	return out;
}

//Вспомогательная функция для вычленения числа из строки
bool popNumberFromStr(int &cursPosit, string str, string &num)
{
	bool ok = true;
	num = "";
	int len = str.size();
	while (cursPosit < len && ok)
	{
		if (str[cursPosit] == ' ')
		{
			ok = false;
			cursPosit++;
			break;
		}
		num += str[cursPosit];
		cursPosit++;
	}
	if (num == "")
		return false;
	return true;
}

//Функция для считывания из файла в vector
vector<int> ReadFromFileToVect(ifstream *file)
{
	int cursPosit = 0, len;
	string line, num;
	getline(*file, line);
	len = line.size();
	vector<int> vect;
	while (cursPosit < len)
	{
		if (popNumberFromStr(cursPosit, line, num))
		{
			int k = atoi(num.c_str());
			vect.push_back(k);
		}
	}
	return vect;
}

//Функция для вычисления среднего арифметического вектора
void avgVect(const vector<int> &vect)
{
	int sum = 0;
	int vectSize = vect.size();
	for (int i = 0; i < vectSize; i++)
	{
		sum += vect[i];
	}
	double avg = sum / static_cast<double>(vectSize);
	cout << "Среднее арифметическое = " << avg << endl << "Сумма = " << sum << endl;
}

//Функция вывода на экран содержимого контейнера
void printVector(const vector<int> &vect)
{
	for (int v : vect)
	{
		cout << v << " ";
	}
}

/*
//Вспомогательная функция для подсчета суммы
int calculateAmount(const vector<int> &vect, int end, int beg = 0)
{
	int sum = 0;
	for (int v : vect)
	{
		sum += v;
	}
	return sum;
}*/

//Вспомогательная функция для подсчета суммы
int calculateAmount(const vector<int> &vect, int end, int beg = 0)
{
	int sum = 0;
	for (int i = beg; i < end; i++)
	{
		sum += vect[i];
	}
	return sum;
}

//Функция вычитающая из каждого числа, сумму всех чисел
vector<int> modify(vector<int> &vect)
{
	int len = vect.size();
	int sum = calculateAmount(vect, len);
	for (int i = 0; i < len; i++)
	{
		vect[i] = vect[i] - (sum - vect[i]);
	}
	return vect;
}

//Перешруженная функция modify
vector<int> modify(vector<int> &vect, int beg, int end)
{
	int sum = calculateAmount(vect, end, beg);
	for (int i = end; i < beg; i++)
	{
		vect[i] = vect[i] - (sum - vect[i]);
	}
	return vect;
}

//Вспомогательная функция, для функции transform
int helpModifyTransfotm(int num)
{
	return num - (sumCounElInVector - num);
}

//Функция вычитающая из каждого числа, сумму всех чисел, transform
vector<int> modifyTransfotm(vector<int> &vect)
{
	sumCounElInVector = calculateAmount(vect, vect.size());
	transform(vect.begin(), vect.end(), vect.begin(), helpModifyTransfotm);
	return vect;
}

//Функция вычитающая из каждого числа, сумму всех чисел, for_each
vector<int> modifyFor_each(vector<int> &vect)
{
	sumCounElInVector = calculateAmount(vect, vect.size());
	for_each(vect.begin(), vect.end(), [](int &n) {n = n - (sumCounElInVector - n);});
	return vect;
}

//Вспомогательная функция для ввода диапазона, в котором будут произвадиться вычисления функции modify
void rangeForModify(int &beg, int &end, int len)
{
	do 
	{
		cout << endl << "Введите диапазон [0.." << len << "] в котором будут производиться вычисления" << endl;
		cout << "Введите нижнюю границу - ";
		cin >> end;
		cout << endl << "Введите верхнюю границу - ";
		cin >> beg;
	} while ((end > beg) || (end < 0) || (beg > len));
}

//Вспомогательное меню, для первого пукта, основного меню
void menuFirstItemOfList(int &range, int &countNumber)
{
	cout << endl << "Введите количество чисел, которое будет генерироваться - ";
	cin >> countNumber;
	cout << endl << "Введите диапазон, в котором будут генерироваться числа - ";
	cin >> range;
}

void fmenu(string fileName)
{
	ofstream file;
	ifstream in(fileName);
	vector<int> vect;
	int select = 0;
	do
	{
		bool ok = false;
		int range = 0, countNumber = 0, beg = 0, end = 0;
		cout << "Выберите пункт меню:" << endl;
		cout << "1. Заполнить файл" << endl;
		cout << "2. Считать из файла в контейнер" << endl;
		cout << "3. Вычесть из каждого числа, сумму всех чисел" << endl;
		cout << "4. Вычесть из каждого числа, сумму всех чисел, в заданном диапазоне" << endl;
		cout << "5. Вычесть из каждого числа, сумму всех чисел, с алгоритмом transform" << endl;
		cout << "6. Вычесть из каждого числа, сумму всех чисел, c алгоритмом for_each" << endl;
		cout << "7. Вычисление суммы и среднего арифметического всех чисел" << endl;
		cout << "8. Вывести контейнер на экран" << endl << endl;
		cout << "Введите номер пункта меню --> ";
		do
		{
			cin >> select;
			if (select < 1 || select > 8)
			{
				cout << "Пункт меню выбран некорректно, повторите ввод" << endl;
				cout << "Введите номер пункта меню --> ";
			}
			else
				ok = true;
		} while (!ok);

		switch (select)
		{
		case 1:
			menuFirstItemOfList(range, countNumber);
			FillTextFile(fileName, range, countNumber);
			break;

		case 2:
			vect = ReadFromFileToVect(&in);
			break;

		case 3:
			vect = modify(vect);
			break;

		case 4:
			rangeForModify(beg, end, vect.size());
			vect = modify(vect, beg, end);
			break;

		case 5:
			modifyTransfotm(vect);
			break;

		case 6:
			modifyFor_each(vect);
			break;

		case 7:
			avgVect(vect);
			break;

		case 8:
			printVector(vect);
			break;
		}

		cout << endl << "Для возврата в главное меню введите - 0, выход - любое другое число --> ";
		cin >> select;
	} while (select == 0);
	
}

int main()
{
	setlocale(0, "");
	string fileName = "D:\\test.txt";
	fmenu(fileName);
	system("pause");
	return 0;
}