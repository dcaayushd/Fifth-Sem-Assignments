// C++ Program for Lucas Primality Test
#include <math.h>
#include <vector>
#include <random>
#include <iostream>

using namespace std;

// function to generate prime factors of n
void primeFactors(int n, vector<int> &factors)
{
    // if 2 is a factor
    if (n % 2 == 0)
        factors.push_back(2);
    while (n % 2 == 0)
        n = n / 2;

    // if prime > 2 is factor
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
            factors.push_back(i);
        while (n % i == 0)
            n = n / i;
    }
    if (n > 2)
        factors.push_back(n);
}

// this function produces power modulo
// some number. It can be optimized to
// using
int power(int n, int r, int q)
{
    int total = n;
    for (int i = 1; i < r; i++)
        total = (total * n) % q;
    return total;
}

string lucasTest(int n)
{
    // Base cases
    if (n == 1)
        return "neither prime nor composite";
    if (n == 2)
        return "prime";
    if (n % 2 == 0)
        return "composite1";

    // Generating and storing factors
    // of n-1
    vector<int> factors;
    primeFactors(n - 1, factors);

    // Array for random generator. This array
    // is to ensure one number is generated
    // only once
    int random[n - 3];
    for (int i = 0; i < n - 2; i++)
        random[i] = i + 2;

    // shuffle random array to produce randomness
    shuffle(random, random + n - 3,
            default_random_engine(time(0)));

    // Now one by one perform Lucas Primality
    // Test on random numbers generated.
    for (int i = 0; i < n - 2; i++)
    {
        int a = random[i];
        if (power(a, n - 1, n) != 1)
            return "composite";

        // this is to check if every factor
        // of n-1 satisfy the condition
        bool flag = true;
        for (int k = 0; k < factors.size(); k++)
        {
            // if a^((n-1)/q) equal 1
            if (power(a, (n - 1) / factors[k], n) == 1)
            {
                flag = false;
                break;
            }
        }

        // if all condition satisfy
        if (flag)
            return "prime";
    }
    return "probably composite";
}

// Driver code
int main()
{
    cout << 7 << " is " << lucasTest(7) << endl;
    cout << 9 << " is " << lucasTest(9) << endl;
    cout << 37 << " is " << lucasTest(37) << endl;
    return 0;
}
