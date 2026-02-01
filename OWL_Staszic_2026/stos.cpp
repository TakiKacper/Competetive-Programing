#include <iostream>
#include <vector>

// szukamy wzorca "maly", "duzy", "mniejszy"
// od nam dzieli permutacje

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int n; std::cin >> n;

    int segments = 1;

    std::vector<int> st; // stos
    long long mid = -1;  // "duzy"

    for(int i = 0; i < n; i++) {
        uint a; std::cin >> a;

        // wykrylismy wzorzec, zacznij nowy segment
        if(a < mid) {
            segments++;
            st.clear();
            mid = -1;
        }

        // aktualizacja stosu
        while(!st.empty() && a > st.back()) {
            mid = std::max(mid, (long long)st.back());
            st.pop_back();
        }

        st.push_back(a);
    }

    std::cout << segments << "\n";
}
