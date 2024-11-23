#include <iostream>

using namespace std;


struct Item {
    int value, weight;

    // Constructor
    Item(int value, int weight)
        : value(value), weight(weight)
    {
    }
};

int c =0;
bool cmp(struct Item a, struct Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
     c  = c + 4;
    return r1 > r2;
}


double fractionalKnapsack(struct Item arr[],
                        int N, int size)
{
    // Sort Item on basis of ratio
    sort(arr, arr + size, cmp);

    // Current weight in knapsack
    int curWeight = 0;

    // Result (value in Knapsack)
    double finalvalue = 0.0;

    c += 2;
    for (int i = 0; i < size; i++) {

    
        if (curWeight + arr[i].weight <= N) 
        {
            curWeight += arr[i].weight;
            finalvalue += arr[i].value;
            c  += 4;
        }

        
        else {
            int remain = N - curWeight;
            finalvalue += arr[i].value
                        * ((double)remain
                            / arr[i].weight);
            c += 6;
            break;
        }
        c = c+4;
    }

    // Returning final value
    return finalvalue;
}

// Driver Code
int main()
{
    // Weight of knapsack
    int N = 60;

    // Given weights and values as a pairs
    Item arr[] = { { 100, 10 },
                { 280, 40 },
                { 120, 20 },
                { 120, 24 } };

    int size = sizeof(arr) / sizeof(arr[0]);

    // Function Call
    cout << "Maximum profit earned = "<< fractionalKnapsack(arr, N, size)<<endl;
    cout<<"No. of required steps : "<<c;
    return 0;
}