#include <iostream>
#include <algorithm>

using ull = unsigned long long;

constexpr ull M     = 1e9 + 7;
constexpr int max_n = 1e6;

int klaser[max_n];

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> klaser[i];

    std::sort(klaser, klaser + n);

    int b_itr = n - 1;  // poczatek przedzialu pasujacych kieszonek, inc
    int e_itr = n;      // koniec przedzialu pasujacych kieszonek,   inc

    ull wynik = 1;

    // kolejne monety, od tylu iterujac
    for (int m = n; m != 0; m--) {
        // Przesuwamy przedzial pasujacych monet
        while (b_itr != 0 && klaser[b_itr - 1] >= m) b_itr--;

        // Mnozymy razy ilosc opcji dla n-tej monety
        (wynik *= (e_itr - b_itr)) %= M;

        // Jedna z opcji zostala wzieta, zakladamy ze ta najwieksza, bez straty ogolnosci
        e_itr--;
    }

    std::cout << wynik;
}
