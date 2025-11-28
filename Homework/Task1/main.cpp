#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

int main() {
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    vector<double> temperature = {20.5, 19.9, 22.8, 23.4, 21.5};

    tuple<string, double> highest = make_tuple(days[0], temperature[0]);

    cout << "\nTemperature: ";

    for (size_t i = 0; i < days.size(); i++) {
        cout << days[i] << ": " << temperature[i] << "Celcius:";


        if (temperature[i] < 10)
            cout << "Cold";
        else if (temperature[i] <= 20)
            cout << "Ok";
        else
            cout << "Warm";

        cout << endl;

        if (temperature[i] > get<1>(highest)) {
            highest = make_tuple(days[i], temperature[i]);
        }
    }

    cout << "Highest Temperature on " << get<0>(highest)
         << " with " << get<1>(highest) << "Celcius" << endl;

    return 0;

}
