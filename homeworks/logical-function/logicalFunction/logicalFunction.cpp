﻿/*
Недавно на уроке информатики ученики одного из классов изучили логические или булевы функции. Напомним, что булева функция f сопоставляет значениям двух булевых аргументов, каждый из которых может быть равен 0 или 1, третье булево значение, называемое результатом. Для учеников, которые выразили желание более подробно изучать эту тему, учительница информатики на дополнительном уроке ввела в рассмотрение понятие цепного вычисления булевой функции f.
Если задана булева функция f и набор из N булевых значений a1, a2, ..., aN , то результат цепного вычисления этой булевой функции определяется следующим образом:
если N = 1, то он равен a1;
если N > 1, то он равен результату цепного вычисления булевой функции f для набора из (N–1) булевого значения f(a1,a2), a3, …, aN, который получается путем замены первых двух булевых значений в наборе из N булевых значений на единственное булево значение – результат вычисления функции f от a1 и a2.
Например, если изначально задано три булевых значения: a1 = 0, a2 = 1, a3 = 0, а функция f – ИЛИ (OR), то после первого шага получается два булевых значения (0 OR 1) и 0, то есть 1 и 0. После второго (и последнего) шага получается результат цепного вычисления, равный 1, так как 1 OR 0 = 1.
В конце дополнительного урока учительница информатики написала на доске булеву функцию f и попросила одного из учеников выбрать такие N булевых значений ai, чтобы результат цепного вычисления этой функции был равен единице. Более того, она попросила найти такой набор булевых значений, в котором число единиц было бы как можно большим.
Требуется написать программу, которая решала бы поставленную учительницей задачу. Использовать подход динамического программирования.
Ввод из файла INPUT.TXT. Первая строка содержит одно натуральное число N (2 ≤ N ≤ 100 000). Вторая строка содержит описание булевой функции в виде четырех чисел, каждое из которых – ноль или единица. Первое из них есть результат вычисления функции в случае, если оба аргумента – нули, второе – результат в случае, если первый аргумент – ноль, второй – единица, третье – результат в случае, если первый аргумент – единица, второй – ноль, а четвертый – в случае, если оба аргумента – единицы.
Вывод в файл OUTUT.TXT. Необходимо вывести строку из N символов, определяющих искомый набор булевых значений ai с максимально возможным числом единиц. Если ответов несколько, требуется вывести любой из них. Если такого набора не существует, выведите в выходной файл слово No.
Примеры
Ввод 1     Ввод 2     Ввод 3
4          5          6
0110       0100       0000

Вывод 1    Вывод 2    Вывод 3
1011       11111      No
Куликова Дарья, ПС-22. Делала в Visual Studio 2019.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> pValues;
void FindWaysToGetUnit(std::string currentSequence, int step, int currentSelection, int n, int& maxOnes, std::string& resultSequence);

int main()
{
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");
	int n;
	char value;
	inputFile >> n;
	for (int i = 0; i < 4; i++)
	{
		inputFile >> value;
		pValues.push_back(value - '0');
	}
	
	
	/*for (int i = 0; i < 4; i++)
	{
		std::cout << pValues[i] << " ";
	}*/
	

	string resultSequence = "";
	int maxOnes = 0;
	FindWaysToGetUnit("", 1, 1, n, maxOnes, resultSequence);
	if (maxOnes) outputFile << resultSequence;
	else outputFile << "No";

	return 0;
}

void FindWaysToGetUnit(std::string currentSequence, int step, int currentSelection, int n, int& maxOnes, std::string& resultSequence)
{
	int countOnes = 0;
	if (step == n)
	{
		currentSequence += to_string(currentSelection);
		for (int i = 0; i < currentSequence.size(); i++)
			if (currentSequence[i] == '1') countOnes++;
		if (countOnes > maxOnes) 
		{
			maxOnes = countOnes;
			resultSequence = currentSequence;
		}
		return;
	}

	for (int i = 0; i < 4; i++)
		if (pValues[i] == currentSelection) 
			FindWaysToGetUnit(to_string(i & 1) + currentSequence, step + 1, (i & 0b10) ? 1 : 0, n, maxOnes, resultSequence);
}

