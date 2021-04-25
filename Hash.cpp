#include <iostream>
#include <iomanip>
#include <math.h>
#include "Hash.h"

using namespace std;

namespace sheet {
	Hash::Hash() : mas(nullptr), prob_mas(nullptr) {
	}
	Hash::~Hash() {
		del();
	}
	Hash::Hash(size_t size) {
		init(size);
	}
	Hash::Hash(const Hash& obj) {
		size = obj.size;
		mas = new double[size];
		prob_mas = new double[size];
		copy(obj.mas, obj.mas + (int)obj.size, mas);
		copy(obj.prob_mas, obj.prob_mas + (int)obj.size, prob_mas);
	}
	double Hash::mHash(double item) {
		return fmod(item, size);
	}
	double Hash::mHash(double item, size_t k) {
		return fmod((mHash(item) + k), size);
	}
	void Hash::init(size_t Size) {
		if (mas != nullptr) {
			
			delete[] mas, prob_mas;
			mas = new double[Size];
			prob_mas = new double[Size]();
			for (int i = 0; i < Size; i++)
				mas[i] = INFINITY;
			size = Size;
		}
		else {
			size = Size;
			if (prob_mas != nullptr)
				delete[] prob_mas;
			mas = new double[Size]();
			prob_mas = new double[Size]();
			for (int i = 0; i < size; i++)
				mas[i] = INFINITY;
			
		}
	}
	void Hash::del() {
		size = 0;
		delete[] mas;
		mas = nullptr;
	}
	void Hash::add(double item) {
		int point = mHash(item);
		if (mas[point] != INFINITY) {
			double Try = 1;
			// бесконечный цикл
			while (mas[point] != INFINITY) {
				point = mHash(item, Try);
				Try++;
				if (Try >= size) return;
			}
			all_try += Try;
			prob_mas[point] = Try;
			Try = 0;
			mas[point] = item;
		}
		else {
			prob_mas[point] = 1;
			mas[point] = item;
		}
	}
	void Hash::del_item(double item) {
		for (int i = 0; i < size; i++) {
			if (mas[i] == item) { 
				mas[i] = INFINITY;
				prob_mas[i] = INFINITY;
				break;
			}
		}
	}
	bool Hash::search(double item) { 
		if (mas != nullptr) {
			int point = mHash(item);
			double Try_search = 0;
			if (mas[point] != item) {
				// бесконечный цикл
				while (mas[point] != item) {
					Try_search++;
					point = mHash(item, Try_search);
					if (Try_search >= size) return false;
				}
				cout << "Количество проб происка: " << Try_search << endl;
				cout << "Индекс элемента: << " << prob_mas[point] << endl;
				return true;
			}
			else { 
				cout << "Количество проб происка: " << Try_search << endl;
				return true;
			};
		}
		else return false;
	}
	bool Hash::search() {
		cout << "\nВведите искомое число: ";
		double tmp;
		cin >> tmp;
		return search(tmp);
	}

	double Hash::Get_AllTry() {
		return all_try;
	}
	ostream& operator<<(ostream& out, const Hash& obj) {
		if (obj.mas != nullptr) {
			double Width = out.width() == 0 ? 5 : out.width();
			static int wide = 0;
			for (int i = 0; i < obj.size; i++)
				out << setw(1) << "|" << setw(2) << i << setw(2) << "|" << setw(Width) << obj.mas[i] << "|" << setw(3) << obj.prob_mas[i] << endl;
			if (!wide) {
				out << "\nОбщее количество проб: " << obj.all_try << endl;
				wide = 1;
			}
		}
		else {
			out << "\nТаблицы не существует!\n";
		}
		return out;
	}
}