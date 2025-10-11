#include "Configuration.h"
#include <string>
#include <sstream>

using namespace std;
Configuration::Configuration()
    : Vehicle("Unknown", "", 0, 0.0, "Unknown"),
    packageName("Basic"),
    hasAirConditioner(false),
    hasMultimedia(false),
    hasSafetySystem(false),
    price(0.0) {
}

Configuration::Configuration(const string& brand, const string& model,
    const string& packageName, bool ac, bool multimedia, bool safety, double price)
    : Vehicle(brand, "", 0, 0.0, model),
    packageName(packageName),
    hasAirConditioner(ac),
    hasMultimedia(multimedia),
    hasSafetySystem(safety),
    price(price) {
}

Configuration::Configuration(const Configuration& other)
    : Vehicle(other),
    packageName(other.packageName),
    hasAirConditioner(other.hasAirConditioner),
    hasMultimedia(other.hasMultimedia),
    hasSafetySystem(other.hasSafetySystem),
    price(other.price) {
}

Configuration::Configuration(Configuration&& other) noexcept
    : Vehicle(move(other)),
    packageName(move(other.packageName)),
    hasAirConditioner(other.hasAirConditioner),
    hasMultimedia(other.hasMultimedia),
    hasSafetySystem(other.hasSafetySystem),
    price(other.price) {
}

Configuration::~Configuration() {
    cout << "[Config] знищено " << endl;
}

string Configuration::getPackageName() const { return packageName; }
void Configuration::setPackageName(const string& name) { packageName = name; }

double Configuration::getPrice() const { return price; }
void Configuration::setPrice(double p) { price = p; }

bool Configuration::isLuxury() const {
    return hasAirConditioner && hasMultimedia && hasSafetySystem;
}

void Configuration::toggleAirConditioner() { hasAirConditioner = !hasAirConditioner; }
void Configuration::toggleMultimedia() { hasMultimedia = !hasMultimedia; }
void Configuration::toggleSafety() { hasSafetySystem = !hasSafetySystem; }

// Вивід інформації
void Configuration::print() const {
    cout << "Configuration: " << packageName
        << " | AC: " << (hasAirConditioner ? "Yes" : "No")
        << " | Multimedia: " << (hasMultimedia ? "Yes" : "No")
        << " | Safety: " << (hasSafetySystem ? "Yes" : "No")
        << " | Price: " << price << endl;
}

string Configuration::toCSV() const {
    ostringstream oss;
    oss << packageName << ","
        << hasAirConditioner << ","
        << hasMultimedia << ","
        << hasSafetySystem << ","
        << price;
    return oss.str();
}

Configuration Configuration::fromCSV(const string& line) {
    istringstream iss(line);
    string packageName;
    bool hasAirConditioner, hasMultimedia, hasSafetySystem;
    double price;

    getline(iss, packageName, ',');
    iss >> hasAirConditioner; iss.ignore();
    iss >> hasMultimedia; iss.ignore();
    iss >> hasSafetySystem; iss.ignore();
    iss >> price;

    return Configuration("Unknown", "Unknown", packageName, hasAirConditioner, hasMultimedia, hasSafetySystem, price);
}

Configuration& Configuration::operator=(const Configuration& other) {
    if (this != &other) {
        Vehicle::operator=(other); 
        packageName = other.packageName;
        hasAirConditioner = other.hasAirConditioner;
        hasMultimedia = other.hasMultimedia;
        hasSafetySystem = other.hasSafetySystem;
        price = other.price;
    }
    return *this;
}
