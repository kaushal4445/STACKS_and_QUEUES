#include <stack>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
  public:
    vector<int> prevSmaller(vector<int>& arr) {
        //  code here
        int n = arr.size();

               // Stack to store potential next smaller elements
               stack<int> st;

               // Answer array initialized with -1
               vector<int> ans(n, -1);

               // Traverse the array from right to left
               for (int i = 0; i <n; i++) {

                   // Pop elements from stack while they are >= current element
                   while (!st.empty() && st.top() >= arr[i]) {
                       st.pop();
                   }

                  if (st.empty()) {
                                 ans[i] = -1;
                             }
                             else {
                                 ans[i] = st.top();
                             }
                   // Push current element to stack
                   st.push(arr[i]);
               }

               // Return result
               return ans;
    }
};
int main() {
    Solution s;
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> ans = s.prevSmaller(arr);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}