#include <iostream>
#include <vector>
#include <bitset>

int p, q; // p + q <= 60 000
int n;    // <= 300 000

// dzwig kladzie elementy na pozycjach: { x }, {x + p lub x + q}, oraz {x + p + q}
// nigdy nie wywolamy dzwigu w pozycji x dwa razy
// za kazdym razem musimy zastanowic sie czy warto nam uruchomic {+p czy +q}
// zawsze musimy odpalic dźwig w pozycji 1

constexpr int safe_bitset_size = 300000 + 60000 + 128;
std::bitset<safe_bitset_size> w = {};

struct akcja {
    int x, y, z;
};

std::vector<akcja> program;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> p >> q >> n;

    // p <= q
    if (p > q) std::swap(p, q);

    for (int x = 0; x < n; x++) {
        if (w[x] || w[x + p + q]) continue;

        // x + p
        if (!w[x + p]) {
            w[x]         = true;
            w[x + p]     = true;
            w[x + p + q] = true;
            program.push_back({x, x + p, x + p + q});
        }
        // x + q
        else {
            w[x]         = true;
            w[x + q]     = true;
            w[x + p + q] = true;
            program.push_back({x, x + q, x + p + q});
        }
    }

    std::cout << program.size() << '\n';
    for (auto a : program) std::cout << (a.x + 1) << ' ' << (a.y + 1) << ' ' << (a.z + 1) << '\n';
}
