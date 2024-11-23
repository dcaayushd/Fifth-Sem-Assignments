#include<iostream>
using namespace std;

static int count = 0;  // Making count explicitly global

void SelectionSort(int A[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int least = A[i];
        int loc = i;
        for(int j = i + 1; j < n; j++)
        {
            if(A[j] < least)
            {
                least = A[j];
                loc = j;
            }
            ::count = ::count + 6;  // Using scope resolution operator
        }
        A[loc] = A[i];
        A[i] = least;
        ::count = ::count + 8;  // Using scope resolution operator
    }
}

int main()
{
    int a[] = {100, 200, 22, 12, 45, 809, 130, 170, 10, 200};
    int n = sizeof(a)/sizeof(int);
    
    cout << "Before sorting: \n";
    for(int i = 0; i < n; i++)
    {
        cout << a[i] << "\t";
    }
    cout << endl;
    
    SelectionSort(a, n);
    
    cout << "After sorting: \n";
    for(int i = 0; i < n; i++)
    {
        cout << a[i] << "\t";
    }
    cout << endl;
    
    cout << "No. of Steps required for " << n << " is " << ::count;  // Using scope resolution operator
    return 0;
}