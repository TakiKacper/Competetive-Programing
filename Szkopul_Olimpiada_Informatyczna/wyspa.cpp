#include <iostream>

using ll = long long;

constexpr int max_n = 50000;

int n;
ll sc[max_n + 12]; // suma czesciowa dystansu [0, miasto], za wskazowkami

inline ll dst_cw(int m1, int m2) {
    // czy idac w prawo mijamy miasto 0?
    if (m2 < m1) {
        ll dst_ccw_m1 = sc[0] - sc[m1];
        return dst_ccw_m1 + sc[m2];
    }
    return std::abs(sc[m2] - sc[m1]);
}

inline ll dst_ccw(int m1, int m2) {
    // czy idac w lewo mijamy miasto 0?
    if (m2 > m1) {
        ll dst_ccw_m2 = sc[n] - sc[m2];
        return dst_ccw_m2 + sc[m1];
    }
    ll r = std::abs(sc[m1] - sc[m2]);
    if (r == 0) return sc[n];
    return r;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    std::cin >> n;
    
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        ll e; std::cin >> e;
        sum += e; sc[i + 1] = sum;
    }

    int m1 = 0;
    int m2 = 0;

    ll dst = 0;

    // przesuwamy miasto m1 w prawo
    while (m1 != n) {
        // tak dlugo jak sie da, wyrownujemy dystans [lewo, prawo]
        // przesuwajac miasto m2 w prawo
        do {
            ll dst_change = dst_cw (m2, m2 + 1); // krok do nastepnej pozycji miasta m2
            ll dst_left   = dst_ccw(m1, m2);
            ll dst_right  = dst_cw (m1, m2);

            ll current_amp  = std::abs(dst_left - dst_right);
            ll moved_m2_amp = std::abs((dst_left - dst_change) - (dst_right + dst_change));

            // nie warto
            if (current_amp < moved_m2_amp) break;
            
            // porusz m2
            // m2 jest ograniczone do jednego obrotu, inaczej weszlibysmy w sytuacje symetryczna
            // juz przeanalizowana, a algorytm nie mial by wlasnosci stopu
            m2++; if (m2 == n) { m2--; break; }
        } while (1); 

        dst = std::max(dst, std::min(dst_cw(m1, m2), dst_ccw(m1, m2)));
        m1++;
    }

    std::cout << dst;
}
