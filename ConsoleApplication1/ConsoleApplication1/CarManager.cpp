#include "CarManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

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
    cout << "Кількість дверей: "; cin >> doors;
    cout << "Рік випуску: "; cin >> year;
    cout << "Ціна: "; cin >> price;

    string packageName;
    bool hasAC, hasMultimedia, hasSafety;
    double configPrice;
    cin.ignore(); // Очищаємо буфер після попереднього cin
    cout << "Package name: "; getline(cin, packageName);
    cout << "Has air conditioner (1/0): "; cin >> hasAC;
    cout << "Has multimedia (1/0): "; cin >> hasMultimedia;
    cout << "Has safety system (1/0): "; cin >> hasSafety;
    cout << "Configuration price: "; cin >> configPrice;

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
        cout << "Нова модель: "; cin >> model;      // <-- нове
        cout << "Новий колір: "; cin >> color;
        cout << "Нові витрати бензину: "; cin >> fuel;
        cout << "Нова кількість дверей: "; cin >> doors;
        cout << "Новий рік: "; cin >> year;
        cout << "Нова ціна: "; cin >> price;

		double configPrice;
        string packageName;
        bool hasAC, hasMultimedia, hasSafety;
        cin.ignore();
        cout << "Package name: "; getline(cin, packageName);
        cout << "Has air conditioner (1/0): "; cin >> hasAC;
        cout << "Has multimedia (1/0): "; cin >> hasMultimedia;
        cout << "Has safety system (1/0): "; cin >> hasSafety;
        cout << "Configuration price: "; cin >> configPrice;


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
    cout << "\nВведіть початковий рік: "; cin >> start;
    cout << "Введіть кінцевий рік: "; cin >> end;

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

/**
* @brief Розраховує вартість поїздки на обраному авто.
*/
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
    cout << "\n--- Довідка (для адміністратора) ---\n";
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
    cout << "22. Допомога (цей список)\n";
    cout << "23. Вийти з програми\n";

}
void CarManager::showHelpnotadm() const {
    cout << "\n--- Довідка (для користувача) ---\n";
    cout << "1. Переглянути всі авто\n";
    cout << "2. Найекономічніше авто\n";
    cout << "3. Середня ціна у періоді\n";
    cout << "4. Пошук авто за критеріями\n";
    cout << "5. Сортувати за ціною (зростання)\n";
    cout << "6. Сортувати за ціною (спадання)\n";
    cout << "7. Сортувати за роком (зростання)\n";
    cout << "8. Сортувати за роком (спадання)\n";
    cout << "9. Фільтр за кольором\n";
    cout << "10. Фільтр за роком\n";
    cout << "11. Допомога (цей список)\n";
    cout << "12. Вийти з програми\n";
}
