#include <stack>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0;
        int r = height.size() - 1;

        int total = 0;

        int leftmax = 0;
        int rightmax = 0;

        while (l < r) {

            if (height[l] <= height[r]) {

                if (leftmax > height[l]) {
                    total += leftmax - height[l];
                }
                else {
                    leftmax = height[l];
                }

                l++;
            }
            else {

                if (rightmax > height[r]) {
                    total += rightmax - height[r];
                }
                else {
                    rightmax = height[r];
                }

                r--;
            }
        }

        return total;
    }
};

int main() {

    Solution s;

    vector<int> height = {
        0, 1, 0, 2, 1, 0,
        1, 3, 2, 1, 2, 1
    };

    int total = s.trap(height);

    cout << "Total trapped water = " << total << endl;

    return 0;
}