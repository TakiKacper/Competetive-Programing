#include <iostream>

long long srednice[300000];
long long minima[300000];

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m; // wysokosc i liczba
    std::cin >> n >> m;

    long long min = 10000000001;

    for (int i = 0; i < n; i++) {
        long long x;
        std::cin >> x;
        
        min = std::min(x, min);

        srednice[i] = x;
        minima[i]   = min;
    }

    int pozycja = n;

    for (int i = 0; i < m; i++) {
        long long krazek; std::cin >> krazek;

        if (pozycja != -1) pozycja--; //zeby takie same nie wypadaly na tym samym

        while (pozycja != -1) {
            long long srednica = srednice[pozycja];
            long long minimum  = minima[pozycja];

            if (srednica >= krazek && minimum >= krazek) break;
            pozycja--;
        }
    }

    std::cout << pozycja + 1;
}
