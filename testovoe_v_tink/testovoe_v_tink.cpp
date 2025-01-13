#include <iostream>

int main() {
    int birth_day, birth_month, current_day, current_month, current_year;
    std::cin >> birth_day >> birth_month >> current_day >> current_month >> current_year;

    // Проверка корректности входных данных
    if (birth_day < 1 || birth_day > 31 || birth_month < 1 || birth_month > 12 ||
        current_day < 1 || current_day > 31 || current_month < 1 || current_month > 12 ||
        current_year < 1920 || current_year > 3000) {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    int days_in_birth_month = 31;
    if (birth_month == 2) {
        days_in_birth_month = (current_year % 400 == 0 || (current_year % 4 == 0 && current_year % 100 != 0)) ? 29 : 28;
    }
    else if (birth_month == 4 || birth_month == 6 || birth_month == 9 || birth_month == 11) {
        days_in_birth_month = 30;
    }

    if (birth_day > days_in_birth_month) {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    int days_in_current_month = 31;
    if (current_month == 2) {
        days_in_current_month = (current_year % 400 == 0 || (current_year % 4 == 0 && current_year % 100 != 0)) ? 29 : 28;
    }
    else if (current_month == 4 || current_month == 6 || current_month == 9 || current_month == 11) {
        days_in_current_month = 30;
    }

    if (current_day > days_in_current_month) {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    int days_to_birthday = 0;
    if (current_month < birth_month) {
        days_to_birthday = birth_day - current_day + (birth_month - current_month - 1) * days_in_current_month;
    }
    else if (current_month > birth_month) {
        days_to_birthday = birth_day - current_day + (12 - current_month + birth_month) * days_in_current_month;
    }
    else {
        if (birth_day >= current_day) {
            days_to_birthday = birth_day - current_day;
        }
        else {
            days_to_birthday = birth_day - current_day + 365;
            if ((current_year % 400 == 0) || (current_year % 4 == 0 && current_year % 100 != 0)) {
                days_to_birthday += 1;
            }
        }
    }

    std::cout << days_to_birthday << std::endl;
    return 0;
}
