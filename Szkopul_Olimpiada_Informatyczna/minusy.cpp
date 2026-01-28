#include <iostream>
#include <bitset>

// mamy wyrazenie
// +, -, -, -, -, -

// mamy zrobic
// +, n, n, n, n, n
// gdzie n to nie wiadomo

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    std::bitset<1000000> do_negacji;

    int n; std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        char c; std::cin >> c;
        do_negacji.set(i, c == '+');
    }

    // jezeli wartosc nie ta teraz, ale ta nastepna wymaga negacji, zaczynamy negowac
    bool prev_nawias = false;
    for (int i = 1; i < n - 1; i++) {
        if (do_negacji[i]) {
            std::cout << '-';
            std::cout << '(';
            while (do_negacji[i]) {
                std::cout << '-';
                i++; if (i == n - 1) break;
            }
            std::cout << ')';
            prev_nawias = true;
        }
        else {
            std::cout << '-';
            prev_nawias = true;
        }
        std::cout << std::flush;
    }
}
