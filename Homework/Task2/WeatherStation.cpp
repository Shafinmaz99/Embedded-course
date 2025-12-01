#include "WeatherStation.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>

WeatherStation::WeatherStation(const std::string& loc)
    : location(loc), readings(nullptr), size(0), capacity(0) {}

void WeatherStation::resize(size_t newCapacity) {
    float* newArr = new float[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = readings[i];
    }
    delete[] readings;
    readings = newArr;
    capacity = newCapacity;
}

WeatherStation::WeatherStation(const WeatherStation& other)
    : location(other.location), readings(nullptr), size(other.size), capacity(other.capacity) {
    if (capacity > 0) {
        readings = new float[capacity];
        for (size_t i = 0; i < size; ++i) readings[i] = other.readings[i];
    }
}

WeatherStation& WeatherStation::operator=(const WeatherStation& other) {
    if (this == &other) return *this;

    delete[] readings;
    location = other.location;
    size = other.size;
    capacity = other.capacity;

    readings = nullptr;
    if (capacity > 0) {
        readings = new float[capacity];
        for (size_t i = 0; i < size; ++i) readings[i] = other.readings[i];
    }
    return *this;
}

WeatherStation::~WeatherStation() {
    delete[] readings;
}

void WeatherStation::addReading(float value) {
    if (capacity == 0) {
        capacity = 4;
        readings = new float[capacity];
    } else if (size == capacity) {
        resize(capacity * 2);
    }
    readings[size++] = value;
}

void WeatherStation::printReadings() const {
    std::cout << "Readings: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << readings[i];
        if (i + 1 < size) std::cout << " ";
    }
    std::cout << "\n";
}

void WeatherStation::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    out << "Location: " << location << "\n";
    out << "Readings:";
    for (size_t i = 0; i < size; ++i) {
        out << " " << readings[i];
    }
    out << "\n";

    if (!out.good()) {
        throw std::runtime_error("I/O error while writing to: " + filename);
    }
}

WeatherStation WeatherStation::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + filename);
    }

    std::string line;

    if (!std::getline(in, line)) {
        throw std::runtime_error("File format error (missing location line).");
    }
    if (line.rfind("Location:", 0) != 0) {
        throw std::runtime_error("File format error (location line malformed).");
    }
    std::string loc = line.substr(std::string("Location:").size());
    loc.erase(0, loc.find_first_not_of(" \t"));

    WeatherStation ws(loc);

    if (!std::getline(in, line)) {
        throw std::runtime_error("File format error (missing readings line).");
    }
    if (line.rfind("Readings:", 0) != 0) {
        throw std::runtime_error("File format error (readings line malformed).");
    }

    std::string readingsPart = line.substr(std::string("Readings:").size());
    std::istringstream iss(readingsPart);
    float val;
    while (iss >> val) {
        ws.addReading(val);
    }

    return ws;
}