#include<stack>
#include<vector>
#include<iostream>
using namespace std;
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
            for(int  asteroid :  asteroids ){
                if( asteroid > 0){
                    ans.push_back( asteroid);
                } else {
                    int currentSize = abs(asteroid);
                bool destroyed = false;
                 while(! ans.empty() && ans.back() >  0){
                  int topSize = abs(ans.back());

                  if(topSize < currentSize){
                    ans.pop_back();
                  } else {
                    if(topSize == currentSize){
                        ans.pop_back();
                    }
                    destroyed = true;
                    break;
                  }
            }
            if(! destroyed){
                ans.push_back(asteroid);
            }

                }
            }
            return ans;
        
    }
};

int main() {
    vector<int> asteroids = {5,10, -5};
    Solution obj;
    vector<int> answer = obj.asteroidCollision(asteroids);

    for (int value : answer) {
        cout << value << " ";
    }
    return 0;
}