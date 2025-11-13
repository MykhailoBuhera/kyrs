#include "Configuration.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

static string trim(const string& s) {
    size_t a = 0;
    while (a < s.size() && isspace(static_cast<unsigned char>(s[a]))) ++a;
    size_t b = s.size();
    while (b > a && isspace(static_cast<unsigned char>(s[b - 1]))) --b;
    return s.substr(a, b - a);
}

static bool parseBoolToken(const string& tok) {
    string t = tok;
    transform(t.begin(), t.end(), t.begin(), [](unsigned char c) { return tolower(c); });
    t = trim(t);
    if (t == "1" || t == "true" || t == "yes") return true;
    if (t == "0" || t == "false" || t == "no") return false;
    throw invalid_argument(string("Invalid boolean token: '") + tok + "'");
}

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
    // Validate parameters that could be invalid at runtime
    if (packageName.empty()) {
        throw invalid_argument("Configuration::Configuration - packageName cannot be empty");
    }
    if (price < 0.0) {
        throw invalid_argument("Configuration::Configuration - price cannot be negative");
    }
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
void Configuration::setPackageName(const string& name) {
    if (name.empty()) throw invalid_argument("Configuration::setPackageName - name cannot be empty");
    packageName = name;
}

double Configuration::getPrice() const { return price; }
void Configuration::setPrice(double p) {
    if (p < 0.0) throw invalid_argument("Configuration::setPrice - price cannot be negative");
    price = p;
}

bool Configuration::isLuxury() const {
    return hasAirConditioner && hasMultimedia && hasSafetySystem;
}

void Configuration::toggleAirConditioner() { hasAirConditioner = !hasAirConditioner; }
void Configuration::toggleMultimedia() { hasMultimedia = !hasMultimedia; }
void Configuration::toggleSafety() { hasSafetySystem = !hasSafetySystem; }

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
    try {
        // Split into tokens by comma
        vector<string> tokens;
        string token;
        istringstream iss(line);
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 5) {
            throw invalid_argument(string("fromCSV: expected 5 fields, got ") + to_string(tokens.size()));
        }

        string packageNameTok = trim(tokens[0]);
        bool ac = parseBoolToken(tokens[1]);
        bool multimedia = parseBoolToken(tokens[2]);
        bool safety = parseBoolToken(tokens[3]);

        string priceTok = trim(tokens[4]);
        double priceVal = 0.0;
        try {
            size_t idx = 0;
            priceVal = stod(priceTok, &idx);
            if (idx != priceTok.length()) {
                throw invalid_argument(string("fromCSV: trailing characters in price token '") + priceTok + "'");
            }
        }
        catch (const invalid_argument& e) {
            throw invalid_argument(string("fromCSV: invalid price value: '") + priceTok + "'");
        }
        catch (const out_of_range& e) {
            throw invalid_argument(string("fromCSV: price out of range: '") + priceTok + "'");
        }

        // Validate parsed values
        if (packageNameTok.empty()) {
            throw invalid_argument("fromCSV: packageName is empty");
        }
        if (priceVal < 0.0) {
            throw invalid_argument("fromCSV: price cannot be negative");
        }

        // Construct and return Configuration. Use "Unknown" for brand/model as before.
        return Configuration("Unknown", "Unknown", packageNameTok, ac, multimedia, safety, priceVal);
    }
    catch (const exception& ex) {
        // Re-throw with context to help callers identify the problematic line
        throw invalid_argument(string("Configuration::fromCSV error parsing line: '") + line + "' -> " + ex.what());
    }
    catch (...) {
        throw invalid_argument(string("Configuration::fromCSV unknown error parsing line: '") + line + "'");
    }
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
