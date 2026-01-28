#include <iostream>
#include <queue>

// wez najwyzsze o takiej samej wysokosci h
// sklej obok siebie
// wez nastepna wysokosc j
// zaplakatuj [h, j]
// wepchnij obnizone

using ull = unsigned long long;

struct budynek {
    ull w;
    int p;
    int k;
};

budynek b[250001];

struct comp {
    bool operator()(const int& l, const int& r) const {
        if (b[l].w != b[r].w) return b[l].w < b[r].w;
        return b[l].p < b[r].p; // nigdy nie sa rowne, k nie sprawdzamy
    };
};

std::priority_queue<
    int,
    std::vector<int>, 
    comp
> q;

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;
    for (int i = 0; i < n; i++) {
        ull d, w; std::cin >> d >> w;
        b[i] = {w, i, i}; q.push(i);
    }

    ull wyn = 0;

    while (q.size()) {
        // po prostu zaplakatuj goscia
        if (q.size() == 1) {
            wyn++; break;
        }

        // obecnie rozwazany najwyzszy budynek
        auto curr = q.top(); q.pop();

        // indekst budynkow do wrzucenia na kolejke z powrotem
        std::vector<int> ind = {curr};

        while (true) {
            // wez nastepny
            if (!q.size()) break;
            auto next = q.top();

            // wysokosci sie nie zgadzaja, konczymy
            if (b[curr].w != b[next].w) break;

            // cokolwiek sie nie wydarzy, bierzemy budek next
            q.pop();

            // jezeli jest kontynuacja budynku curr, to zlacz je
            if (b[curr].p - 1 == b[next].k) {
                b[curr].p = b[next].p;
            }
            // inaczej zakoncz z budynkiem curr, przejdz do budowania next
            else {
                b[curr].w = 0;

                if (b[curr].p != 0) 
                    b[curr].w = b[b[curr].p - 1].w;

                if (b[curr].k + 1 != n) 
                    b[curr].w = std::max(b[curr].w, b[b[curr].k + 1].w);

                ind.push_back(next);
                curr = next;
            }
        }

        b[curr].w = 0;

        if (b[curr].p != 0) 
            b[curr].w = b[b[curr].p - 1].w;

        if (b[curr].k + 1 != n) 
            b[curr].w = std::max(b[curr].w, b[b[curr].k + 1].w);
        
        wyn += ind.size();
        for (auto j : ind) q.push(j);

        // zaplakatowalismy calosc
        if (ind.size() == 1 && b[ind[0]].p == 0 && b[ind[0]].k == n - 1) break;
    }

    std::cout << wyn;
}
