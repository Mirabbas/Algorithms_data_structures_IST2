
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//Функция считывания с файла времен прибытия и ухода посетителей
void read_file(std::vector<int> & mas1, std::vector<int> &  mas2)
{
	std::ifstream fin;
	fin.open("ishodnik.txt");
	std::string str;
	while (!fin.eof())
	{
		char ch;
		ch = fin.get();
		if (ch != ' ' && ch != '\n' && ch != ':' && !fin.eof())
			str += ch;
		if (ch == ' ')
		{
			mas1.push_back(atoi(str.c_str()));
			str.clear();
		}
		if (ch == '\n' || fin.eof())
		{
			mas2.push_back(atoi(str.c_str()));
			str.clear();
		}
	}
}

//Функция быстрой сортировки по возрастанию
void sort(std::vector<int> & mas, int begin, int end)
{
	int left = begin, right = end;
	int piv = mas[(left + right) / 2];
	while (left <= right)
	{
		while (mas[left] < piv)
			left++;
		while (mas[right] > piv)
			right--;
		if (left <= right)
		{
			int buf = mas[left];
			mas[left] = mas[right];
			mas[right] = buf;
			left++;
			right--;
		}
	}
	if (begin < right)
		sort(mas, begin, right);
	if (end > left)
		sort(mas, left, end);
}

int main()
{
	//mas1 - вектор для хранения времен прибытия посетителей;
	//mas2 - вектор для хранения времен ухода посетителей
	std::vector<int> mas1, mas2;
	read_file(mas1, mas2);
	mas1.shrink_to_fit();
	mas2.shrink_to_fit();
	//Сортировка векторов 
	sort(mas1, 0, mas1.size() - 1);
	sort(mas2, 0, mas2.size() - 1);
	//------------------------------------------
	//time1 - время начала промежутка
	//time2 - время конца промежутка
	//maxVisitors - максимальное кол-во посетителей
	//bufMaxVisitors - дополнительная переменная 
	int time1 = mas1[0], time2 = mas2[0], i = 1, j = 1, maxVisitors = 0, bufMaxVisitors = 1;
	//Поиск промежутка времени
	while (i < mas1.size())
	{
		if (mas1[i] < mas2[j])
		{
			bufMaxVisitors++;
			if (bufMaxVisitors > maxVisitors)
			{
				time1 = mas1[i];
				maxVisitors = bufMaxVisitors;
			}
			i++;
			continue;
		}
		if (mas1[i] == mas2[j])
		{
			time2 = mas2[j + 1];
			i++;
			j++;
			continue;
		}
		if (mas1[i] > mas2[j])
		{
			if (bufMaxVisitors == maxVisitors)
				time2 = mas2[j];
			bufMaxVisitors--;
			j++;
			continue;
		}
	}
	//------------------------------------------
	//Вывод результата на экран
	std::string str;
	char bufStr[5];
	_itoa_s(time1, bufStr, 10);
	str = bufStr;
	auto it = str.end();
	it -= 2;
	str.insert(it, ':');
	std::cout << str << ' ';
	_itoa_s(time2, bufStr, 10);
	str = bufStr;
	it = str.end();
	it -= 2;
	str.insert(it, ':');
	std::cout << str << std::endl;
	system("pause");
	//------------------------------------------
	return 0;
}
