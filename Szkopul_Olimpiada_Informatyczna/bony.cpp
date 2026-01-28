#include <iostream>
#include <bitset>
#include <vector>

// bierzemy a najmniejszych paczek ktorych reszta z dzielenia przez liczbe uczestnikow wynosi zero
// kolejno a, 2a, 3a, 4a, ... 
// warto dodac ze kazda paczka jest TYLKO JEDNA

// musimy wypisac ktory klient kupil bon

// wykupienie paczek
// powoduje braki na osi
// trzeba je przeskoczyc

// co przybliza nas do bonu na osi

using ull = unsigned long long;

constexpr ull max_dim = 1'000'001;
std::bitset<max_dim> dostepne;
std::bitset<max_dim> bony;

ull last_w[max_dim];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    dostepne.flip();

    for (ull i = 0; i < max_dim; i++) last_w[i] = 0;

    ull m; std::cin >> m;
    for (ull i = 0; i < m; i++) {
        ull x; std::cin >> x;
        bony[x] = true;
    }

    ull klient = 1;
    std::vector<ull> szczesciaze;

    ull n; std::cin >> n;
    for (ull i = 0; i < n; i++) {
        ull a; std::cin >> a;

        ull o = a;             // osoby pozostale
        ull w = last_w[a] + a; // wartosc
        
        while (o) {
            if (w >= max_dim) {
                klient += o;
                break;
            }

            if (dostepne[w]) {
                dostepne[w] = false;

                if (bony[w]) {
                    szczesciaze.push_back(klient);
                }

                klient++;
                o--; 
            }

            w += a;
        }

        last_w[a] = w - a;
    }

    std::cout << szczesciaze.size() << '\n';
    for (ull s : szczesciaze) {
        std::cout << s << '\n';
    }
}
