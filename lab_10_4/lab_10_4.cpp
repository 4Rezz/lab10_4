#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
struct Goods
{
	char company[64];
	char towar[64];
	double price;
	double priceUAH;
};
void Create(char* fname);
void Print(char* fname);
void Exchange(char* fname, char* gname);
int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[61];
	char gname[61];
	char ch;
	do
	{
		cout << endl;
		cout << "Головне меню:" << endl;
		cout << "[1] - Введення та збереження данних;" << endl;
		cout << "[2] - Завантаження та вивід данних;" << endl;
		cout << "[3] - Добавлення ціни в гривнях;" << endl << endl;
		cout << "[0] - Завершення роботи." << endl << endl;
		cout << "Ваш вибір: "; cin >> ch; cout << endl;
			switch (ch)
			{
			case '0':
				break;
			case '1':
				cin.get(); // очищуємо буфер клавіатури – щоб не було символу
				cin.sync(); // "кінець рядка", який залишився після вводу числа
				cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
				Create(fname);
				break;
			case '2':
				cin.get(); // очищуємо буфер клавіатури – щоб не було символу
				cin.sync(); // "кінець рядка", який залишився після вводу числа
				cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
				Print(fname);
				break;
			case '3':
				cin.get(); // очищуємо буфер клавіатури – щоб не було символу
				cin.sync(); // "кінець рядка", який залишився після вводу числа
				cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
				cout << endl;
				cout << "Введіть назву другого файлу: "; cin.getline(gname, sizeof(fname));
				Exchange(fname, gname);
				break;
			default:
				cout << "Помилка введення! ";
			}
	} while (ch != '0');
	return 0;
}
void Create(char* fname)
{
	ofstream f(fname);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		return;
	}
	Goods goods;
	char ch;
	do
	{
		cout << endl;
		cout << "Фірма - виробник: "; cin.sync(); 
		cin >> goods.company; cout << endl;
		cout << "Товар: "; cin >> goods.towar; cout << endl;
		cout << "Ціна(USD): "; cin >> goods.price; cout << endl;
		if (!f.write((char*)&goods, sizeof(Goods)))
		{
			cerr << "Помилка запису у файл." << endl;
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	f.close();
}
void Print(char* fname)	{
	ifstream f(fname);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		return;
	}
	Goods goods;
	cout << endl;
	cout << "================================================================================================================" << endl;
	while (f.read((char*)&goods, sizeof(Goods)))
	{
		cout << endl;
		cout << "Фірма - виробник: " << goods.company << endl;
		cout << "Товар: " << goods.towar << endl;
		cout << "Ціна(USD): " << goods.price << "$" << endl;
		if (goods.priceUAH >= 0) {
			cout << fixed;
			cout.precision(2);
			cout << "Ціна(UAH): " << goods.priceUAH << endl;
		}
	}
	cout << endl;
	cout << "================================================================================================================" << endl;
	f.close();
}

void Exchange(char* fname, char* gname) {
	ifstream f(fname);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		return;
	}
	Goods goods;
	ofstream g(gname);
	if (!g)
	{
		cerr << "Помилка відкриття файлу '" << gname << "'" << endl;
		return;
	}
	while (f.read((char*)&goods, sizeof(Goods))) {
		goods.priceUAH = goods.price * 27.9;
		g.write((char*)&goods, sizeof(Goods));
	}
	cout << endl;
	cout << "================================================================================================================" << endl;
	cout << "Конвертація успішна! Використайте функцію виводу данних для перегляду результату!" << endl;
	cout << "================================================================================================================" << endl;
	f.close();
	g.close();
}

