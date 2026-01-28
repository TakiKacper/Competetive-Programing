#include <iostream>
#include <vector>
#include <math.h>
#include <climits>

using ull = unsigned long long;

int n;
constexpr int max_n = 100000;

std::vector<int> adj[max_n];
std::vector<int> anty_adj[max_n];

ull tim[max_n];

ull wczesny_koniec  [max_n];
ull pozny_koniec    [max_n];

std::vector<int> indep;
std::vector<int> konce;

std::vector<int> topo_order;

ull ans;

bool topo_sort() {
    std::vector<int> queue = indep;
    std::vector<int> next;

    std::vector<int>  visit_count(n, 0);
    std::vector<bool> visited(n, false);

    while (queue.size()) {
        for (auto& v : queue) {
            visited[v] = true;

            for (auto& w : adj[v]) {
                auto& vc = visit_count[w]; vc++;

                // last enter
                if (vc == anty_adj[w].size()) {
                    next.push_back(w);
                }
                else if (vc > anty_adj[w].size()) {
                    return false; //cykl
                }
            }

            if (adj[v].size() == 0) konce.push_back(v);
        }
        
        queue.swap(next);
        for (auto& x : next) topo_order.push_back(x);
        next.clear();
    }

    for (auto v : visited) if (!v) return false;

    return true;
}

ull begin_end() {
    ull comp_time = 0;

    for (auto& i : indep) {
        wczesny_koniec[i] = tim[i];
    }

    for (auto& v : topo_order) {
        for (auto& w : adj[v]) {
            auto& val = wczesny_koniec[w];
            val       = std::max(val, wczesny_koniec[v] + tim[w]);
            comp_time = std::max(comp_time, val);
        }
    }

    return comp_time;
}

void end_begin() {
    for (int i = 0; i < n; i++) {
        pozny_koniec[i] = LONG_LONG_MAX;
    }
    
    for (auto& i : konce) {
        pozny_koniec[i] = (wczesny_koniec[i] + (ans - wczesny_koniec[i])); //znamy luzy koncow
    }

    for (int i = topo_order.size() - 1; i != - 1 ; i--) {
        auto& v = topo_order[i];

        //luz = czas najpozniejszej depedencji - czas wlasnej depedencji + luz targetu
        //w minimie z innych targetow

        ull luz_targetu = pozny_koniec[v] - wczesny_koniec[v];
        ull najpoz_dep  = wczesny_koniec[v] - tim[v];
        
        for (auto& w : anty_adj[v]) {
            ull wlasny  = wczesny_koniec[w];
            ull luz     = najpoz_dep - wlasny + luz_targetu;
            
            pozny_koniec[w] = std::min(pozny_koniec[w], wczesny_koniec[w] + luz);
        }
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int k; std::cin >> tim[i] >> k;

        if (k == 0) indep.push_back(i);

        for (int j = 0; j < k; j++) {
            int dep; std::cin >> dep; dep--;
            adj[dep].push_back(i);
            anty_adj[i].push_back(dep);
        }
    }

    bool dag = topo_sort();
    
    if (!dag) {
        std::cout << "CYKL\n";
        return 0;
    }
    
    ans = begin_end();
    std::cout << ans << '\n';
    end_begin();

    int q; std::cin >> q;
    
    while (q--) {
        int m, d; std::cin >> m >> d; m--;
        bool wydluzy = (d > pozny_koniec[m] - wczesny_koniec[m]);
        std::cout << (wydluzy ? "TAK\n" : "NIE\n");
    }
}
