#include <iostream>
#include <queue>

using namespace std;

struct Customer {
    int arrivalTime;
    int serviceTime;
};

int main() {
    queue<Customer> waitingQueue;
    int totalCustomers = 5; // Replace with actual number of customers

    // Sample customer data (replace with actual data)
    Customer customer1 = {0, 3};
    Customer customer2 = {2, 2};
    Customer customer3 = {5, 4};
    Customer customer4 = {8, 1};
    Customer customer5 = {10, 3};

    waitingQueue.push(customer1);
    waitingQueue.push(customer2);
    waitingQueue.push(customer3);
    waitingQueue.push(customer4);
    waitingQueue.push(customer5);

    int clock = 0;
    int totalWaitTime = 0;
    int maxQueueLength = 0;

    while (!waitingQueue.empty()) {
        Customer currentCustomer = waitingQueue.front();
        waitingQueue.pop();

        // Idle time if customer arrives before the clock
        if (currentCustomer.arrivalTime > clock) {
            clock = currentCustomer.arrivalTime;
        }

        // Update wait time
        totalWaitTime += clock - currentCustomer.arrivalTime;

        // Update clock
        clock += currentCustomer.serviceTime;

        // Update max queue length
        maxQueueLength = max(maxQueueLength, (int)waitingQueue.size() + 1);
    }

    double averageWaitTime = (double)totalWaitTime / totalCustomers;
    double averageServiceTime = (double)(clock - waitingQueue.front().arrivalTime) / totalCustomers;

    cout << "Average waiting time: " << averageWaitTime << endl;
    cout << "Average service time: " << averageServiceTime << endl;
    cout << "Maximum queue length: " << maxQueueLength << endl;

    return 0;
}
