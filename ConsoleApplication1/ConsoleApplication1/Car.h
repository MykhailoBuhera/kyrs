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

    // --- методи предметної області ---
    bool isEconomical(double limit) const;
    bool isFamilyCar() const;
    bool compareByFuel(const Car& other) const;
    bool isNewerThan(int y) const;
    double costPer100km(double fuelPrice) const;
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