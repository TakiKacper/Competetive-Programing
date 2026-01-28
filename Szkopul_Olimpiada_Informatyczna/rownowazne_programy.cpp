#include <iostream>
#include <queue>

/*
nieprzekraczalne instrukcje, z punkty widzenia instrukcji k, dziela kod na czesci

k, k, k, GRANICA, k, k

utworz dla kazdej litery czesci, programu, i sprawdz czy maja taka sama liczebnosc instrukcji k
jezeli tak, to znaczy ze nie moga ale i nie musza przechodzic ergo dzialo

dla kazdej litery trzymaj adj[], liter ktore trzeba podzielic przy spotkaniu
zeby nie iterowac *1000, zeby wiedziec po prostu
*/

constexpr int max_n = 100000;
constexpr int max_k = 1000;

int n, k, m;

std::vector<int> block[max_k + 1];
std::queue<int>  areas[max_k + 1];

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> k >> m;

    // Load barriers
    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1;
        block[x0].push_back(x1);
        block[x1].push_back(x0);
    }

    // Load areas of first program
    {
        std::vector<int> counts(k + 1, 0);

        for (int i = 0; i < n; i++) {
            int x; std::cin >> x;
            counts[x]++;

            for (int b : block[x]) {
                areas[b].push(counts[b]);
                counts[b] = 0;
            }
        }

        // push remaining
        for (int i = 0; i < k + 1; i++) {
            areas[i].push(counts[i]);
        }
    }

    // Compare second program
    {
        std::vector<int> counts(k + 1, 0);

        for (int i = 0; i < n; i++) {
            int x; std::cin >> x;
            counts[x]++;

            for (int b : block[x]) {
                // new area, and there is non to compare
                if (!areas[b].size()) {
                    std::cout << "NIE";
                    return 0;
                }

                auto l = areas[b].front(); 
                areas[b].pop();

                // not matching sizes
                if (l != counts[b]) {
                    std::cout << "NIE";
                    return 0;
                }

                counts[b] = 0;
            }
        }

        // push remaining
        for (int i = 0; i < k + 1; i++) {
            // new area, and there is non to compare
            if (!areas[i].size()) {
                std::cout << "NIE";
                return 0;
            }

            auto l = areas[i].front(); 
            areas[i].pop();

            // not matching sizes
            if (l != counts[i]) {
                std::cout << "NIE";
                return 0;
            }

            counts[i] = 0;
        }
    }

    std::cout << "TAK";
}
