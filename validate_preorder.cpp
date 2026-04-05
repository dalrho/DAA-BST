#include <bits/stdc++.h>
using namespace std;

bool isValidPreorder(const vector<int>& preorder) {
    stack<int> st;
    int lowerBound = INT_MIN;

    for (int value : preorder) {
        // Violation of BST property
        if (value < lowerBound)
            return false;

        // Move to right subtree
        while (!st.empty() && value > st.top()) {
            lowerBound = st.top();
            st.pop();
        }

        st.push(value);
    }
    return true;
}

int main() {
    vector<vector<int>> testCases = {
        {8, 5, 1, 7, 10, 12},      // VALID
        {8, 10, 5, 1, 7, 12},     // INVALID
        {5, 2, 1, 3, 6},          // VALID
        {7, 9, 6},                // INVALID
        {10, 5, 1, 7, 40, 50},    // VALID
        {10, 5, 7, 1}             // INVALID
    };

    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test case " << i + 1 << ": ";
        cout << (isValidPreorder(testCases[i]) ? "VALID" : "INVALID") << endl;
    }

    return 0;
}

