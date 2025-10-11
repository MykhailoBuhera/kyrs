#pragma once
#include <iostream>
#include <string>

/**
 * @class Vehicle
 * @brief Абстрактний базовий клас, що представляє транспортний засіб.
 * @details Визначає загальні властивості для всіх транспортних засобів,
 * такі як марка, колір, рік та ціна, а також базовий інтерфейс.
 */
class Vehicle {
public:
    /**
     * @brief Перевантажений оператор присвоювання.
     */
    Vehicle& operator=(const Vehicle& other);

    /**
     * @brief Конструктор за замовчуванням.
     */
    Vehicle();

    /**
     * @brief Конструктор з параметрами.
     * @param b Марка.
     * @param c Колір.
     * @param y Рік випуску.
     * @param p Ціна.
     * @param m Модель.
     */
    Vehicle(const std::string& b, const std::string& c, int y, double p, const std::string& m);

    /**
     * @brief Конструктор копіювання.
     */
    Vehicle(const Vehicle& other);

    /**
     * @brief Конструктор переміщення.
     */
    Vehicle(Vehicle&& other) noexcept;

    /**
     * @brief Віртуальний деструктор.
     */
    virtual ~Vehicle();

    // --- Getters ---
    std::string getBrand() const;
    std::string getColor() const;
    int getYear() const;
    double getPrice() const;
    std::string getModel() const;

    // --- Setters ---
    void setBrand(const std::string& b);
    void setColor(const std::string& c);
    void setYear(int y);
    void setPrice(double p);

    // --- 5 власних методів ---

    /**
     * @brief Перевіряє, чи є транспортний засіб старшим за вказаний рік.
     * @param y Рік для порівняння.
     * @return true, якщо авто старше, інакше false.
     */
    bool isOlderThan(int y) const;

    /**
     * @brief Перевіряє, чи є транспортний засіб дешевшим за вказану ціну.
     * @param p Ціна для порівняння.
     * @return true, якщо авто дешевше, інакше false.
     */
    bool isCheaperThan(double p) const;

    /**
     * @brief Розраховує вік транспортного засобу.
     * @param currentYear Поточний рік.
     * @return Вік у роках.
     */
    int age(int currentYear) const;

    /**
     * @brief Застосовує відсоткову знижку до ціни.
     * @param percent Відсоток знижки.
     */
    void applyDiscount(double percent);

    /**
     * @brief Перевіряє, чи співпадає марка авто із заданою.
     * @param b Марка для порівняння.
     * @return true, якщо марки співпадають, інакше false.
     */
    bool isBrand(const std::string& b) const;

    // --- Чисто віртуальні методи ---

    /**
     * @brief Чисто віртуальний метод для виводу інформації про об'єкт.
     */
    virtual void print() const = 0;

    /**
     * @brief Чисто віртуальний метод для конвертації даних у CSV-рядок.
     * @return Рядок у форматі CSV.
     */
    virtual std::string toCSV() const = 0;

protected:
    std::string model;

private:
    std::string brand;
    std::string color;
    int year;
    double price;
};