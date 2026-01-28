#include <iostream>
#include <queue>
#include <vector>

constexpr int max_n = 500'000;
constexpr int two_n = 1 << 19; // max_n rounded to power of two

/*
    Topomapping:
        - class_beg[v]
        - class_end[v]
        - position[v]

    Wtedy 3 przedziały:
        - class_beg[v], position[v]
        - position[v],  position[u],
        - position[u],  class_end[u]
*/


int n, m;

// do set maybe
struct dag {
    std::vector<int> adj[max_n];
    int              ins[max_n];
};

dag nor;
dag rev;

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;

        nor.adj[x0].push_back(x1);
        nor.ins[x1]++;

        rev.adj[x1].push_back(x0);
        rev.ins[x0]++;
    }
}

// count of edges leading to given vertex
// from start of the graph
int dst_pre [max_n];
// from end of the graph
int dst_post[max_n];

// invalidates G.ins, its okay
std::vector<std::vector<int>> calc_dst(dag& G, int* dst) {
    std::vector<std::vector<int>> complex_topoorder;

    // vertex, dst
    std::vector<std::pair<int, int>> Q, nQ;
    for (int v = 0; v < n; v++) if (G.ins[v] == 0) Q.push_back({v, 0});

    while (Q.size()) {
        complex_topoorder.push_back({});

        for (auto p : Q) {
            complex_topoorder.back().push_back(p.first);

            for (auto u : G.adj[p.first]) {
                G.ins[u]--; dst[u] = std::max(dst[u], p.second + 1);
                if (!G.ins[u]) nQ.push_back({u, p.second + 1});
            }
        }
        
        Q.swap(nQ);
        nQ.clear();
    }

    return complex_topoorder;
}

int tpo_pos    [max_n];
int tpo_min_pos[max_n];
int tpo_max_pos[max_n];

void make_topomapping(std::vector<std::vector<int>>& ctpo) {
    int iter = 0;
    int min  = 0;
    int max  = 0;

    for (auto& set : ctpo) {
        max += set.size();

        for (auto v : set) {
            tpo_pos[v]     = iter;
            tpo_min_pos[v] = min;
            tpo_max_pos[v] = max - 1;

            iter++;
        }

        min += set.size();
    }
}

int tree[two_n * 2];

void add(int beg, int end, int val) {
    beg += two_n;
    end += two_n;

    while (beg <= end) {
        if (beg % 2 == 1) tree[beg++] = std::max(tree[beg], val);
        if (end % 2 == 0) tree[end--] = std::max(tree[end], val);
        beg /= 2; end /= 2;
    }
}

int query(int pos) {
    pos += two_n;
    int len = 0;

    while (pos != 0) {
        len = std::max(len, tree[pos]);
        pos /= 2;
    }

    return len;
}

int dst_byp[max_n];

void calculate_bypass() {
    for (int v = 0; v < n; v++) {
        for (int u : nor.adj[v]) {
            int length = dst_pre[v] + 1 + dst_post[u];

            add(
                tpo_min_pos[v], 
                tpo_pos[v] - 1, 
                length
            );

            add(
                tpo_pos[v] + 1, 
                tpo_pos[u] - 1, 
                length
            );

            add(
                tpo_pos[u] + 1, 
                tpo_max_pos[u], 
                length
            );
        }
    }

    for (int v = 0; v < n; v++) {
        dst_byp[v] = query(tpo_pos[v]);
    }
}

int main() {
    load();

    auto ctpo = calc_dst(nor, dst_pre);
    calc_dst(rev, dst_post);

    make_topomapping(ctpo);
    calculate_bypass();

    int vert = -1;
    int path = __INT_MAX__;

    for (int v = 0; v < n; v++) {
        auto npath = std::max(
            dst_byp[v], std::max(dst_pre[v] - 1, dst_post[v] - 1)
        );

        if (npath < path) {
            path = npath;
            vert = v;
        }
    }

    std::cout << (vert + 1) << ' ' << path;
}
