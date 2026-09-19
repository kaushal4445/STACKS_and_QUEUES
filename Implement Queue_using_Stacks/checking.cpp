#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
public:
    stack<int> s1;
    stack<int> s2;

    MyQueue() {
    }

    // Push element into queue
    void push(int x) {
        // Move all elements from s1 to s2
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        // Push new element
        s1.push(x);

        // Move elements back to s1
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    // Remove front element
    int pop() {
        if (s1.empty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }

        int ans = s1.top();
        s1.pop();

        return ans;
    }

    // Get front element
    int peek() {
        if (s1.empty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }

        return s1.top();
    }

    // Check empty
    bool empty() {
        return s1.empty();
    }
};

int main() {

    MyQueue q;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: " << endl;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        q.push(x);
    }

    cout << "\nFront element: " << q.peek() << endl;

    cout << "Popped element: " << q.pop() << endl;

    cout << "Front element after pop: " << q.peek() << endl;

    cout << "Popped element: " << q.pop() << endl;

    if (q.empty()) {
        cout << "Queue is Empty" << endl;
    }
    else {
        cout << "Queue is Not Empty" << endl;
    }

    return 0;
}