#pragma once
#include <string>

// Тип указателя на подынтегральную функцию
typedef double (*TPF)(double);

// Структура для хранения и печати результатов вычислений
struct resultToPrint {
    const char* name; // Наименование функции
    double i_toch;    // Точное (аналитическое) значение интеграла
    double i_sum;     // Вычисленное численно значение интеграла (IntSum)
    int n;            // Число разбиений N[i]
};

// Подынтегральные функции
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

// Аналитические формулы точных значений интеграла
double exact_f1(double a, double b);
double exact_f2(double a, double b);
double exact_f3(double a, double b);
double exact_f4(double a, double b);

// Функции численного интегрирования
double integrationByRectangle(TPF f, double a, double b, double eps, int& n);
double integrationByTrapezoidal(TPF f, double a, double b, double eps, int& n);

// Функция печати таблицы результатов (по Приложению 1 и 2)
void printTabl(resultToPrint* i_prn, int countRowOfTable);