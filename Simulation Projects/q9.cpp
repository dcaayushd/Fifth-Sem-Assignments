#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double chi_square_test(const vector<double>& observed, const vector<double>& expected) {
  if (observed.size() != expected.size()) {
    cerr << "Error: Observed and expected frequencies must have the same size." << endl;
    return -1;
  }

  int n = observed.size();
  double chi_square_value = 0.0;

  for (int i = 0; i < n; ++i) {
    chi_square_value += pow(observed[i] - expected[i], 2) / expected[i];
  }

  return chi_square_value;
}

int main() {
  // Example data
  vector<double> observed = {20, 30, 50};
  vector<double> expected = {25, 25, 50};

  double chi_square = chi_square_test(observed, expected);
  cout << "Chi-square value: " << chi_square << endl;

  // You would typically compare the calculated chi-square value to a critical value
  // or calculate a p-value to make a decision about the null hypothesis.

  return 0;
}
