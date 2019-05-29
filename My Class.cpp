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
		cout << "Число в квадрате: " << numb_1 << endl;
}

	void calculate(Numbers); // Прототип функции
};


void Numbers::calculate(Numbers num1) {

	numb_1 = num1.numb_1 * num1.numb_1;

}

int main() {
	Numbers data1;
	data1.get_number();
	data1.calculate(data1);
	data1.show_result();
	return 0;
}
