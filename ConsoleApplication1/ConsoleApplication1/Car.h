#pragma once
#include "Vehicle.h"
#include <sstream>
#include "Configuration.h"

class Car : public Vehicle {
public:
    // Конструктори
    Car();
    Car(const std::string& b, const std::string& c, const std::string& m, double fuel, int doors, int y, double p, const Configuration& config);
    Car(const Car& other);
    Car(Car&& other) noexcept;
    ~Car();

    // Getters
    double getFuelConsumption() const;
    int getDoorCount() const;

    // Setters
    void setFuelConsumption(double f);
    void setDoorCount(int d);

    // Методи предметної області
    bool isEconomical(double limit) const;       // Економічність
    bool isFamilyCar() const;                    // Сімейне авто (>=4 дверей)
    bool compareByFuel(const Car& other) const;  // Порівняння витрат пального
    bool isNewerThan(int y) const;               // Чи новіший за рік
    double costPer100km(double fuelPrice) const; // Вартість поїздки на 100 км
    int getAge() const;

    // Реалізація абстрактних методів
    void print() const override;
    std::string toCSV() const override;
    std::string getModel() const;
    void setModel(const std::string& m);

    static Car fromCSV(const string& line);

private:
    Configuration config;
    double fuelConsumption;
    int doorCount;
    std::string model;

};
