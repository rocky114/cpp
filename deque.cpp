#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void printKMax(int arr[], int n, int k) 
{
    if (n < k) {
        return;
    } 

    int steps = n - k + 1;
    
    std::deque<int> mydeque {};

    for (int i = 0; i < k; i++) {
        mydeque.push_back(arr[i]);
    }

    int max = *std::max_element(mydeque.begin(), mydeque.end());
    std::cout << max << " ";

    for (int i = k; i < n; i++) {   
        int front = mydeque.front();

        mydeque.pop_front();
        mydeque.push_back(arr[i]);
                    
        if (front == max) {
            max = *std::max_element(mydeque.begin(), mydeque.end());
        } else {
            max = std::max(max, arr[i]);
        }

        std::cout << max << " ";
    }

    std::cout << std::endl;
}

int main()
{
    /*  int arr[] {3, 4, 5, 8, 1, 4, 10};
      printKMax(arr, 7, 4);
      return 0;
    */

    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;

        int arr[n] {};

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        printKMax(arr, n, k);
    }
    
    return 0;
}