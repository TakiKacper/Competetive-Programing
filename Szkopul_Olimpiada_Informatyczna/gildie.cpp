#include <iostream>
#include <vector>

constexpr int max_n = 200000;
char stany[max_n];
bool ma_krawedz[max_n];

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    
    int n, m; std::cin >> n >> m;

    for (int i = 0; i < n; i++) stany[i] = 'N';
    

    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        ma_krawedz[x0] = true; ma_krawedz[x1] = true;

        if (stany[x0] == stany[x1] && stany[x0] == 'N') {
            stany[x0] = 'S'; stany[x1] = 'K';
        }
        else if (stany[x0] == 'N') {
            stany[x0] = (stany[x1] == 'S' ? 'K' : 'S');
        }
        else if (stany[x1] == 'N') {
            stany[x1] = (stany[x0] == 'S' ? 'K' : 'S');
        }
        // oba przypisane nic nie robimy
    }

    for (int i = 0; i < n; i++) {
        if (!ma_krawedz[i]) {
            std::cout << "NIE\n";
            return 0;
        }
    }

    std::cout << "TAK\n";
    for (int i = 0; i < n; i++) {
        std::cout << stany[i] << '\n';
    }
}
