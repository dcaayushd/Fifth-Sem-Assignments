#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double autocorrelation(const vector<double>& data, int lag) {
    int n = data.size();
    double sum_xy = 0.0;
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_x2 = 0.0;
    double sum_y2 = 0.0;

    for (int i = 0; i < n - lag; i++) {
        sum_xy += data[i] * data[i + lag];
        sum_x += data[i];
        sum_y += data[i + lag];
        sum_x2 += data[i] * data[i];
        sum_y2 += data[i + lag] * data[i + lag];
    }

    double numerator = sum_xy - (sum_x * sum_y) / (n - lag);
    double denominator = sqrt((sum_x2 - sum_x * sum_x / (n - lag)) * (sum_y2 - sum_y * sum_y / (n - lag)));

    return numerator / denominator;
}

int main() {
    vector<double> data = {2.5, 0.5, 2.2, 1.1, 0.3, 0.0, 1.4, 1.9, 1.8};
    int lag = 1; // You can change the lag value

    double acf = autocorrelation(data, lag);
    cout << "Autocorrelation for lag " << lag << ": " << acf << endl;

    return 0;
}
