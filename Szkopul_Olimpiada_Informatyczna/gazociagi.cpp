#include <iostream>
#include <queue>
#include <vector>
#include <set>

using ull = unsigned long long;

struct stacja {
    int  x, y;
    bool w; // wydobycia?
    int  idx;
};

struct comp_queue {
    // operatory odwrocone
    bool operator()(const stacja& a, const stacja& b) const {
        if (a.x != b.x) return a.x > b.x; // najpierw lewe (zachodnie)
        return a.y < b.y;                 // najpierw wyzsze (polnocne)
    }
};

struct comp_set {
    bool operator()(const stacja& a, const stacja& b) const {
        if (a.y != b.y) return a.y < b.y; // od najmniejszego do najwiekszego, zeby lower bound dzialal
        return a.x < b.x; // najpierw bierz te dalsze (zachodnie)
    }
};

std::priority_queue<
    stacja,
    std::vector<stacja>, 
    comp_queue
> Q;

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    
    int n; std::cin >> n;
    stacja s;
    
    s.w = true;
    for (int i = 0; i < n; i++) { 
        std::cin >> s.x >> s.y; s.idx = i + 1; Q.push(s);
    }

    s.w = false;
    for (int i = 0; i < n; i++) { 
        std::cin >> s.x >> s.y; s.idx = i + 1; Q.push(s);
    }
}

void answer() {
    std::multiset<stacja, comp_set> W; // ominiente wydobycia stacje
                                       // mozemy brac tylko takie o <= y

    ull dst = 0;
    std::vector<std::pair<int, int>> conn;                             
    
    while (Q.size()) {
        if (Q.top().w) {
            W.insert(Q.top());
        }
        else {
            auto itr = W.lower_bound(Q.top());
            if (itr == W.end()) itr = std::prev(W.end());
            
            dst += std::abs(itr->x - Q.top().x);
            dst += std::abs(itr->y - Q.top().y);
            conn.push_back({itr->idx, Q.top().idx});

            W.erase(itr);
        }

        Q.pop();
    }
    
    std::cout << dst << '\n';
    for (auto p : conn) std::cout << p.first << ' ' << p.second << '\n';
}

int main() {
    load();
    answer();
}
