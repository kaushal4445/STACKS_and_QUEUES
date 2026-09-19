#include <stack>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
          stack<char> st;  // Stack to store opening brackets

        for (auto it : s) {
            if (it == '(' || it == '{' || it == '[')
                st.push(it);  // Push opening brackets to stack
            else {
                if (st.empty()) return false;  // No matching opening bracket
                char ch = st.top();
                st.pop();

                // Check for matching pair
                if ((it == ')' && ch == '(') ||
                    (it == ']' && ch == '[') ||
                    (it == '}' && ch == '{'))
                    continue;
                else
                    return false;
            }
        }
        return st.empty();  // True if all brackets matched
    }
};
int main() {
    Solution s;
    string str = "{[()]}";
    bool ans = s.isValid(str);
    if (ans)
        cout << "The string is valid." << endl;
    else
        cout << "The string is not valid." << endl;
    return 0;
}