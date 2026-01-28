#include <iostream>

using ull = unsigned long long;

// czerwone krawedzie z wiercholka
ull C[1000]; 

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    ull n, m; std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; std::cin >> a >> b; a--; b--;
        C[a]++; C[b]++;
    }

    // newton(n, 3)
    ull wszystkie   = n * (n - 1) * (n - 2) / 6;

    ull roznobarwne = 0;
    for (int i = 0; i < n; i++) roznobarwne += C[i] * (n - 1 - C[i]);
    roznobarwne /= 2;

    std::cout << (wszystkie - roznobarwne);
}
