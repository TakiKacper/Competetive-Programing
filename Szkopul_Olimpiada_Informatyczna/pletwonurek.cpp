#include <iostream>

const int INF = 1e9;

int main() {
    int O, N;
    std::cin >> O >> N;

    int K;
    std::cin >> K;

    int dp[O + 1][N + 1];

    // Inicjalizujemy caly stan jak INF
    for (int o = 0; o < O + 1; o++) {
        for (int n = 0; n < N + 1; n++) {
            dp[o][n] = INF;
        }
    }

    // Zerowa masa jest potrzebna, by miec zero tlenu i zero azotu
    dp[0][0] = 0;

    for (int k = 0; k < K; k++) {
        // Ładujemy butle
        int o, n, w; std::cin >> o >> n >> w;

        // Patrzymy na kazda istniejaca kombinacje, ja bedziemy przesuwac o butle
        // Ogolnie lecimy do tylu, bo inaczej moglo by sie zdarzyc ze natrafili bysmy na przesunienty stan w przyszlosci
        // I przesuneli go znowu o ta sama butle
        // A przeciez kazda butle mozemy uzyc tylko raz!

        // O[i] przesunelo by sie na O[i + di], di > 0
        // jako ze i + di jest wieksze od i, iterujac do przodu natrafilibysmy na ta pozycje!

        // W ogolnosci trzeba isc w druga strone do przesuniencia, to istotna notatka
        // jezeli kiedys mielibysmy natrafic na problem plecakowy z ujemnymi wartosciami
        for (int i = O; i >= 0; i--) {
            for (int j = N; j >= 0; j--) {
                // Sprawdzamy czy dana ilosc tlenu i azotu zostala juz chociaz raz osiagnieta
                if (dp[i][j] == INF) continue;

                // Zwiekszamy ilosc tlenu i azotu, z granica
                int ni = std::min(O, i + o); 
                int nj = std::min(N, j + n);

                // By uzyskac ilosc ni tlenu i nj azotu
                // Mozemy użyc już istniejacego rozwiazania, badz innege przesunietego o butle
                dp[ni][nj] = std::min(dp[ni][nj], dp[i][j] + w);
            }
        }
    }

    std::cout << dp[O][N];
}
