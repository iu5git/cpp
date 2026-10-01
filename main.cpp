#include <iostream>
#include <windows.h>

namespace {
    const int MIN_HOUR = 0;
    const int MAX_HOUR = 23;
    const int MIN_MINUTE = 0;
    const int MAX_MINUTE = 59;

    const int MIDNIGHT_HOUR = 0;
    const int NOON_HOUR = 12;
    const int EXACT_MINUTE = 0;

    const int MORNING_START = 5;
    const int DAY_START = 12;
    const int EVENING_START = 18;

    const int TWELVE_HOURS = 12;

    const int MOD_TEN = 10;
    const int MOD_HUNDRED = 100;

    const int TEEN_MIN = 11;
    const int TEEN_MAX = 14;

    const int DIGIT_ONE = 1;
    const int DIGIT_TWO = 2;
    const int DIGIT_FOUR = 4;
}

bool isValidTime(int hours, int minutes) {
    return (hours >= MIN_HOUR && hours <= MAX_HOUR &&
            minutes >= MIN_MINUTE && minutes <= MAX_MINUTE);
}

void printHoursNoun(int hours) {
    int rem100 = hours % MOD_HUNDRED;
    int rem10 = hours % MOD_TEN;

    if (rem100 >= TEEN_MIN && rem100 <= TEEN_MAX) {
        std::cout << "часов";
    } else if (rem10 == DIGIT_ONE) {
        std::cout << "час";
    } else if (rem10 >= DIGIT_TWO && rem10 <= DIGIT_FOUR) {
        std::cout << "часа";
    } else {
        std::cout << "часов";
    }
}

void printMinutesNoun(int minutes) {
    int rem100 = minutes % MOD_HUNDRED;
    int rem10 = minutes % MOD_TEN;

    if (rem100 >= TEEN_MIN && rem100 <= TEEN_MAX) {
        std::cout << "минут";
    } else if (rem10 == DIGIT_ONE) {
        std::cout << "минута";
    } else if (rem10 >= DIGIT_TWO && rem10 <= DIGIT_FOUR) {
        std::cout << "минуты";
    } else {
        std::cout << "минут";
    }
}

void printTimeOfDay(int originalHour) {
    if (originalHour >= MORNING_START && originalHour < DAY_START) {
        std::cout << "утра";
    } else if (originalHour >= DAY_START && originalHour < EVENING_START) {
        std::cout << "дня";
    } else if (originalHour >= EVENING_START && originalHour <= MAX_HOUR) {
        std::cout << "вечера";
    } else {
        std::cout << "ночи";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int rawHours = 0;
    int rawMinutes = 0;

    if (!(std::cin >> rawHours >> rawMinutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 0;
    }

    if (!isValidTime(rawHours, rawMinutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 0;
    }

    if (rawHours == MIDNIGHT_HOUR && rawMinutes == EXACT_MINUTE) {
        std::cout << "полночь" << std::endl;
        return 0;
    }

    if (rawHours == NOON_HOUR && rawMinutes == EXACT_MINUTE) {
        std::cout << "полдень" << std::endl;
        return 0;
    }

    int displayHour = rawHours;
    if (rawHours > NOON_HOUR) {
        displayHour = rawHours - TWELVE_HOURS;
    } else if (rawHours == MIDNIGHT_HOUR) {
        displayHour = TWELVE_HOURS;
    }

    std::cout << displayHour << " ";
    printHoursNoun(displayHour);
    std::cout << " ";

    if (rawMinutes != EXACT_MINUTE) {
        std::cout << rawMinutes << " ";
        printMinutesNoun(rawMinutes);
        std::cout << " ";
    }

    printTimeOfDay(rawHours);

    if (rawMinutes == EXACT_MINUTE) {
        std::cout << " ровно";
    }

    std::cout << std::endl;
    return 0;
}