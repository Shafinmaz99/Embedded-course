#ifndef WEATHER_STATION_H
#define WEATHER_STATION_H

#include <string>
#include <iostream>

class WeatherStation {
private:
    std::string location;
    float* readings;     // dynamic array
    size_t size;         // number of readings currently stored
    size_t capacity;     // allocated capacity

    void resize(size_t newCapacity);

public:
    explicit WeatherStation(const std::string& loc = "");
    WeatherStation(const WeatherStation& other);
    WeatherStation& operator=(const WeatherStation& other);
    ~WeatherStation();

    void addReading(float value);
    void printReadings() const;

    void saveToFile(const std::string& filename) const;

    static WeatherStation loadFromFile(const std::string& filename);

    const std::string& getLocation() const { return location; }
    size_t getSize() const { return size; }
    float* getReadingsPtr() const { return readings; }
};

#endif