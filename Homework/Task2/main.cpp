#include "WeatherStation.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

template <typename T>
double average(const T* arr, size_t n) {
    if (n == 0) {
        throw std::runtime_error("Cannot compute average: no readings.");
    }
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) sum += arr[i];
    return sum / static_cast<double>(n);
}

int main() {
    try {
        WeatherStation lahti("Lahti");

        lahti.addReading(22.5f);
        lahti.addReading(24.0f);
        lahti.addReading(26.3f);
        lahti.addReading(21.8f);
        lahti.addReading(25.7f);

        std::cout << "Location: Lahti\n";

        std::vector<float> vec(lahti.getReadingsPtr(),
                               lahti.getReadingsPtr() + lahti.getSize());

        std::sort(vec.begin(), vec.end());

        std::cout << "Readings: ";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i];
            if (i + 1 < vec.size()) std::cout << " ";
        }
        std::cout << "\n";

        double avg = average(lahti.getReadingsPtr(), lahti.getSize());
        std::cout.setf(std::ios::fixed);
        std::cout.precision(2);
        std::cout << "Average: " << avg << "\n";

        const float threshold = 25.0f;
        auto aboveCount = std::count_if(vec.begin(), vec.end(),
                                        [threshold](float x) { return x > threshold; });

        std::cout << "Readings above 25°C: " << aboveCount << "\n";

        const std::string filename = "lahti_readings.txt";
        try {
            lahti.saveToFile(filename);
            std::cout << "Saved to file: " << filename << "\n";
        } catch (const std::exception& e) {
            std::cerr << "File save error: " << e.what() << "\n";
        }

        try {
            WeatherStation reconstructed = WeatherStation::loadFromFile(filename);

            std::cout << "\n--- Reconstructed Station ---\n";
            std::cout << "Location: " << reconstructed.getLocation() << "\n";
            reconstructed.printReadings();
        } catch (const std::exception& e) {
            std::cerr << "File load error: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}