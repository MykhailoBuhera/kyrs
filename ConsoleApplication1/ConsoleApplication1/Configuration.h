#pragma once
#include "Vehicle.h"
#include "IPrintable.h"
#include <string>
#include <iostream>

/**
 * @class Configuration
 * @brief Клас, що представляє комплектацію автомобіля.
 * @details Зберігає інформацію про пакет опцій (кондиціонер, мультимедіа),
 * його назву та ціну. Є нащадком Vehicle та реалізує IPrintable.
 */
class Configuration : public Vehicle, public IPrintable {
public:
    Configuration& operator=(const Configuration& other);
    Configuration();
    Configuration(const std::string& brand, const std::string& model,
        const std::string& packageName, bool ac, bool multimedia, bool safety, double price);
    Configuration(const Configuration& other);
    Configuration(Configuration&& other) noexcept;
    ~Configuration();

    // --- Get/Set ---
    std::string getPackageName() const;
    void setPackageName(const std::string& name);
    double getPrice() const;
    void setPrice(double p);

    // --- 4 методи предметної області ---

    /**
     * @brief Перевіряє, чи є комплектація люксовою.
     * @return true, якщо всі опції включені, інакше false.
     */
    bool isLuxury() const;

    void toggleAirConditioner();
    void toggleMultimedia();
    void toggleSafety();

    // --- Реалізація інтерфейсу ---
    void print() const override;
    std::string toCSV() const override;

    /**
     * @brief Створює об'єкт Configuration з рядка CSV.
     * @param line Рядок у форматі CSV.
     * @return Новий об'єкт Configuration.
     */
    static Configuration fromCSV(const std::string& line);

private:
    std::string packageName;
    bool hasAirConditioner;
    bool hasMultimedia;
    bool hasSafetySystem;
    double price;
};