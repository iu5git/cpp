#include "lab6.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

// Вывод русского текста в консоль через широкие символы Unicode (работает при любой кодировке файла)
void printRu(const wchar_t* text) {
    DWORD written;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), text, wcslen(text), &written, NULL);
}

int main() {
    // Устанавливаем кодовую страницу 866 для корректного отображения рамок таблицы (псевдографики)
    SetConsoleOutputCP(866);
    SetConsoleCP(866);

    double a, b;
    printRu(L"Введите границы интегрирования a и b через пробел (например, -1 3): ");
    if (!(std::cin >> a >> b)) {
        return 1;
    }
    std::cout << "\n";

    TPF funcs[4] = { f1, f2, f3, f4 };
    const char* funcNames[4] = { "y=x", "y=sin(22x)", "y=x^4", "y=arctg(x)" };

    double epsilons[5] = { 0.01, 0.001, 0.0001, 0.00001, 0.000001 };

    double exactValues[4] = {
        exact_f1(a, b),
        exact_f2(a, b),
        exact_f3(a, b),
        exact_f4(a, b)
    };

    resultToPrint tableData[4];

    // ================= 1. МЕТОД ПРЯМОУГОЛЬНИКОВ =================
    std::cout << std::string(78, '/') << "\n";
    printRu(L"Быстродействие алгоритма численного интегрирования в зависимости от функции\n");
    printRu(L"и требуемой точности (быстродействие характеризуется числом отрезков n[i])\n");
    printRu(L"Метод прямоугольников\n");
    std::cout << std::string(78, '/') << "\n";

    printRu(L"Область интегрирования функций:  ");
    std::cout << std::defaultfloat << a << "<= x <= " << b << "\n";

    for (int i = 0; i < 5; i++) {
        double eps = epsilons[i];
        printRu(L"        Точность вычислений = ");
        if (i == 0) {
            std::cout << std::defaultfloat << eps << "\n";
        }
        else {
            std::cout << std::fixed << std::setprecision(10) << eps << "\n";
        }

        for (int j = 0; j < 4; j++) {
            int n = 0;
            double calcVal = integrationByRectangle(funcs[j], a, b, eps, n);
            tableData[j] = { funcNames[j], exactValues[j], calcVal, n };
        }
        printTabl(tableData, 4);
    }

    std::cout << "\n";

    // ================= 2. МЕТОД ТРАПЕЦИЙ =================
    std::cout << std::string(78, '/') << "\n";
    printRu(L"Быстродействие алгоритма численного интегрирования в зависимости от функции\n");
    printRu(L"и требуемой точности (быстродействие характеризуется числом отрезков n[i])\n");
    printRu(L"Метод трапеций\n");
    std::cout << std::string(78, '/') << "\n";

    printRu(L"Область интегрирования функций:  ");
    std::cout << std::defaultfloat << a << "<= x <= " << b << "\n";

    for (int i = 0; i < 5; i++) {
        double eps = epsilons[i];
        printRu(L"        Точность вычислений = ");
        if (i == 0) {
            std::cout << std::defaultfloat << eps << "\n";
        }
        else {
            std::cout << std::fixed << std::setprecision(10) << eps << "\n";
        }

        for (int j = 0; j < 4; j++) {
            int n = 0;
            double calcVal = integrationByTrapezoidal(funcs[j], a, b, eps, n);
            tableData[j] = { funcNames[j], exactValues[j], calcVal, n };
        }
        printTabl(tableData, 4);
    }

    return 0;
}