#include "CarManager.h"
#include "AuthManager.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <limits> 
using namespace std;

int safeInput() {
    int value;
    while (true) {
        cin >> value;

        if (cin.fail()) {  // Якщо введено не число
            cin.clear(); // Скидаємо стан помилки
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаємо буфер вводу
            cout << "Помилка: введіть число! Спробуйте ще раз: ";
        }
        else {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очистка "хвоста" рядка
            return value; // Коректне число
        }
    }
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    AuthManager auth;
    CarManager manager;
    manager.loadFromFile("cars.csv");

    while (true) {
        if (!auth.login()) {
            cout << "Спроба входу неуспішна. Повторити? (1 - так, ,будь яка  інша - вихід): ";
            int retry; cin >> retry;
            if (retry != 1) break;
            continue;
        }
        bool activeSession = true;

        while (activeSession) {

            if (auth.isAdmin()) {
                cout << "\nВітаємо вас, адміністраторе\n";
                cout << "\n--- Меню адміністратора ---\n";
                cout << "1. Додати користувача\n";
                cout << "2. Видалити користувача\n";
                cout << "3. Переглянути всіх користувачів\n";
                cout << "4. Перейти до меню авто\n";
                cout << "5. Змінити користувача\n";
                cout << "6. Вийти з програми\n";
                cout << "Ваш вибір: ";
                int choice;
                choice = safeInput();

                switch (choice) {
                case 1: auth.addUser(); break;
                case 2: auth.deleteUser(); break;
                case 3: auth.listUsers(); break;
                case 4: {
                    bool carMenuActive = true;
                    while (carMenuActive) {
                        cout << "\n--- Меню авто ---\n";
                        cout << "1. Переглянути всі авто\n";
                        cout << "2. Додати нове авто\n";
                        cout << "3. Найекономічніше авто\n";
                        cout << "4. Середня ціна у періоді\n";
                        cout << "5. Редагувати авто\n";
                        cout << "6. Видалити авто\n";
                        cout << "7. Повернутися до меню адміністратора\n";
                        cout << "8. Пошук авто за критеріями (searchCars)\n";
                        cout << "9. Пошук за маркою (findByBrand)\n";
                        cout << "10. Знайти всі економічні авто\n";
                        cout << "11. Знайти сімейні авто\n";
                        cout << "12. Застосувати знижку до авто\n";
                        cout << "13. Показати вік авто\n";
                        cout << "14. Розрахувати вартість поїздки\n";
                        cout << "15. Сортувати за ціною (зростання)\n";
                        cout << "16. Сортувати за ціною (спадання)\n";
                        cout << "17. Сортувати за роком (зростання)\n";
                        cout << "18. Сортувати за роком (спадання)\n";
                        cout << "19. Сортувати за витратами пального\n";
                        cout << "20. Фільтр за кольором\n";
                        cout << "21. Фільтр за роком\n";
                        cout << "22. Допомога\n";
                        cout << "23. Вийти з програми\n";
                        cout << "Ваш вибір: ";
                        int carChoice;
                        carChoice = safeInput();

                        switch (carChoice) {
                        case 1: manager.showAllCars(); break;
                        case 2: manager.addCar(); break;
                        case 3: manager.findMostEconomicalCar(); break;
                        case 4: manager.averagePriceInPeriod(); break;
                        case 5: manager.editCar(); break;
                        case 6: manager.removeCar(); break;
                        case 7: carMenuActive = false; break;
                        case 8: manager.searchCars(); break;
                        case 9: manager.findByBrand(); break;
                        case 10: manager.findEconomicalCars(); break;
                        case 11: manager.findFamilyCars(); break;
                        case 12: manager.applyDiscountToCar(); break;
                        case 13: manager.showCarAge(); break;
                        case 14: manager.calcTripCost(); break;
                        case 15: manager.sortByPrice(true); break;
                        case 16: manager.sortByPrice(false); break;
                        case 17: manager.sortByYear(true); break;
                        case 18: manager.sortByYear(false); break;
                        case 19: manager.sortByFuelConsumption(true); break;
                        case 20: {
                            string color;
                            cout << "Введіть колір: "; cin >> color;
                            manager.filterByColor(color);
                            break;
                        }
                        case 21: {
                            int year;
                            cout << "Введіть рік: "; cin >> year;
                            manager.filterByYear(year);
                            break;
                        }
                        case 22: manager.showHelp(); break;
                        case 23: manager.saveToFile("cars.csv"); return 0;
                        default: cout << "Невірний вибір.\n"; break;
                        }
                    }
                    break;
                }
                case 5: activeSession = false; break;
                case 6: manager.saveToFile("cars.csv"); return 0;
                default: cout << "Невірний вибір.\n"; break;
                }
            }
            else {
                cout << "Вітаємо, " << auth.getCurrentUser() << "!\n";
                cout << "--- Меню користувача ---\n";
                cout << "1. Переглянути всі авто\n";
                cout << "2. Найекономічніше авто\n";
                cout << "3. Середня ціна у періоді\n";
                cout << "4. Пошук авто за критеріями (searchCars)\n";
                cout << "5. Сортувати за ціною (зростання)\n";
                cout << "6. Сортувати за ціною (спадання)\n";
                cout << "7. Сортувати за роком (зростання)\n";
                cout << "8. Сортувати за роком (спадання)\n";
                cout << "9. Фільтр за кольором\n";
                cout << "10. Фільтр за роком\n";
                cout << "11. Допомога\n";
                cout << "12. Вийти з програми\n";
                cout << "13. Змінити користувача\n";
                cout << "Ваш вибір: ";

                int choice;
                choice = safeInput();

                switch (choice) {
                case 1: manager.showAllCars(); break;
                case 2: manager.findMostEconomicalCar(); break;
                case 3: manager.averagePriceInPeriod(); break;
                case 4: manager.searchCars(); break;
                case 5: manager.sortByPrice(true); break;
                case 6: manager.sortByPrice(false); break;
                case 7: manager.sortByYear(true); break;
                case 8: manager.sortByYear(false); break;
                case 9: {
                    string color;
                    cout << "Введіть колір: "; cin >> color;
                    manager.filterByColor(color);
                    break;
                }
                case 10: {
                    int year;
                    cout << "Введіть рік: "; cin >> year;
                    manager.filterByYear(year);
                    break;
                }
                case 11: manager.showHelpnotadm(); break;
                case 12: manager.saveToFile("cars.csv"); return 0;
                case 13: activeSession = false; break;
                default: cout << "Невірний вибір.\n"; break;
                }
            }
        }

    }

    return 0;
}
