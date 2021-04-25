#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "Hash.h"

using namespace std;
using namespace sheet;
void Menu();
void s_menu();
void f_menu();
int get_variant(int item);

int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream in("input.txt");
	Hash Sheet(32);
	int item;
	if (!in) {
		cout << "File not found!";
		return -1;
	}
	else {
		while (!in.eof() && in >> item) {
			Sheet.add(item);
		}
	}
	int variant;
	do {
		Menu();
		variant = get_variant(2);
		switch(variant)
		{
		case 1: {
			do {
				f_menu();
				variant = get_variant(6);
			switch (variant)
				{
				case 1: { // добавление
					int tmp;
					cout << "\nВведите ваше число: ";
					cin >> tmp;
					Sheet.add(tmp);
					system("pause");
						break;
					}
				case 2: { // Поиск
					cout << "Введите число: ";
					int tmp;
					cin >> tmp;
					bool ans=Sheet.search(tmp);
					cout << "Результат поиска :" << ans << endl;
					system("pause");
						break;
					}
				case 3: { // Удаление конкретного элемента
					int tmp;
					cout << "\nВведите число: ";
					cin >> tmp;
					Sheet.del_item(tmp);
					cout << Sheet;
					system("pause");
					break;
					}
				case 4: { // Полное удаление
					cout
						<< "Эта операция удалит уже построенную таблицу для проверки.\n"
						<< "Выполнить?\n"
						<< "1: Да\n"
						<< "2: Нет\n"
						<< "\n>>";
					int tmp = get_variant(2);
					if (tmp != 1) {
						break;
					}
					else {
						system("pause");
						Sheet.del();
						cout << Sheet;
						break;
					}
					}
				case 5: { // Инициализация
					Hash tmp;
					tmp.init(5);
					cout << tmp;
					system("pause");
					break;
					}
				case 6: { // Вывод
					cout << Sheet;
					system("pause");
					break;
				}
				}
			} while (variant !=0);
			variant = 9;
			system("cls");
			break;
			}
		case 2: {
			do {
				s_menu();
				variant = get_variant(5);
				switch (variant)
				{
				case 1: { // Обычный конструктор
					Hash temp;
					cout <<"Результат: \n" << temp << endl;
					system("pause");
					break;
					}
				case 2: { // С параметром
					Hash temp(5);
					cout << "Результат: \n"<< temp << endl;
					system("pause");
					break;
					}
				case 3: { // Копирующий
					Hash temp(Sheet);
					cout << "Начальный: \n"<< Sheet << endl;
					cout << "Скопированный: \n"<< temp << endl;
					system("pause");
					break;
					}

				}
				if (variant == 0) break;
			} while (variant !=0);
			variant = 9;
			break;
			system("cls");
			}
		}
	} while (variant !=0);
}

void Menu() {
	cout 
		<< "\n1: Функции\n"
		<< "2: Конструктор\n\n"
		<< "0: Выход\n"
		<< ">> ";
}
void f_menu() {
	cout
		<< "\n1: Добавление\n"
		<< "2: Поиск\n"
		<< "3: Удаление элемента\n"
		<< "4: Полное удаление\n"
		<< "5: Инициализация\n"
		<< "6: Вывод\n\n"
		<< "0: Выход\n"
		<< ">> ";
}
void s_menu() {
	cout
		<< "\n1: Обычный конструктор\n"
		<< "2: Конструктор с параметор\n"
		<< "3: Копирующий конструктор\n\n"
		<< "0: Выход\n"
		<< ">> ";
}

int get_variant(int count) { // защита от ненужных вариантов
	int variant;
	std::string s; // строка для считывания введённых данных
	getline(std::cin, s); // считываем строку

	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf_s(s.c_str(), "%d", &variant) != 1 || variant < -1 || variant > count) {
		std::cout << "Incorrect input. Try again: "; // выводим сообщение об ошибке
		getline(std::cin, s); // считываем строку повторно
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return variant;
}