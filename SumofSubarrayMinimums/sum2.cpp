#include<stack>
#include<vector>
#include<iostream>
using namespace std;
class Solution {
    private:
    vector<int> findPreviousLess(vector<int>& arr) {
        int n = arr.size();
        vector<int> previousLess(n, -1);
        stack<int> st1;
        for (int i = 0; i < n; i++) {
            while (!st1.empty() &&
                   arr[st1.top()] >= arr[i]) {
                st1.pop();
            }
            if (!st1.empty()) {
                previousLess[i] = st1.top();
            }
            st1.push(i);
        }

        return previousLess;
    }

   vector<int> findNextLessOrEqual(vector<int>& arr) {
        int n = arr.size();
        vector<int> nextLessOrEqual(n, n);
        stack<int> st2;
        for (int i = n - 1; i >= 0; i--) {
            while (!st2.empty() &&
                   arr[st2.top()] > arr[i]) {
                st2.pop();
            }
            if (!st2.empty()) {
                nextLessOrEqual[i] = st2.top();
            }
            st2.push(i);
        }

        return nextLessOrEqual;
    }
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
       long long mod = 1e9 +7;

        vector<int> pse = findPreviousLess(arr);
        vector<int> nse = findNextLessOrEqual(arr);

        long long answer = 0;
        for (int i = 0; i < n; i++) {
            long long left = i - pse[i];
            long long right = nse[i] - i;
            // long long contribution = (arr[i] * left) % mod;
            // contribution = (contribution * right) % mod;
            // answer = (answer + contribution) % mod;
            answer = (answer + (right*left *arr[i]) % mod )  % mod;
        }

        return (int)answer;
    }
};

int main() {
    vector<int> arr = {3, 1, 2, 4};

    Solution obj;
    cout << obj.sumSubarrayMins(arr) << endl;

    return 0;
}


