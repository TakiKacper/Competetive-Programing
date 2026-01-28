#include <iostream>
#include <vector>
#include <string>

int  w[182][182]; // wynik
int  v[182][182]; // czy odwiedzony

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    // <= 182
    int n, m; std::cin >> n >> m;
    
    std::vector<std::pair<int, int>> q;

    for (int i = 0; i < n; i++) {
        std::string str; std::cin >> str;
        for (int j = 0; j < m; j++) {
            if (str[j] == '0') continue;
            q.push_back({i, j});
            v[i][j] = true;
        }
    }

    decltype(q) nq;
    int dst = 0;
    
    while (q.size()) {
        auto check = [&](int f1, int f2) {
            if (f1 == -1 || f1 == 182) return;
            if (f2 == -1 || f2 == 182) return;

            if (v[f1][f2]) return;

            v[f1][f2] = true;
            nq.push_back({f1, f2});
        };

        for (auto& v : q) {
            w[v.first][v.second] = dst;
            check(v.first - 1, v.second);
            check(v.first + 1, v.second);
            check(v.first, v.second - 1);
            check(v.first, v.second + 1);
        }
        
        q.swap(nq);
        nq.clear();

        dst++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << w[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
