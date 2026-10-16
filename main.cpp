#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Задание 1: Сумма натуральных чисел от 1 до n, которые делятся на 5 и не делятся на m (m < n)
void task1() {
    int n = 0, m = 0;

    cout << "\n--- Задание 1 ---\n";
    cout << "Введите натуральные числа n и m (m < n): ";
    cin >> n >> m;

    if (m >= n || n <= 0 || m <= 0) {
        cout << "Ошибка: должны выполняться условия n > 0, m > 0 и m < n.\n";
        return;
    }

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 5 == 0 && i % m != 0) {
            sum += i;
        }
    }

    cout << "Сумма чисел от 1 до " << n
         << ", кратных 5 и не кратных " << m << ": " << sum << "\n";
}

// Задание 2: Вычисление по формуле со скриншота 1
void task2() {
    double a = 0.0;
    cout << "\n--- Задание 2 ---\n";
    cout << "Введите вещественное значение a: ";
    cin >> a;

    double s = 0.0;

    if (a >= 0.0) {
        double prod = 1.0;
        for (int i = 2; i <= 8; i += 2) {
            prod *= (i * i);
        }
        s = prod - a;
    } else {
        double prod = 1.0;
        for (int i = 3; i <= 9; i += 3) {
            prod *= (i - 2.0);
        }
        s = prod;
    }

    cout << "Результат S = " << fixed << setprecision(6) << s << "\n";
}

// Задание 3: Ряд S(x) = 1 + 3x^2 + ... + ((2n+1)/n!)*x^(2n)
// и функция Y(x) = (1 + 2x^2) * e^(x^2) со скриншота 2
void task3() {
    cout << "\n--- Задание 3 ---\n";

    const double x_start = 0.0;
    const double x_end = 1.0;
    const double h = 0.2;
    const double eps = 1e-6;

    // Шапка таблицы (без рамок, 4 столбца: x, Y(x), S(x), N)
    cout << left
         << setw(10) << "x"
         << setw(16) << "Y(x)"
         << setw(16) << "S(x)"
         << setw(8)  << "N" << "\n";

    int steps = static_cast<int>(round((x_end - x_start) / h));

    for (int step = 0; step <= steps; ++step) {
        double x = x_start + step * h;

        // Точное значение функции: Y(x) = (1 + 2x^2) * e^(x^2)
        double y_val = (1.0 + 2.0 * x * x) * exp(x * x);

        // Нулевой член ряда (при n = 0): A_0 = 1
        double prev_term = 1.0;
        double sum = prev_term;
        int n = 0;

        // Если x == 0, то все последующие члены равны 0
        if (x > 0.0) {
            while (true) {
                n++;
                // Коэффициент перехода от A_{n-1} к A_n:
                // k = ((2n + 1) * x^2) / ((2n - 1) * n)
                double k = ((2.0 * n + 1.0) * x * x) / ((2.0 * n - 1.0) * n);
                double current_term = prev_term * k;

                if (fabs(current_term) < eps) {
                    break;
                }

                sum += current_term;
                prev_term = current_term; // Сохраняем текущий член как предыдущий
            }
        }

        cout << left << fixed
             << setw(10) << setprecision(2) << x
             << setw(16) << setprecision(6) << y_val
             << setw(16) << setprecision(6) << sum
             << setw(8)  << n << "\n";
    }
}

// Вспомогательная функция расчёта цепной дроби для заданного количества звеньев k
// y = 1 / (3 + 1 / (5 + 1 / (7 + ... + 1 / (2k + 1))))
double calcContinuedFraction(int k) {
    double res = 0.0;
    // Сворачиваем дробь снизу вверх: от i = k до i = 1
    for (int i = k; i >= 1; --i) {
        res = 1.0 / ((2.0 * i + 1.0) + res);
    }
    return res;
}

// Задание 4: Цепная дробь со скриншота 3
void task4() {
    cout << "\n--- Задание 4 ---\n";

    char repeat_n = 'y';
    while (repeat_n == 'y' || repeat_n == 'Y') {
        int n = 0;
        cout << "\nВведите натуральное число n: ";
        cin >> n;

        if (n <= 0) {
            cout << "Ошибка: число n должно быть натуральным (n > 0).\n";
        } else {
            // Вывод промежуточных значений при 3, 5 и 10 слагаемых (если n достаточно велико)
            if (n >= 3) {
                cout << "Промежуточное значение (3 слагаемых):  "
                     << fixed << setprecision(6) << calcContinuedFraction(3) << "\n";
            }
            if (n >= 5) {
                cout << "Промежуточное значение (5 слагаемых):  "
                     << fixed << setprecision(6) << calcContinuedFraction(5) << "\n";
            }
            if (n >= 10) {
                cout << "Промежуточное значение (10 слагаемых): "
                     << fixed << setprecision(6) << calcContinuedFraction(10) << "\n";
            }

            // Основной расчёт для введённого n
            double y = calcContinuedFraction(n);
            cout << "Итоговое значение y при n = " << setw(2) << n << ":        "
                 << fixed << setprecision(6) << y << "\n";
        }

        cout << "Вычислить для другого значения n? (y/n): ";
        cin >> repeat_n;
    }
}

int main() {
    char cont = 'y';

    while (cont == 'y' || cont == 'Y') {
        int choice = 0;
        cout << "\n========================================\n";
        cout << "Лабораторная работа №2 (Вариант 5)\n";
        cout << "Выберите номер задания (1, 2, 3 или 4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            default:
                cout << "Неверный номер задания! Введите число от 1 до 4.\n";
                break;
        }

        cout << "\nПродолжить работу с программой? (y/n): ";
        cin >> cont;
    }

    cout << "Работа программы завершена.\n";
    return 0;
}
