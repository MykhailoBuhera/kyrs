#include "CarManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

//конструктор за замовчуванням
CarManager::CarManager() {}
CarManager::CarManager(const CarManager& other) : cars(other.cars) {}
CarManager::CarManager(CarManager&& other) noexcept : cars(move(other.cars)) {}
CarManager::~CarManager() {
    cout << "[CarManager] Деструктор\n";
}

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return tolower(c); });
    return result;
}

void CarManager::printCarIndexList() const {
    cout << "\nІндекс\tМарка\n";
    for (size_t i = 0; i < cars.size(); ++i) {
        cout << i << "\t";
        cars[i]->print();
    }
}

void CarManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            cars.push_back(make_shared<Car>(Car::fromCSV(line)));
        }
    }
}

void CarManager::saveToFile(const string& filename) {
    ofstream file(filename);
    for (const auto& car : cars) {
        file << car->toCSV() << '\n';
    }
}

void CarManager::addCar() {
    string brand, color, model;   
    double fuel, price;
    int doors, year;

    cout << "\n--- Додавання нового авто ---\n";
    cout << "Марка: "; cin >> brand;
    cout << "Модель: "; cin >> model;             
    cout << "Колір: "; cin >> color;
    cout << "Витрати бензину (л/100км): "; cin >> fuel;

    cout << "Кількість дверей: ";
    while (!(cin >> doors)) {
        cout << "Помилка! Введіть ціле число (напр. 4): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Рік випуску: ";
    while (!(cin >> year)) {
        cout << "Помилка! Введіть ціле число (напр. 2023): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Ціна: ";
    while (!(cin >> price)) {
        cout << "Помилка! Введіть числове значення (напр. 550000): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string packageName;
    bool hasAC, hasMultimedia, hasSafety;
    double configPrice;
    cin.ignore(); // Очищаємо буфер після попереднього cin
    cout << "Назва комплектації: "; getline(cin, packageName);
    cout << "Чи є кондиціонер (1 - так/0 - ні): "; cin >> hasAC;
    cout << "Чи є мультимедія (1 - так/0 - ні): "; cin >> hasMultimedia;
    cout << "Чи є система безпеки (1 - так/0 - ні): "; cin >> hasSafety;
    cout << "Нова ціна конфігурації: ";
    while (!(cin >> configPrice)) {
        cout << "Помилка! Введіть числове значення (напр. 550000): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Configuration config(brand, model, packageName, hasAC, hasMultimedia, hasSafety, configPrice);

    cars.push_back(make_shared<Car>(brand, color, model, fuel, doors, year, price, config));
    cout << "? Авто додано!\n";
	saveToFile("cars.csv");
}

void CarManager::showAllCars() const {
    if (cars.empty()) {
        cout << "База порожня.\n";
        return;
    }
    cout << "\n--- Всі автомобілі ---\n";
    for (const auto& car : cars) car->print();
}

void CarManager::editCar() {
    int index;
    showAllCars();
    cout << "\nВведіть індекс авто для редагування: ";
    cin >> index;

    if (index >= 0 && index < cars.size()) {
        string brand, color, model;
        double fuel, price;
        int doors, year;

        cout << "--- Редагування авто ---\n";
        cout << "Нова марка: "; cin >> brand;
        cout << "Нова модель: "; cin >> model; 
        cout << "Новий колір: "; cin >> color;
        cout << "Нові витрати бензину: "; cin >> fuel;
        cout << "Нова кількість дверей: ";
        while (!(cin >> doors)) {
            cout << "Помилка! Введіть ціле число (напр. 4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Новий рік випуску: ";
        while (!(cin >> year)) {
            cout << "Помилка! Введіть ціле число (напр. 2023): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Нова ціна: ";
        while (!(cin >> price)) {
            cout << "Помилка! Введіть числове значення (напр. 550000): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
		double configPrice;
        string packageName;
        bool hasAC, hasMultimedia, hasSafety;
        cin.ignore();
        cout << "Назва комплектації: "; getline(cin, packageName);
        cout << "Чи є кондиціонер (1 - так/0 - ні): "; cin >> hasAC;
        cout << "Чи є мультимедія (1 - так/0 - ні): "; cin >> hasMultimedia;
        cout << "Чи є система безпеки (1 - так/0 - ні): "; cin >> hasSafety;
        cout << "Нова ціна: ";
        while (!(cin >> configPrice)) {
            cout << "Помилка! Введіть числове значення (напр. 550000): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        Configuration config(brand, model, packageName, hasAC, hasMultimedia, hasSafety, configPrice);
        Car car(brand, color, model, fuel, doors, year, price, config);


        cars[index] = make_shared<Car>(brand, color, model, fuel, doors, year, price, config);
        cout << "? Авто оновлено!\n";
        saveToFile("cars.csv");
    }
    else {
        cout << "? Невірний індекс!\n";
    }
}

void CarManager::removeCar() {
    int index;
    showAllCars();
    cout << "\nВведіть індекс авто для видалення: ";
    cin >> index;
    if (index >= 0 && index < cars.size()) {
        cars.erase(cars.begin() + index);
        cout << "? Авто видалено!\n";
    }

    else {
        cout << "? Невірний індекс!\n";
    }
}

// ---------------- Аналітика ----------------
void CarManager::findMostEconomicalCar() const {
    if (cars.empty()) {
        cout << "База порожня.\n"; return;
    }
    auto best = min_element(cars.begin(), cars.end(),
        [](auto& a, auto& b) { return a->getFuelConsumption() < b->getFuelConsumption(); });
    cout << "\nНайекономічніший автомобіль:\n";
    (*best)->print();
}

void CarManager::averagePriceInPeriod() const {
    int start, end;
	cout << "\nВведіть початковий рік: ";
    while (!(cin >> start)) {
        cout << "Помилка! Введіть ціле число ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введіть кінцевий рік : ";
    while (!(cin >> end)) {
        cout << "Помилка! Введіть ціле число (напр. 2023): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double sum = 0; int count = 0;
    for (const auto& car : cars) {
        if (car->getYear() >= start && car->getYear() <= end) {
            sum += car->getPrice();
            count++;
        }
    }
    if (count == 0) cout << "? Немає авто у цьому періоді.\n";
    else cout << "Середня ціна: " << sum / count << " грн\n";
}

// ---------------- Сортування ----------------
void CarManager::sortByPrice(bool ascending) {
    sort(cars.begin(), cars.end(), [ascending](auto& a, auto& b) {
        return ascending ? a->getPrice() < b->getPrice() : a->getPrice() > b->getPrice();
        });
    cout << "? Відсортовано за ціною.\n";
}

void CarManager::sortByYear(bool ascending) {
    sort(cars.begin(), cars.end(), [ascending](auto& a, auto& b) {
        return ascending ? a->getYear() < b->getYear() : a->getYear() > b->getYear();
        });
    cout << "? Відсортовано за роком.\n";
}

void CarManager::sortByFuelConsumption(bool ascending) {
    sort(cars.begin(), cars.end(), [ascending](auto& a, auto& b) {
        return ascending ? a->getFuelConsumption() < b->getFuelConsumption()
            : a->getFuelConsumption() > b->getFuelConsumption();
        });
    cout << "? Відсортовано за витратами пального.\n";
}

// ---------------- Фільтрація ----------------
void CarManager::filterByBrand(const string& b) const {
    cout << "\nФільтр за маркою: " << b << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->isBrand(b)) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? Немає авто з такою маркою.\n";
}

void CarManager::filterByColor(const string& color) const {
    cout << "\nФільтр за кольором: " << color << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->getColor() == color) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? Немає авто з таким кольором.\n";
}

void CarManager::filterByYear(int year) const {
    cout << "\nФільтр за роком: " << year << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->getYear() == year) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? Немає авто цього року.\n";
}

void CarManager::showCarAge() const {
    int index;
    showAllCars();
    cout << "\nВведіть індекс авто для перевірки віку: "; cin >> index;

    if (index >= 0 && index < cars.size()) {
        cout << "Вік авто: " << cars[index]->getAge() << " років\n";
    }
    else {
        cout << "? Невірний індекс.\n";
    }
}

void CarManager::findByBrand() const {
    string b;
    cout << "\nВведіть марку для пошуку: "; cin >> b;
    filterByBrand(b);
}

void CarManager::searchCars() const {
    if (cars.empty()) {
        cout << "База порожня.\n";
        return;
    }

    string brandFilter, colorFilter;
    int yearFilter = 0;

    cout << "\n--- Пошук авто ---\n";
    cout << "Введіть марку (або залиште порожнім): ";
    cin.ignore();
    getline(cin, brandFilter);

    cout << "Введіть колір (або залиште порожнім): ";
    getline(cin, colorFilter);

    cout << "Введіть рік (або 0 для пропуску): ";
    cin >> yearFilter;

    // Приводимо фільтри до нижнього регістру
    brandFilter = toLower(brandFilter);
    colorFilter = toLower(colorFilter);

    bool found = false;
    for (const auto& car : cars) {
        string carStr = toLower(car->toCSV());
        bool matches = true;

        if (!brandFilter.empty() && carStr.find(brandFilter) == string::npos)
            matches = false;
        if (!colorFilter.empty() && carStr.find(colorFilter) == string::npos)
            matches = false;
        if (yearFilter != 0 && car->getYear() != yearFilter)
            matches = false;

        if (matches) {
            car->print();
            found = true;
        }
    }

    if (!found)
        cout << "Нічого не знайдено за заданими критеріями.\n";
}


void CarManager::findEconomicalCars() const {
    double limit;
    cout << "Введіть ліміт витрат пального (літр/100км): "; cin >> limit;
    bool found = false;
    for (const auto& car : cars) {
        if (car->isEconomical(limit)) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? Немає авто економніших за " << limit << " л/100км.\n";
}

void CarManager::findFamilyCars() const {
    cout << "\nСімейні авто (>=4 дверей):\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->isFamilyCar()) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? Сімейних авто немає.\n";
}

void CarManager::filterByModel(const string& m) const {
    cout << "\nФільтр за моделлю: " << m << "\n";
    bool found = false;
    for (const auto& car : cars) {
        if (car->getModel() == m) {
            car->print();
            found = true;
        }
    }
    if (!found) cout << "? Немає авто з такою моделлю.\n";
}

void CarManager::applyDiscountToCar() {
    int index;
    double percent;
    showAllCars();
    cout << "\nВведіть індекс авто для знижки: "; cin >> index;
    cout << "Введіть відсоток знижки: "; cin >> percent;

    if (index >= 0 && index < cars.size()) {
        cars[index]->applyDiscount(percent);
        cout << "? Знижку застосовано!\n";
        cars[index]->print();
    }
    else {
        cout << "? Невірний індекс.\n";
    }
}

void CarManager::calcTripCost() const {
    int index;
    double distance, fuelPrice;
    showAllCars();
    cout << "\nВведіть індекс авто: "; cin >> index;
    cout << "Введіть відстань поїздки (км): "; cin >> distance;
    cout << "Введіть ціну за літр пального (грн): "; cin >> fuelPrice;

    if (index >= 0 && index < cars.size()) {
        double cost = cars[index]->costPer100km(fuelPrice) * (distance / 100.0);
        cout << "Вартість поїздки: " << cost << " грн\n";
    }
    else {
        cout << "? Невірний індекс.\n";
    }
}

void CarManager::showHelp() const {
    cout << "\n================ Довідка для адміністратора ================\n";

    cout << "\n--> Пояснення роботи програми <--\n";
    cout << "Ця програма є системою управління автосалоном. Вона дозволяє\n";
    cout << "адміністраторам та користувачам працювати зі спільною базою даних автомобілів,\n";
    cout << "що зберігається у файлі 'cars.csv'.\n";
    cout << "Адміністратор має повний доступ до всіх функцій, включаючи керування\n";
    cout << "користувачами та редагування каталогу авто.\n";

    cout << "\n--> Правила вводу даних <--\n";
    cout << "1. При введенні числових даних (ціна, рік, кількість дверей) використовуйте\n";
    cout << "   лише цифри. Введення тексту призведе до помилки.\n";
    cout << "2. При введенні тексту (марка, модель, колір) уникайте пробілів.\n";
    cout << "   Наприклад, вводьте 'Volkswagen', а не 'Volks wagen'.\n";
    cout << "3. Для позначення 'так' або 'ні' (наприклад, наявність кондиціонера)\n";
    cout << "   використовуйте 1 для 'так' і 0 для 'ні'.\n";

    cout << "\n--> Короткий опис команд <--\n\n";
    cout << "--- Керування каталогом ---\n";
    cout << "1.  Переглянути всі авто  - Виводить повний список автомобілів у базі.\n";
    cout << "2.  Додати нове авто       - Запускає процес додавання нового авто в каталог.\n";
    cout << "5.  Редагувати авто        - Дозволяє змінити дані існуючого автомобіля за його індексом.\n";
    cout << "6.  Видалити авто          - Видаляє автомобіль з бази за його індексом.\n";
    cout << "12. Застосувати знижку     - Застосовує відсоткову знижку до ціни обраного авто.\n\n";

    cout << "--- Аналітика та пошук ---\n";
    cout << "3.  Найекономічніше авто   - Знаходить авто з найменшими витратами пального.\n";
    cout << "4.  Середня ціна у періоді - Розраховує середню ціну авто за вказаний період років.\n";
    cout << "8.  Пошук за критеріями    - Розширений пошук за маркою, кольором та роком.\n";
    cout << "9.  Пошук за маркою        - Швидкий пошук та фільтрація всіх авто конкретної марки.\n";
    cout << "13. Показати вік авто      - Визначає вік обраного автомобіля.\n";
    cout << "14. Розрахувати вартість   - Розраховує вартість поїздки на задану відстань.\n\n";

    cout << "--- Сортування та фільтрація ---\n";
    cout << "15-18. Сортувати           - Сортує список авто за ціною або роком (за зростанням/спаданням).\n";
    cout << "19-21. Фільтрувати         - Показує авто, що відповідають заданому кольору або року.\n\n";

    cout << "--- Керування акаунтом ---\n";
    cout << "7.  Меню адміністратора    - Повернення до головного меню адміністратора (керування користувачами).\n";
    cout << "23. Вийти з програми       - Зберігає всі зміни та завершує роботу програми.\n";
    cout << "===========================================================\n";
}
void CarManager::showHelpnotadm() const {
    cout << "\n================== Довідка для користувача ==================\n";

    cout << "\n--> Пояснення роботи програми <--\n";
    cout << "Ця програма є каталогом автомобілів автосалону. Ви можете\n";
    cout << "переглядати, шукати, сортувати та аналізувати доступні автомобілі.\n";
    cout << "Усі дані завантажуються зі спільної бази даних.\n";

    cout << "\n--> Правила вводу даних <--\n";
    cout << "1. При введенні числових даних (наприклад, рік) використовуйте лише цифри.\n";
    cout << "2. При введенні тексту (марка, колір) пишіть одне слово без пробілів.\n";

    cout << "\n--> Короткий опис команд <--\n\n";
    cout << "--- Перегляд та аналітика ---\n";
    cout << "1.  Переглянути всі авто  - Виводить повний список автомобілів у базі.\n";
    cout << "2.  Найекономічніше авто   - Знаходить авто з найменшими витратами пального.\n";
    cout << "3.  Середня ціна у періоді - Розраховує середню ціну авто за вказаний період років.\n";
    cout << "4.  Пошук за критеріями    - Дозволяє знайти авто за маркою, кольором або роком.\n\n";

    cout << "--- Сортування та фільтрація ---\n";
    cout << "5-8.  Сортувати            - Сортує список авто за ціною або роком.\n";
    cout << "9-10. Фільтрувати          - Показує авто, що відповідають заданому кольору або року.\n\n";

    cout << "--- Загальні команди ---\n";
    cout << "11. Допомога (цей список)  - Виводить цю довідку.\n";
    cout << "12. Вийти з програми       - Завершує роботу програми.\n";
    cout << "===========================================================\n";
}