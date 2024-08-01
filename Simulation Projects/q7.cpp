

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double ks_statistic(const vector<double>& data1, const vector<double>& data2);
double empirical_cdf(const vector<double>& data, double x);

int main() {
    // Example data
    vector<double> data1 = {0.1, 0.4, 0.35, 0.8};
    vector<double> data2 = {0.2, 0.5, 0.3, 0.7};

    double ks = ks_statistic(data1, data2);
    cout << "KS statistic: " << ks << endl;

    return 0;
}

double ks_statistic(const vector<double>& data1, const vector<double>& data2) {
    vector<double> all_data = data1;
    all_data.insert(all_data.end(), data2.begin(), data2.end());
    sort(all_data.begin(), all_data.end());

    double max_diff = 0.0;
    for (double x : all_data) {
        double cdf1 = empirical_cdf(data1, x);
        double cdf2 = empirical_cdf(data2, x);
        double diff = fabs(cdf1 - cdf2);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff;
}

double empirical_cdf(const vector<double>& data, double x) {
    int count = 0;
    for (double value : data) {
        if (value <= x) {
            count++;
        }
    }
    return static_cast<double>(count) / data.size();
}
