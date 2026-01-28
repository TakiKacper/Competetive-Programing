#include <iostream>
#include <queue>
#include <set>

constexpr int tree_base = 1 << 20; // 1 048 576

using ull = unsigned long long;

std::queue<int> pos[32];
ull             off[tree_base * 2 + 1];

// all to the right, may include itself
void add(int pos) {
    pos += tree_base;
    
    // always add on your right, if it is not where you came from
    while (true) {
        int prev = pos; pos /= 2; if (pos == 0) break;
        if (prev % 2 == 0) off[pos * 2 + 1]++;
    }
}

ull quarry(int pos) {
    ull offset = 0;
    pos += tree_base;

    while (pos != 0) {
        offset += off[pos];
        pos /= 2;
    }

    return offset;
};

int main() {
    std::cin.tie(0); 
    std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n; // 1 000 000

    std::string str; std::cin >> str;
    for (int i = 0; i < n; i++) pos[str[i] - 'A'].push(i);

    ull wyn = 0;

    std::cin >> str;
    for (int i = 0; i < n; i++) {
        auto& q = pos[str[i] - 'A'];

        ull p = q.front(); q.pop();
        ull o = quarry(p);

        wyn += p - o;

        add(p);
    }

    std::cout << wyn;
}
