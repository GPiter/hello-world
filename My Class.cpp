#include <iostream>
using namespace std;

class Numbers {
	private:
	int numb_1;

	public:
	Numbers() : numb_1(0) {} // Конструктор 1, инициализация по умолчанию - применятеся для определения в main как Numbers numb1.
	Numbers(int n1) : numb_1(n1) {} // Конструктор 2, инициализация аргументов - применятеся для определения в main как Numbers numb1(5).

	void get_number() {
		cout << "Введите число: "; cin >> numb_1;
	}

	void show_result() {
		cout << "Результат: " << numb_1 << endl;
}

	void calculate(Numbers); // Прототип функции, возведение в квадрат
	Numbers operator+(Numbers) const; // Прототип функции, перегрузка операции +
	Numbers operator-(Numbers) const; // Прототип функции, перегрузка операции -
};

// Перегрузка операций + и -
Numbers Numbers::operator+(Numbers number) const {
	int num = numb_1 + number.numb_1;
	return Numbers(num);
}

Numbers Numbers::operator-(Numbers number) const {
	int num = numb_1 - number.numb_1;
	return Numbers(num);
}

// Функция возведения в квадрат
void Numbers::calculate(Numbers num1) {
	numb_1 = num1.numb_1 * num1.numb_1;
}

int main() {
	Numbers data1(5);
	Numbers data2, data3;
	data2.get_number();
	data3 = data1 + data2;
	data3.show_result();
	data3 = data1 - data2;
	data3.show_result();
	return 0;
}
