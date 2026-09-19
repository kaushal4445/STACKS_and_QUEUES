#include <stack>
#include <vector>
#include <iostream>
using namespace std;
class MinStack {
     // Initialize a stack
   stack<long long> st;
long long mini;
public:
    MinStack() {
         
    }
    
    void push(int value) {
       if(st.empty()){
    mini = value;
    st.push(value);
    return;

        } 
        if(value > mini){
            st.push(value);
        } else {
            st.push( 2ll* value -mini);
            mini = value;
        }
        
    }
    
    void pop() {
        if(st.empty())
            return;
            long long x = st.top();
            st.pop();
            if(x < mini)
            mini = 2ll*mini - x;
    }
    
    int top() {
        if(st.empty()) 
        return -1;
        long long x= st.top();
        if(mini < x){
        return x;
        }
        else{
            return mini;
        }


        
    }
    
    int getMin() {
        return  mini;
        
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
int main() {
    MinStack* obj = new MinStack();
    obj->push(3);
    obj->push(5);
    cout << "Top: " << obj->top() << endl; // Output: 5
    cout << "Min: " << obj->getMin() << endl; // Output: 3
    obj->push(2);
    obj->push(1);
    cout << "Min: " << obj->getMin() << endl; // Output: 1
    obj->pop();
    cout << "Min: " << obj->getMin() << endl; // Output: 2
    return 0;
}