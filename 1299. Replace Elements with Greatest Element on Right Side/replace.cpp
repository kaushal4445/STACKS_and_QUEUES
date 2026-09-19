#include <stack>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {

        int n = arr.size();
        vector<int> ans(n);

        int greatest = -1;

        for(int i = n - 1; i >= 0; i--) {

            ans[i] = greatest;

            greatest = max(greatest, arr[i]);
        }

        return ans;
    }
};
int main() {

    Solution s;

    vector<int> arr = {17, 18, 5, 4, 6, 1};

    vector<int> ans = s.replaceElements(arr);

    for(int i = 0; i < ans.size(); i++) {
      cout << ans[i] << " ";
    }

    cout << endl;

    return 0;
}