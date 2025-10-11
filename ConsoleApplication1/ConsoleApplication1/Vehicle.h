#pragma once
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
	Vehicle& operator=(const Vehicle& other);
    Vehicle();
    Vehicle(const string& b, const string& c, int y, double p, const string& m);
    Vehicle(const Vehicle& other);
    Vehicle(Vehicle&& other) noexcept;

    
    virtual ~Vehicle();

    // Getters
    string getBrand() const;
    string getColor() const;
    int getYear() const;
    double getPrice() const;
    string getModel() const;

    // Setters
    void setBrand(const string& b);
    void setColor(const string& c);
    void setYear(int y);
    void setPrice(double p);

    // Методи предметної області
    bool isOlderThan(int y) const;          // Чи старший за рік
    bool isCheaperThan(double p) const;     // Чи дешевший за ціну
    int age(int currentYear) const;         // Вік авто
    void applyDiscount(double percent);     // Знижка
    bool isBrand(const string& b) const;    // Чи відповідає марці

    // Віртуальні методи для реалізації у нащадках

    virtual void print() const = 0;
    virtual string toCSV() const = 0;

protected:
    string model;

private:
    string brand;
    string color;
    int year;
    double price;

};
 