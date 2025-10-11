#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Car.h"
#include "Configuration.h"

using namespace std;

class CarManager {
public:
	CarManager();
    CarManager(const CarManager& other);
	CarManager(CarManager&& other) noexcept;
	~CarManager();

    // --- CRUD ---
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    void addCar();
    void showAllCars() const;
    void editCar();
    void removeCar();

    // --- Аналітика ---
    void findMostEconomicalCar() const;
    void averagePriceInPeriod() const;

    // --- Сортування ---
    void sortByPrice(bool ascending = true);
    void sortByYear(bool ascending = true);
    void sortByFuelConsumption(bool ascending = true);

    // --- Фільтрація ---
    void filterByBrand(const string& b) const;
    void filterByColor(const string& c) const;
    void filterByYear(int y) const;
	void filterByModel(const string& m) const;

    // --- Нові методи (з предметної області) ---
    void findByBrand() const;
    void findEconomicalCars() const;
    void findFamilyCars() const;
    void applyDiscountToCar();
    void showCarAge() const;
    void calcTripCost() const;
    void searchCars() const;
    // --- Сервісний метод ---
    void showHelp() const;
    void showHelpnotadm() const;

private:
    vector<shared_ptr<Car>> cars;

    void printCarIndexList() const;
};
 //get set methods add