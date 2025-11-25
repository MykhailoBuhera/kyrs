#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Car.h"

/**
 * @class CarManager
 * @brief Менеджер-клас для керування колекцією автомобілів.
 * @details Реалізує всю бізнес-логіку програми: CRUD-операції,
 * завантаження/збереження, пошук, сортування, фільтрацію та аналітику.
 * Є центральним компонентом, що взаємодіє з користувачем.
 */
class CarManager {
public:
    CarManager();
    CarManager(const CarManager& other);
    CarManager(CarManager&& other) noexcept;
    ~CarManager();

    /**
     * @brief Завантажує дані про автомобілі з файлу.
     * @param filename Ім'я файлу для завантаження (напр., "cars.csv").
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Зберігає поточну колекцію автомобілів у файл.
     * @param filename Ім'я файлу для збереження.
     */
    void saveToFile(const std::string& filename);

    /**
     * @brief Ініціює процес додавання нового автомобіля через діалог з користувачем.
     */
    void addCar();

    /**
     * @brief Виводить повний список автомобілів з їх характеристиками в консоль.
     */
    void showAllCars() const;

    /**
     * @brief Дозволяє користувачеві редагувати дані існуючого автомобіля за індексом.
     */
    void editCar();

    /**
     * @brief Видаляє автомобіль з колекції за вказаним індексом.
     */
    void removeCar();

    // --- Аналітика та розрахунки ---
    void findMostEconomicalCar() const;
    void averagePriceInPeriod() const;
	// --- Методи для додаткової інформації по окремих авто ---
    void calcTripCost() const;
    void showCarAge() const;
    void applyDiscountToCar();

    // --- Сортування ---

    /**
     * @brief Сортує список автомобілів за ціною.
     * @param ascending true для сортування за зростанням, false - за спаданням.
     */
    void sortByPrice(bool ascending = true);

    /**
     * @brief Сортує список автомобілів за роком випуску.
     * @param ascending true для сортування за зростанням, false - за спаданням.
     */
    void sortByYear(bool ascending = true);

    /**
     * @brief Сортує список автомобілів за витратами пального.
     * @param ascending true для сортування за зростанням, false - за спаданням.
     */
    void sortByFuelConsumption(bool ascending = true);

    // --- Пошук та фільтрація ---

    /**
     * @brief Фільтрує та виводить автомобілі за вказаною маркою.
     * @param b Марка для фільтрації.
     */
    void filterByBrand(const std::string& b) const;

    /**
     * @brief Фільтрує та виводить автомобілі за вказаним кольором.
     * @param c Колір для фільтрації.
     */
    void filterByColor(const std::string& c) const;

    /**
     * @brief Фільтрує та виводить автомобілі за вказаним роком.
     * @param y Рік для фільтрації.
     */
    void filterByYear(int y) const;

    /**
     * @brief Фільтрує та виводить автомобілі за вказаною моделлю.
     * @param m Модель для фільтрації.
     */
    void filterByModel(const std::string& m) const;

    /**
     * @brief Запускає діалог пошуку авто за маркою.
     */
    void findByBrand() const;

    /**
     * @brief Запускає розширений пошук за декількома критеріями.
     */
    void searchCars() const;

    /**
     * @brief Знаходить та виводить економічні авто (витрати пального нижче ліміту).
     */
    void findEconomicalCars() const;

    /**
     * @brief Знаходить та виводить "сімейні" авто (4+ дверей).
     */
    void findFamilyCars() const;

    // --- Сервісні методи ---
    void showHelp() const;
    void showHelpnotadm() const;

    /**
     * @brief Валідатор введених значень за ключем.
     * @tparam Type Тип значення (наприклад, `int`, `double`).
     * @param value Значення для перевірки.
     * @param flag Ключ правила ("year","fuel","AC","multi","safe","price","doors","distance","fuelPrice" тощо).
     * @return `true`, якщо значення коректне.
     */
    template <typename Type>
    bool checker(Type value, const std::string& flag) const;

    /**
     * @brief Безпечне зчитування цілого числа з `std::cin`.
     * @return Коректно введене ціле число.
     */
    int safeInput() const;

    /**
     * @brief Безпечне зчитування `double` з `std::cin`.
     * @return Коректно введене число з плаваючою комою.
     */
	double safeInputDouble() const;

private:
    std::vector<std::shared_ptr<Car>> cars;
    void printCarIndexList() const;
};