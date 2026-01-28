#include <iostream>
#include <vector>

constexpr int max_v = 1e6;

// liczba nodow
int n;

// liczba zapytan
int m;

// mapowanie 
// indeks z zadania -> indeks drzewa
int in_tree_id[max_v];

// rodzic
// indeks zadania -> indeks zadania (bez zmian)
int parent[max_v];

// ciagly zakres numeracji w drzewie przedzialowym
// oznaczajacych pozycje dzieci noda w drzewie
// indeks zadania -> indeks drzewa
int child_segment_begin[max_v]; // inclusive
int child_segment_end[max_v];   // exclusive

// liczba strajkujacych dzieci
// po indeksach z zadania
int child_strikes[max_v];

// drzewo przedzialowe, do zglaszania strajkow
// zamiast w O(n) kazdemu dziecku dodawac strajkujacego sasiada (ojca)
// doliczamy +1 na caly przedzial dzieci
int tree[2 * max_v];

void make_tree_from_adj(const std::vector<std::vector<int>>& adj);

void load() {
    std::cin >> n;
    std::vector<std::vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        adj[x0].push_back(x1); adj[x1].push_back(x0);
    }

    make_tree_from_adj(adj);
    std::cin >> m;
}

void make_tree_from_adj(const std::vector<std::vector<int>>& adj) {
    std::vector<int> q = { 0 };
    decltype(q) nq;

    int in_tree_names_gen = 0;
    in_tree_id[0] = in_tree_names_gen++;

    while (q.size()) {
        for (int v : q) {
            // only parent
            if (adj[v].size() == 1 && v != 0) continue;

            child_segment_begin[v] = in_tree_names_gen;

            for (auto u : adj[v]) {
                if (u == parent[v]) continue;
                nq.push_back(u);

                parent[u] = v;
                in_tree_id[u] = in_tree_names_gen++;
            }

            child_segment_end[v] = in_tree_names_gen;
        }

        q.swap(nq);
        nq.clear();
    }
}

void add(int beg, int end, int change) {
    end--; // make end inclusive
    beg += max_v; end += max_v;

    tree[beg] += change;
    if (beg != end) tree[end] += change;

    while ((beg / 2) != (end / 2)) {
        if (beg % 2 == 0) tree[beg + 1] += change;
        if (end % 2 == 1) tree[end - 1] += change;
        beg /= 2; end /= 2;
    }
}

int quarry(int v) {
    int pos = in_tree_id[v] + max_v;
    int res = 0;

    while (pos != 0) {
        res += tree[pos];
        pos /= 2;
    }

    return res;
}

// wynik rozpadu Wielkiej Bajtocji
int answer   = 1;

// strajkujace nody
int striking = 0;

inline int calculate_change_amount(int v) {
    // all neighbours
    int neightbours = child_segment_end[v] - child_segment_begin[v];
    if (v != 0) neightbours++; // parent

    // striking neightbours
    int striking = quarry(v) + child_strikes[v];

    return neightbours - striking - 1;
}

void add_strike(int v) {
    striking++;

    if (v != 0) // have no parent
        child_strikes[parent[v]]++;

    if (child_segment_begin[v] != 0) // if have children
        add(child_segment_begin[v], child_segment_end[v], 1);

    answer += calculate_change_amount(v);
}

void erase_strike(int v) {
    striking--;

    if (v != 0) // have no parent
        child_strikes[parent[v]]--;

    if (child_segment_begin[v] != 0) // if have children
        add(child_segment_begin[v], child_segment_end[v], -1);

    answer -= calculate_change_amount(v);
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    load();

    for (int i = 0; i < m; i++) {
        int e; std::cin >> e;
        if (e > 0) add_strike(e - 1);
        else       erase_strike((-e) - 1);

        if (striking == n) std::cout << "0\n";
        else               std::cout << answer << '\n';
    }
}
