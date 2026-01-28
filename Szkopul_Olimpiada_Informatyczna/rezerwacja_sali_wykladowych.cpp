#include <iostream>
#include <vector>
#include <algorithm>

constexpr int max_n = 30000;
constexpr int max_n_2_rouned = 1 << 15;

int tree[2 * max_n_2_rouned];

void add(int pos, int val) {
    pos += max_n_2_rouned;
    tree[pos] = std::max(tree[pos], val);
    pos /= 2;

    while (pos) {
        tree[pos] = std::max(tree[2 * pos], tree[2 * pos + 1]);
        pos /= 2;
    }
}

int quarry(int end) {
    int beg = max_n_2_rouned;
    end += max_n_2_rouned;

    int res = 0;

    while ((beg / 2) != (end / 2)) {
        if (beg % 2 == 0) res = std::max(tree[beg + 1], res);
        if (end % 2 == 1) res = std::max(tree[end - 1], res);
        beg /= 2; end /= 2;
    }

    return res;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
    int wyn = 0;

    std::vector<std::pair<int, int>> wyklady;
    wyklady.resize(n);

    for (int i = 0; i < n; i++) {
        std::cin >> wyklady[i].first >> wyklady[i].second;
    }

    std::sort(wyklady.begin(), wyklady.end());

    for (int i = 0; i < n; i++) {
        int p = wyklady[i].first;
        int k = wyklady[i].second;

        // najlepszy wynik przed rozpoczaciem
        int before = quarry(p + 1);
        int v = before + k - p;

        add(k, before + k - p);
        wyn = std::max(wyn, v);
    }

    std::cout << wyn;
}
