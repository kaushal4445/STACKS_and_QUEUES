#include<stack>
#include<vector>
#include<iostream>
using namespace std;
class Solution {
private:
    // Next Smaller Element
    vector<int> findNSE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            ans[i] = !st.empty() ? st.top() : n;

            st.push(i);
        }

        return ans;
    }

    // Previous Smaller Element
    vector<int> findPSE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;

        for (int i = 0; i < n; i++) {

            while (!st.empty() && nums[st.top()] > nums[i]) {
                st.pop();
            }

            ans[i] = !st.empty() ? st.top() : -1;

            st.push(i);
        }

        return ans;
    }

    // Next Greater Element
    vector<int> findNGE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {

            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            ans[i] = !st.empty() ? st.top() : n;

            st.push(i);
        }

        return ans;
    }

    // Previous Greater Element
    vector<int> findPGE(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = 0; i < n; i++) {

            while (!st.empty() && nums[st.top()] < nums[i]) {
                st.pop();
            }
            ans[i] = !st.empty() ? st.top() : -1;

            st.push(i);
        }

        return ans;
    }

    long long sumSubarrayMins(vector<int>& nums) {

        int n = nums.size();

        vector<int> nse = findNSE(nums);
        vector<int> pse = findPSE(nums);

        long long sum = 0;

        for (int i = 0; i < n; i++) {

            long long left = i - pse[i];
            long long right = nse[i] - i;

            long long frequency = left * right;

            sum += frequency * nums[i];
        }

        return sum;
    }

    long long sumSubarrayMaxs(vector<int>& nums) {

        int n = nums.size();

        vector<int> nge = findNGE(nums);
        vector<int> pge = findPGE(nums);

        long long sum = 0;

        for (int i = 0; i < n; i++) {

            long long left = i - pge[i];
            long long right = nge[i] - i;

            long long frequency = left * right;

            sum += frequency * nums[i];
        }

        return sum;
    }

public:

    long long subArrayRanges(vector<int>& nums) {

        return sumSubarrayMaxs(nums) - sumSubarrayMins(nums);
    }
};
int main() {
    vector<int> arr = {1, 2, 3};
    
    // Creating an instance of Solution class.
    Solution sol;
    
    // Function call to find the sum of subarray ranges.
    long long ans = sol.subArrayRanges(arr);
    
    cout << "The sum of subarray ranges is: " << ans;
    
    return 0;
}