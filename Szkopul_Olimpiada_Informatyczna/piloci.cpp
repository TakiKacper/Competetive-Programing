#include <iostream>
#include <deque>

// w szczegolnosci warunek zadania
// max przedzialu - min przedzialu <= t

constexpr int max_n = 3'000'000;
using ull = unsigned long long;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    // max amplituda, liczba elementow
    ull t, n; std::cin >> t >> n;

    // poczatek zakresu
    int beg = 0;

    // obecny zakres / gasienica
    // wartosc, pozycja
    std::deque<std::pair<ull, int>> min_Q, max_Q;

    ull ans = 1;
    
    for (int i = 0; i < n; i++) {
        ull x; std::cin >> x;

        // push min
        while (!min_Q.empty() && min_Q.back().first > x) min_Q.pop_back();
        min_Q.push_back({x, i});

        // push max
        while (!max_Q.empty() && max_Q.back().first < x) max_Q.pop_back();
        max_Q.push_back({x, i});

        // przesuwaj poczatek az przedzial poprawnym sie stanie
        while ((max_Q.front().first - min_Q.front().first) > t) {
            beg++;
            if (min_Q.front().second < beg) min_Q.pop_front();
            if (max_Q.front().second < beg) max_Q.pop_front(); 
        }
        
        ans = std::max(ans, (ull)(i - beg + 1));
    }

    std::cout << ans;
}
