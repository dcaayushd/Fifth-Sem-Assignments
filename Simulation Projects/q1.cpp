#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Seed the random number generator

    int total_points = 1000000;
    int points_inside_circle = 0;

    for (int i = 0; i < total_points; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        double distance = x * x + y * y;
        if (distance <= 1.0) {
            points_inside_circle++;
        }
    }

    double pi_estimate = 4 * (double)points_inside_circle / total_points;
    cout << "Estimated value of Pi: " << pi_estimate << endl;

    return 0;
}
