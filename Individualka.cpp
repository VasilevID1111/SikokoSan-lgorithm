#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int naibol(int* chisla_norm, int n)
{
	int max = chisla_norm[0];
	for (int i = 1; i < n + 1; i++)
	{
		if (chisla_norm[i] > max)
		{
			max = chisla_norm[i];
		}
	}
	return max;
}

void vivod_na_ekran(int* nomer, string* chisla)
{
	for (int i = 0; nomer[i] != -1; i++)
	{
		if (i % 10 == 0)
		{
			cout << "\n";
		}
		cout << chisla[nomer[i]] << " ";
	}
}

void vvodchisel(int* chisla_norm, int* nomer)
{
	for (int i = 0; i < 101; i++)
	{
		chisla_norm[i] = 0;
		nomer[i] = -1;
	}

}

void vvodizfaila(int* number, string* chisla, int& n, bool& proverka)
{
	fstream file1;
	string str, strnum, file, proverka_durak("0123456789");
	do
	{
		cout << "Введите путь к файлу" << endl;
		getline(cin, file);
		file1.open(file, ios::in);
	} while (!file1.is_open());
	int normal_number = 0, unnormal_number = 0;

	for (int i = 0; i < 10; i++)
	{
		getline(file1, str);
		if (str.size() < 5)
		{
			proverka = true;
			break;
		}
		strnum = str.substr(0, 1);
		if (proverka_durak.find(strnum, 0) == -1)
		{
			proverka = true;
			break;
		}
		normal_number = atoi(strnum.c_str());
		strnum = str.substr(4, 1);
		if (proverka_durak.find(strnum, 0) == -1)
		{
			proverka = true;
			break;
		}
		unnormal_number = atoi(strnum.c_str());
		number[normal_number] = unnormal_number;
	}


	while (!file1.eof())
	{
		if (n == 100)
		{
			proverka = true;
			break;
		}
		getline(file1, chisla[n]);
		for (int i = 0; i < chisla[n].size(); i++)
		{
			if (proverka_durak.find(chisla[n][i], 0) == -1)
			{
				proverka = true;
				break;
			}
		}
		if (proverka)
			break;
		n++;
	}
	n--;

}

void perevod(int i, string* chisla, int* chisla_norm, int* number)
{
	string symbol;
	int cifra, k = 0, mom = 0;
	for (int j = 0; j < chisla[i].size(); j++)
	{
		symbol = chisla[i].substr(j, 1);
		cifra = atoi(symbol.c_str());
		while (cifra != number[mom])
		{
			mom++;
		}
		chisla_norm[i] = chisla_norm[i] * 10 + mom;
		mom = 0;
	}
}

void sortirovka(int* chisla_norm, int* nomer, int n, int max)
{
	int min, k = 0;
	for (int i = 0; i < n + 1; i++)
	{
		min = chisla_norm[i];
		for (int j = 0; j < n + 1; j++)
		{
			if (min >= chisla_norm[j])
			{
				min = chisla_norm[j];
				k = j;
			}
		}
		nomer[i] = k;
		chisla_norm[k] = max;
	}

}

void vivodvfail(int* nomer, string* chisla)
{
	ofstream file1;
	string file;
	do
	{
		cout << "Введите название файла куда нужно вывести результаты " << endl;
		getline(cin, file);
		file1.open(file);
	} while (!file1.is_open());
	for (int i = 0; nomer[i] != -1; i++)
	{
		if ((i % 10 == 0) and (i != 0))
		{
			file1 << "\n";
		}
		if (chisla[nomer[i]]!="")
			file1 << chisla[nomer[i]] << " ";
	}
}


int main()
{
	fstream file1;
	file1.open("Sin-soi.txt", ios::in);
	string chisla[100];
	int number[10], chisla_norm[101], nomer[101];
	int j = 0, n = 0, naib = 0;
	bool proverka = false;
	setlocale(LC_ALL, "Russian");

	vvodizfaila(number, chisla, n, proverka); // ВВод числе из файла(всех)
	if (proverka)
	{
		cout << "Использован некорректный файл :(" << endl;
		return 0;
	}
	vvodchisel(chisla_norm, nomer); // Инициализация числе в 100кратном массиве



	for (int i = 0; i <= n; i++) //Перевод из Син-соя в наш
	{
		perevod(i, chisla, chisla_norm, number);
	}

	naib = naibol(chisla_norm, n) + 1; // Определение наибольшего элемента 

	sortirovka(chisla_norm, nomer, n, naib); // Сортировка уже переведенных чисел

	vivodvfail(nomer, chisla);

	// vivod_na_ekran(nomer, chisla); // Вывод на экран по 10 символов

}