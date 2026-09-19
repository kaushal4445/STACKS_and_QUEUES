#include<stack>
#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack <int> st;
        int n = nums.size();
        vector<int> nge(n);
        for(int i = 2*n-1; i >=0; i--){
            int ind = i % n;
            int currEle = nums[ind];
            while(! st.empty() && st.top()<= currEle){
                st.pop();
            }
            if( i<n){
            if(st.empty())
            nge[i] = -1;
            else
            nge[i] = st.top();
            }
            st.push(currEle);
        }
        return nge;
    }
};
int main(){
    Solution s;
    vector<int> nums = {1,2,1};
    vector<int> ans = s.nextGreaterElements(nums);
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}