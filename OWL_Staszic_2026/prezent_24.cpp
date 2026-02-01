#include <iostream>
#include <set>

// startujemy w L
// po m liczbach musimy wybrać minimum
// bierzemy minimum
// powtarzaj, az wybierzemy k te minimum
// jezeli dotrzemy do R nie idz dalej, rozwaz co masz

constexpr int max_n = 100'000;

int  n, q;
uint A[max_n];

// O(n log m)
void zapytka(int l, int r, int m, int k) {
    std::multiset<uint> pamiec;

    for (int i = l; i <= r; ) {
        if (pamiec.size() == m) {
            int najmniejsza = *pamiec.begin();
            pamiec.erase(pamiec.begin());

            k--;

            if (k == 0) {
                std::cout << najmniejsza << '\n';
                return;
            }  
        }
        else {
            pamiec.insert(A[i]);
            i++;
        }
    }

    auto itr = pamiec.begin();
    while (--k) itr++;

    std::cout << *itr << '\n';
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    std::cin >> n >> q;
    for (int i = 0; i < n; i++) std::cin >> A[i];

    for (int i = 0; i < q; i++) {
        int l, r, m, k; std::cin >> l >> r >> m >> k; l--; r--;
        zapytka(l, r, m, k);
    }
}
