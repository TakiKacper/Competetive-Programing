#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

constexpr int max_n = 500000;

struct adj_item {
    int              owner;
    std::vector<int> elemenets;
};

adj_item adj[max_n];

struct adj_item_sort {
    bool operator()(const adj_item& l, const adj_item& b) const {
        return l.elemenets < b.elemenets;
    }
};

int main() {
    int n; std::cin >> n;

    for (int i = 0; i < n; i++) {
        int c; std::cin >> c;
        bool have_to_insert = true;

        adj[i].owner = i;
        
        for (int j = 0; j < c; j++) {
            int x; std::cin >> x; x--;

            if (x > i && have_to_insert) {
                have_to_insert = false;
                adj[i].elemenets.push_back(i);
            } 

            adj[i].elemenets.push_back(x);
        }

        if (have_to_insert) adj[i].elemenets.push_back(i);
    }

    std::sort(adj, adj + n, adj_item_sort{});

    std::vector<int> cities(n, 0);

    int city_counter = 0;
    int itr = 0;

    std::vector<int> unique_adjs;

    while (itr != n) {
        city_counter++;
        cities[adj[itr].owner] = city_counter;

        unique_adjs.push_back(itr);

        int next = itr + 1;
        
        while (next != n) {
            if (adj[itr].elemenets != adj[next].elemenets) break;
            cities[adj[next].owner] = city_counter;
            next++;
        }

        itr = next;
    }

    std::set<std::pair<int, int>> edges;

    for (auto& ua : unique_adjs) {
        int owner_city = cities[adj[ua].owner];
        
        for (auto& e : adj[ua].elemenets) {
            int other_city = cities[e];

            if (owner_city == other_city) continue;

            edges.insert({
                std::min(owner_city, other_city),
                std::max(owner_city, other_city)
            });
        }
    }

    if (city_counter == 1 && n != 1) {
        cities[0] = ++city_counter;
        edges.insert({cities[0], cities[1]});
    }

    std::cout << (city_counter) << '\n';
    for (int i = 0; i < n; i++) std::cout << cities[i] << ' ';
    std::cout << '\n';
    for (auto& p : edges) std::cout << p.first << ' ' << p.second << '\n';
}
