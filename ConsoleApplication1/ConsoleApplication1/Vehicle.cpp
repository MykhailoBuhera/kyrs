#include "Vehicle.h"
using namespace std;

// Конструктори
Vehicle::Vehicle() : brand(""), color(""), year(0), price(0.0) {}

Vehicle::Vehicle(const string& b, const string& c, int y, double p, const string& m)
    : brand(b), color(c), year(y), price(p), model(m) {}

Vehicle::Vehicle(const Vehicle& other)
    : brand(other.brand), color(other.color), year(other.year), price(other.price) {}

Vehicle::Vehicle(Vehicle&& other) noexcept
    : brand(move(other.brand)), color(move(other.color)), year(other.year), price(other.price) {}

// Деструктор
Vehicle::~Vehicle() {
    cout << "[Vehicle] Знищено " << endl;
}

// Getters
string Vehicle::getBrand() const { return brand; }
string Vehicle::getColor() const { return color; }
int Vehicle::getYear() const { return year; }
double Vehicle::getPrice() const { return price; }

// Setters
void Vehicle::setBrand(const string& b) { brand = b; }
void Vehicle::setColor(const string& c) { color = c; }
void Vehicle::setYear(int y) { year = y; }
void Vehicle::setPrice(double p) { price = p; }

bool Vehicle::isOlderThan(int y) const { return year < y; }
bool Vehicle::isCheaperThan(double p) const { return price < p; }
int Vehicle::age(int currentYear) const { return currentYear - year; }
void Vehicle::applyDiscount(double percent) { price -= price * (percent / 100.0); }
bool Vehicle::isBrand(const string& b) const { return brand == b; }
string Vehicle::getModel() const {
    return model;
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
       if (this != &other) {
           brand = other.brand;
           model = other.model;
           color = other.color;
           year = other.year;
           price = other.price;
       }
       return *this;
   }

