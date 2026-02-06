#include <iostream>
#include <stack>

constexpr int max_n = 20; //5 * 1e5;

int  n;
uint a[max_n];

int min_left [max_n]; // od kiedy moja wartosc jest minimum z lewej strony
int min_right[max_n]; // od kiedy moja wartosc jest minimum z prawej strony

uint ans[max_n + 1];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    
    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::stack<int> st;
    for (int i = 0; i < n; i++) {
        // wyrzuc wszystkie wieksze i rowne
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        min_left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        min_right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        int len = min_right[i] - min_left[i] - 1;
        ans[len] = std::max(ans[len], a[i]);
    }

    for (int i = n - 1; i >= 1; i--) {
        ans[i] = std::max(ans[i], ans[i + 1]);
    }

    for (int i = 1; i <= n; i++) std::cout << ans[i] << ' ';
}
