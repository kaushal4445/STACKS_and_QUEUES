#include <iostream>
#include <queue>
using namespace std;

class MyStack {
public:
    queue<int> q1;
    queue<int> q2;

    MyStack() {
    }

    // Push element into stack
    void push(int x) {
        // Move all elements from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        // Push new element into q1
        q1.push(x);

        // Move all elements back to q1
        while (!q2.empty()) {
            q1.push(q2.front());
            q2.pop();
        }
    }

    // Remove top element
    int pop() {
        if (q1.empty()) {
            cout << "Stack is Empty" << endl;
            return -1;
        }

        int ans = q1.front();
        q1.pop();

        return ans;
    }

    // Return top element
    int top() {
        if (q1.empty()) {
            cout << "Stack is Empty" << endl;
            return -1;
        }

        return q1.front();
    }

    // Check if stack is empty
    bool empty() {
        return q1.empty();
    }
};

int main() {

    MyStack s;

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:" << endl;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.push(x);
    }

    cout << "\nTop element: " << s.top() << endl;

    cout << "Popped element: " << s.pop() << endl;

    cout << "Top element after pop: " << s.top() << endl;

    cout << "Popped element: " << s.pop() << endl;

    if (s.empty()) {
        cout << "Stack is Empty" << endl;
    }
    else {
        cout << "Stack is Not Empty" << endl;
    }

    return 0;
}