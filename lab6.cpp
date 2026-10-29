#include "lab6.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>

// 1. Подынтегральные функции
double f1(double x) { return x; }
double f2(double x) { return std::sin(22.0 * x); }
double f3(double x) { return x * x * x * x; }
double f4(double x) { return std::atan(x); }

// 2. Точные значения интегралов на интервале [a, b]
double exact_f1(double a, double b) {
    return (b * b - a * a) / 2.0;
}

double exact_f2(double a, double b) {
    return (std::cos(a * 22.0) - std::cos(b * 22.0)) / 22.0;
}

double exact_f3(double a, double b) {
    return (std::pow(b, 5) - std::pow(a, 5)) / 5.0;
}

double exact_f4(double a, double b) {
    return b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1.0) - std::log(a * a + 1.0)) / 2.0;
}

// 3. Метод средних прямоугольников (по правилу Рунге)
double integrationByRectangle(TPF f, double a, double b, double eps, int& n) {
    n = 1;
    double dx = b - a;
    double I_prev = 0.0;
    double I_curr = f(a + dx / 2.0) * dx;

    do {
        I_prev = I_curr;
        n *= 2;
        dx = (b - a) / n;

        double sum = 0.0;
        for (int i = 1; i <= n; i++) {
            double x_i = a + dx / 2.0 + (i - 1) * dx;
            sum += f(x_i);
        }
        I_curr = sum * dx;

    } while (std::abs(I_curr - I_prev) / 3.0 >= eps);

    return I_curr;
}

// 4. Метод трапеций (по правилу Рунге)
double integrationByTrapezoidal(TPF f, double a, double b, double eps, int& n) {
    n = 1;
    double dx = b - a;
    double I_prev = 0.0;
    double I_curr = dx * (f(a) + f(b)) / 2.0;

    do {
        I_prev = I_curr;
        n *= 2;
        dx = (b - a) / n;

        double sum = (f(a) + f(b)) / 2.0;
        for (int i = 1; i < n; i++) {
            sum += f(a + i * dx);
        }
        I_curr = sum * dx;

    } while (std::abs(I_curr - I_prev) / 3.0 >= eps);

    return I_curr;
}

// Вспомогательная функция для рисования горизонтальных линий таблицы в CP866
static void drawLine(char left, char mid, char right, int w1, int w2, int w3, int w4) {
    const char H = '\xC4'; // горизонтальная линия '─'
    std::cout << left << std::string(w1, H)
        << mid << std::string(w2, H)
        << mid << std::string(w3, H)
        << mid << std::string(w4, H) << right << "\n";
}

// 5. Печать таблицы точно как в Приложении 1 и 2 методички
void printTabl(resultToPrint* i_prn, int countRowOfTable) {
    const int w1 = 12;
    const int w2 = 18;
    const int w3 = 18;
    const int w4 = 10;
    const char V = '\xB3'; // вертикальная линия '│'

    // Верхняя рамка: ┌────────────┬──────────────────┬──────────────────┬──────────┐
    drawLine('\xDA', '\xC2', '\xBF', w1, w2, w3, w4);

    // Заголовок таблицы: │  Функция   │     Интеграл     │      IntSum      │   N[i]   │
    // Слово "Функция" и "Интеграл" записаны в кодах CP866, чтобы не зависеть от кодировки файла
    std::cout << V << "  \x94\xE3\xAD\xAA\xE6\xA8\xEF   "
        << V << "     \x88\xAD\xE2\xA5\xA3\xE0\xA0\xAB     "
        << V << "      IntSum      "
        << V << "   N[i]   " << V << "\n";

    // Разделитель шапки: ├────────────┼──────────────────┼──────────────────┼──────────┤
    drawLine('\xC3', '\xC5', '\xB4', w1, w2, w3, w4);

    // Строки со значениями
    for (int i = 0; i < countRowOfTable; i++) {
        // Центрируем название функции в первом столбце шириной 12
        int len = static_cast<int>(std::strlen(i_prn[i].name));
        int padLeft = (w1 - len) / 2;
        int padRight = w1 - len - padLeft;

        std::cout << V << std::string(padLeft, ' ') << i_prn[i].name << std::string(padRight, ' ')
            << V << std::right << std::fixed << std::setprecision(10) << std::setw(w2 - 1) << i_prn[i].i_toch << " "
            << V << std::right << std::fixed << std::setprecision(10) << std::setw(w3 - 1) << i_prn[i].i_sum << " "
            << V << std::right << std::setw(w4 - 1) << i_prn[i].n << " " << V << "\n";

        if (i < countRowOfTable - 1) {
            // Межстрочный разделитель: ├────────────┼──────────────────┼──────────────────┼──────────┤
            drawLine('\xC3', '\xC5', '\xB4', w1, w2, w3, w4);
        }
    }

    // Нижняя рамка: └────────────┴──────────────────┴──────────────────┴──────────┘
    drawLine('\xC0', '\xC1', '\xD9', w1, w2, w3, w4);
}