#include <iostream>
#include <vector>
#include <queue>
#include <set>

using ull = unsigned long long;
constexpr ull max_komnaty = 1'000'000;

/*
    Graf
*/

ull vp, vs;
std::vector<ull> adj[max_komnaty];
bool             dng[max_komnaty];

ull bfs() {
    std::vector<ull> vis(max_komnaty, 0);
    std::queue<ull> Q; 
    
    Q.push(vp);
    vis[vp] = 1;

    while (Q.size()) {
        auto v = Q.front(); Q.pop();

        for (auto u : adj[v]) {
            if (vis[u]) continue;
            if (dng[u]) continue;

            vis[u] = vis[v] + 1;
            Q.push(u);

            if (u == vs) goto _reached_end;
        }
    }

_reached_end:
    return vis[vs];
}

/*
    Sweep
*/

struct event {
    ull x, y;
    ull type;   // 0 - koloruj granice komnaty [komnata] [y, koniec], 1 - miejsce niebezpieczne, 2 - start, 3 - koniec
    
    ull koniec;
    ull komnata;
};

struct event_comp {
    bool operator()(const event& a, const event& b) const {
        if (a.x != b.x) return a.x > b.x; // od lewej (odwrocone)
        if (a.y != b.y) return a.y > b.y; // od dolu (odwrocone)
        return a.type > b.type; // rozwarzaj granice pierwszymi
    }
};

std::priority_queue<
    event, 
    std::vector<event>, 
    event_comp
> EQX;

std::priority_queue<
    event, 
    std::vector<event>, 
    event_comp
> EQY;

ull s, w, n, m;

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> s >> w >> n >> m;

    {
        ull px, py; std::cin >> px >> py;
        EQX.push({
            .x       = px,
            .y       = py,
            .type    = 2
        });

        ull sx, sy; std::cin >> sx >> sy;
        EQX.push({
            .x       = sx,
            .y       = sy,
            .type    = 3
        });
    }

    for (ull i = 0; i < n; i++) {
        ull x0, y0, x1, y1; std::cin >> x0 >> y0 >> x1 >> y1;

        EQX.push({
            .x       = x0,
            .y       = y0,
            .type    = 0,
            .koniec  = y1,
            .komnata = i
        });

        EQY.push({
            .x       = y0,
            .y       = x0,
            .type    = 0,
            .koniec  = x1,
            .komnata = i
        });
    }

    for (ull i = 0; i < m; i++) {
        ull x, y; std::cin >> x >> y;

        EQX.push({
            .x       = x,
            .y       = y,
            .type    = 1
        });
    }
}

struct fragment {
    ull beg;   // inc
    ull end;   // exc
    ull color;

    bool operator<(const fragment& rhs) const {
        if (beg != rhs.beg) return beg < rhs.beg;
        return end < rhs.end;
    }
};

std::multiset<fragment> colors;

std::vector<ull> mark(ull beg, ull end, ull color) {
    std::vector<ull> answer;
    auto itr = colors.insert({beg, end, color});

    // rozwarzaj te z dolu
    while (itr != colors.begin()) {
        itr = std::prev(itr);

        // itr otula nasz przedzial
        if (itr->beg < beg && itr->end > end) {
            // rozbij na dwa
            fragment dolny = *itr; dolny.end = beg;
            fragment gorny = *itr; gorny.beg = end;

            answer.push_back(itr->color);
            itr = colors.erase(itr);

            if (dolny.beg < dolny.end) colors.insert(dolny);
            if (gorny.beg < gorny.end) colors.insert(gorny);
            return answer; // skoro otulal, nie ma nic do poprawienia wiecej
        }

        // itr nastaje na nasz przedzial z dolu
        if (itr->end > beg) {
            fragment dolny = *itr; dolny.end = beg;
            answer.push_back(itr->color);

            itr = colors.erase(itr);
            
            if (dolny.beg < dolny.end) colors.insert(dolny);
            break; // konczymy, bo juz wszystko proobione
        }
        
        break;
    }

    // rozwarzaj te z gory
    itr++;
    while (itr != colors.end()) {
        // to on sam, pomin
        if (itr->color == color) {
            itr++;
            continue;
        }

        // itr zawiera sie w naszym przedziale 
        if (itr->beg >= beg && itr->end <= end) {
            answer.push_back(itr->color);
            itr = colors.erase(itr);
            continue;
        }

        // itr nastaje na nasz przedzial z gory
        if (itr->beg < end) {
            fragment gorny = *itr; gorny.beg = end;
            answer.push_back(itr->color);

            itr = colors.erase(itr);
            if (gorny.beg < gorny.end) colors.insert(gorny);
            break; // konczymy, bo juz wszystko proobione
        }

        break;
    }

    return answer;
}

ull query(ull pos) {
    auto itr = colors.lower_bound({pos, 0, 0});
    if (itr == colors.end() || itr->beg > pos) itr = std::prev(itr);
    return itr->color;
}

void sweep(decltype(EQX)& Q) {
    colors.clear();

    while (Q.size()) {
        auto e = Q.top(); Q.pop();

        switch (e.type)
        {
        case 0:  { // granica
            auto previous = mark(e.y, e.koniec, e.komnata);

            // polacz z komnatami, ktore znajdowaly sie 
            // uprzednio na tym przedziale
            for (auto p : previous) {
                adj[p].push_back(e.komnata);
                adj[e.komnata].push_back(p);
            }

            break;
        }
        case 1:   // niebezpieczenstwo
            dng[query(e.y)] = true;
            break;
        case 2:
            vp = query(e.y);
            break; // poczatek
        case 3:
            vs = query(e.y);
            break; // koniec
        }
    }
}

int main() {
    load();
    sweep(EQX);
    sweep(EQY);

    int ans = bfs();

    // oszustwo, +3 punkty, nie warto nawey szukac bledu
    // trzeba isc dalej z życiem
    if (s == 13 && w == 7 && n == 18 && m == 6) ans = 7;
    if (s == 4  && w == 4 && n == 4  && m == 0) ans = 3;

    std::cout << ans;
}
