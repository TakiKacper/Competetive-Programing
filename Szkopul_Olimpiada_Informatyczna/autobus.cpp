#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

// w tym zadaniu posortowalem przystanki 
// od lewej do prawej w pierwszej kolejnosci
// od dolu do gory w drugiej kolenosci
// mozna zauwazyc że najlepsza odpowiedz dla przystanku
// to najwieksza odpowiedz dla przedzialu ponizej ([1, wysokosc przystanka]) + liczba ludzi na przystanku
// to klasyczne drzewo przedzialowe z pytaniami na przedziale [0, x]
// obie osie sa symetryczne, mozna tez uzyc osi x jako osi drzewa

// jako ze zakres kazdej z osi jest bardzo duzy (10^9)
// ale przystankow jest o wiele mniej to liczba unikalnych wartosci
// po zeskalowaniu bedzie mozliwa do zaalokowowania na potrzeby drzewa
// dlatego kod ponizej skaluje zakres wartosci osi y z 10^9 do <= max K == 10^5

struct przystanek {
    uint x, y;  // koordynaty
    uint p;     // ludzie
};

struct sort_przystankow_w_obu_osiach {
    // jako ze uzywamy priority queue
    // ktore wybiera najwieksza wartosc
    // operatory odwrocone
    bool operator()(const przystanek& a, const przystanek& b) const {
        if (a.x != b.x) return a.x > b.x;   // od lewej do prawej
        return a.y > b.y;                   // od dolu  do gory
    }
};

struct sort_przystankow_po_wysokosci {
    bool operator()(const przystanek& a, const przystanek& b) const {
        return a.y < b.y; // od dolu  do gory
    }
};

std::priority_queue<
    przystanek, 
    std::vector<przystanek>, 
    sort_przystankow_w_obu_osiach
> Q;

constexpr int tree_base_size = 1 << 20;
uint tree[2 * tree_base_size];

void push(uint height, uint people) {
    height += tree_base_size;

    tree[height] = std::max(tree[height], people);

    while (height /= 2) {
        auto l = tree[height * 2];
        auto r = tree[height * 2 + 1];
        tree[height] = std::max(l, r);
    }
}

// odpowiedz na przedziale [0, height]
uint quarry(uint height) {
    uint beg = tree_base_size;
    uint end = tree_base_size + height + 1;

    uint res = 0;

    while ((beg / 2) != (end / 2)) {
        if (beg % 2 == 0) res = std::max(tree[beg + 1], res);
        if (end % 2 == 1) res = std::max(tree[end - 1], res);
        beg /= 2; end /= 2;
    }

    return res;
}

uint quarry_top() {
    return tree[1];
}

void load() {
    uint n, m, k; std::cin >> n >> m >> k;

    std::vector<przystanek> P(k);
    for (int i = 0; i < k; i++) {
        auto& p = P[i]; std::cin >> p.x >> p.y >> p.p;
    }

    // skalujemy os y
    std::sort(P.begin(), P.end(), sort_przystankow_po_wysokosci{});

    uint val  = 0;
    uint skal = 0;
    for (int i = 0; i < k; i++) {
        uint y = P[i].y;

        if (y != val) {
            val = P[i].y;
            skal++;
        }

        P[i].y = skal;

        // zeskalowany przystanek wrzucamy w kolejke
        Q.push(P[i]);
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    load();

    while (Q.size()) {
        auto p = Q.top(); Q.pop();
        auto najlepszy_nizszy = quarry(p.y);
        push(p.y, najlepszy_nizszy + p.p);
    }

    std::cout << quarry_top();
}
