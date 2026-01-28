#include <iostream>
#include <vector>
#include <climits>

// najmniejszy dystans z miasta 1: 
//     std::min(dys_cw_1[i], dys_ccw_1[i])
// najmniejszy dystans miast a i b 
//    std::min(
//      std::abs(dys_cw_1[a]  - dys_cw_1[b]),   // oba w prawo idac
//      std::abs(dys_ccw_1[a] - dys_ccw_1[b]),  // oba w lewo idac
//      std::abs(dys_ccw_1[a] + dys_cw_1[b]),   // w lewo przez jedynke
//      std::abs(dys_cw_1[a]  + dys_ccw_1[b])   // w prawo przez jedynke
//    )

using ull = unsigned long long;

constexpr int max_n = 10000;

int zap[max_n];
int dys[max_n];

int dys_cw_1[max_n];  // suma czesciowa dystansu w prawo [0, miasto n]
int dys_ccw_1[max_n]; // suma czesciowa dystansu w lewo [0, miasto n] 

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
 
    for (int i = 0; i < n; i++) {
        std::cin >> zap[i] >> dys[i];
    }

    // suma czesciowa w prawo
    int psum = 0;
    for (int i = 0; i < n; i++) {
        dys_cw_1[i] = psum;
        psum += dys[i];
    }

    // suma czesciowa w lewo
    psum = 0;
    for (int i = n - 1; i != 0; i--) {
        psum += dys[i];
        dys_ccw_1[i] = psum;
    }

    // Robimy obliczenie kosztu dla miasta 0
    ull koszt_z = 0;

    int prawa_granica = 0;
    int lewa_granica  = 0;

    ull zapotrzebowanie_lewo  = 0;
    ull zapotrzebowanie_prawo = 0;

    for (int i = 0; i < n; i++) {
        uint dystans = std::min(
            dys_cw_1[i],
            dys_ccw_1[i]
        );
        
        if (dys_cw_1[i] < dys_ccw_1[i]) {
            zapotrzebowanie_prawo += zap[i];
            prawa_granica = std::max(i, prawa_granica);
        }
        else if (i != 0) {
            zapotrzebowanie_lewo += zap[i];
            if (lewa_granica == 0) lewa_granica = i;
        }

        koszt_z += dystans * zap[i];
    }

    // trzymamy sume cystern na lewo i prawo
    // gdy przesuwamy sie w prawo
    // koszt += suma_lewo  * zmiana_dst
    // koszt -= suma_prawo * zmiana_dst

    // optymalny koszt
    ull koszt_o = koszt_z;

    // idziemy do kolejnych miast w prawo
    for (int m = 1; m < n; m++) {
        uint dst_zmiana = (m - 1 == 0 ? dys_cw_1[m] : dys_cw_1[m] - dys_cw_1[m - 1]);

        // miasto m - 1 zostaje opuszczone wiec dolacza sie do lewa
        zapotrzebowanie_lewo += zap[m - 1];

        // poprawiamy koszta o powyższe
        koszt_z -= zapotrzebowanie_prawo * dst_zmiana;
        koszt_z += zapotrzebowanie_lewo  * dst_zmiana;

        // a zapotrzebowanie prawa maleje bo miasto staje sie alko stolica
        zapotrzebowanie_prawo -= zap[m];

        // czy warto wlaczyc najbardziej lewy element na prawo?
        do {
            // dystans [m, lewa granica]
            uint dst_lewo;  // czy w lewo mijamy miasto 0?
            if (lewa_granica > m) dst_lewo = dys_ccw_1[lewa_granica] + dys_cw_1[m];
            else                  dst_lewo = dys_cw_1[m] - dys_cw_1[lewa_granica];
            
            // dystans [m, prawa granica]
            uint dst_prawo; // czy w prawo mijamy miasto 0?
            if (prawa_granica < m) dst_prawo = dys_ccw_1[m] + dys_cw_1[prawa_granica];
            else                   dst_prawo = dys_cw_1[prawa_granica] - dys_cw_1[m];

            if (dst_lewo > dst_prawo + dys[prawa_granica]) {
                zapotrzebowanie_lewo  -= zap[lewa_granica];
                zapotrzebowanie_prawo += zap[lewa_granica];

                // w takim razie przeliczamy koszt przenoszonego miasta
                koszt_z -= zap[lewa_granica] * dst_lewo;
                koszt_z += zap[lewa_granica] * (dst_prawo + dys[prawa_granica]); 

                lewa_granica  = std::modulus<int>()(lewa_granica + 1, n);
                prawa_granica = std::modulus<int>()(prawa_granica + 1, n);
            }
            else break;
        } while (1);

        koszt_o = std::min(koszt_o, koszt_z);
    }

    std::cout << koszt_o;
}
