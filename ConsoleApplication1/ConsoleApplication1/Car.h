#pragma once
#include "Vehicle.h"
#include "Configuration.h"
#include <sstream>

/**
 * @class Car
 * @brief Клас, що представляє автомобіль.
 * @details Є нащадком класу Vehicle і містить специфічну для авто
 * інформацію: витрати пального, кількість дверей та комплектацію.
 */
class Car : public Vehicle {
public:
    // --- Конструктори та деструктор ---
    Car();
    Car(const std::string& b, const std::string& c, const std::string& m, double fuel, int doors, int y, double p, const Configuration& config);
    Car(const Car& other);
    Car(Car&& other) noexcept;
    ~Car();

    // --- Getters ---
    double getFuelConsumption() const;
    int getDoorCount() const;
    std::string getModel() const;

    // --- Setters ---
    void setFuelConsumption(double f);
    void setDoorCount(int d);
    void setModel(const std::string& m);

    /**
     * @brief Перевіряє, чи є автомобіль економічним.
     * @param limit Поріг витрат пального у літрах на 100 км (L/100km).
     * @return true, якщо витрати пального цього автомобіля менші або рівні @p limit; інакше false.
     */
    bool isEconomical(double limit) const;

    /**
     * @brief Визначає, чи підходить автомобіль як сімейний.
     * @details У прикладі реалізації можуть використовуватися критерії: кількість дверей (наприклад, >=4),
     * наявність систем безпеки в конфігурації тощо.
     * @return true, якщо автомобіль вважається сімейним згідно з критеріями; інакше false.
     */
    bool isFamilyCar() const;

    /**
     * @brief Порівнює цей автомобіль з іншим за витратами пального.
     * @param other Інший автомобіль для порівняння.
     * @return true, якщо цей автомобіль має менші витрати пального (краща економія), ніж @p other; інакше false.
     */
    bool compareByFuel(const Car& other) const;

    /**
     * @brief Перевіряє, чи автомобіль новіший за вказаний рік.
     * @param y Рік для порівняння.
     * @return true, якщо рік випуску автомобіля строго більший за @p y; інакше false.
     */
    bool isNewerThan(int y) const;

    /**
     * @brief Обчислює вартість пального для проїзду 100 км.
     * @param fuelPrice Ціна пального за літр (у тій же валюті, що й ціна автомобіля).
     * @return Оцінкова вартість проїзду 100 км, обчислена як fuelConsumption (L/100km) * @p fuelPrice (валюта/літр).
     */
    double costPer100km(double fuelPrice) const;

    /**
     * @brief Повертає вік автомобіля в повних роках.
     * @details Вік обчислюється відносно поточного календарного року.
     * @return Кількість повних років від року випуску автомобіля до поточного року.
     */
    int getAge() const;

    // --- Реалізація абстрактних методів ---
    void print() const override;
    std::string toCSV() const override;

    /**
     * @brief Створює об'єкт Car з рядка CSV.
     * @param line Рядок у форматі CSV.
     * @return Новий об'єкт Car.
     */
    static Car fromCSV(const std::string& line);

private:
    Configuration config;
    double fuelConsumption;
    int doorCount;
    std::string model;
};