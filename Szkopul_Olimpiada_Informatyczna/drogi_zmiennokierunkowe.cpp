#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

constexpr int max_n = 500'000;
constexpr int max_m = 1'000'000;
int n, m;

bool vis[max_n];

std::vector<int>    adj_nor[max_n];
std::vector<int>    adj_rev[max_n];
std::pair<int, int> edg_nor[max_m];

void load() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        adj_nor[x0].push_back(x1);
        adj_rev[x1].push_back(x0);
        edg_nor[i] = {x0, x1};
    }
}

void dfs(int v) {
    vis[v] = true;
    for (int u : adj_nor[v]) if (!vis[u]) dfs(u);
    for (int u : adj_rev[v]) if (!vis[u]) dfs(u);
}

bool is_connected() {
    std::memset(vis, false, sizeof(vis));
    dfs(0); // start from node 0 (or any node)

    for (int i = 0; i < n; i++) {
        if (!vis[i]) return false;
    }
    return true;
}

int              scc_count;
int              vertex_to_scc[max_n];
std::vector<int> scc_to_vertex[max_n];

// temp mem
std::vector<int> order;

void kosaraju_dfs_1(int v) {
    vis[v] = true;
    for (int u : adj_nor[v]) if (!vis[u]) kosaraju_dfs_1(u);
    order.push_back(v);
}

void kosaraju_dfs_2(int v) {
    vis[v] = true; 

    vertex_to_scc[v] = scc_count;
    scc_to_vertex[scc_count].push_back(v);

    for (auto u : adj_rev[v]) if (!vis[u]) kosaraju_dfs_2(u);
}

void kosaraju() {
    order.clear();

    memset(vis, false, sizeof(vis));
    for (int v = 0; v < n; v++) if (!vis[v]) kosaraju_dfs_1(v);

    memset(vis, false, sizeof(vis));
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        auto v = order[i];
        if (!vis[v]) {
            kosaraju_dfs_2(v);
            scc_count++;
        }
    }
}

struct dag {
    int           ver;
    int           in [max_n];
    std::set<int> adj[max_n];
};

dag nor_dag;
dag rev_dag;

void make_dag(dag* target, bool nor) {
    target->ver = scc_count;

    for (auto e : edg_nor) {
        int x0 = vertex_to_scc[e.first]; 
        int x1 = vertex_to_scc[e.second];

        if (x0 == x1) continue;
        if (!nor) std::swap(x0, x1);

        bool success = target->adj[x0].insert(x1).second;
        if (success) target->in[x1]++;
    }
}

bool good_nor[max_n];
bool good_rev[max_n];

void find_topo_order(std::vector<int>& topoorder, dag* target) {
    std::queue<int> Q;
    for (int v = 0; v < target->ver; v++) if (target->in[v] == 0) Q.push(v);

    while (Q.size()) {
        auto v = Q.front();
        topoorder.push_back(v);
        Q.pop();

        for (auto u : target->adj[v]) {
            target->in[u]--;
            if (target->in[u] == 0) Q.push(u);
        }
    }
}

void mark_good(dag* target, std::vector<int>& topoorder, bool* good) {
    // najdajmy indeksy wiercholkom
    std::vector<int> topoidx(target->ver);
    for (int i = 0; i < target->ver; i++) topoidx[topoorder[i]] = i;

    // najmniejszy indeks wiercholka do ktorego prowadzi krawedz z wiercholka o indeksie i
    std::vector<int> r(target->ver);
    for (int i = 0; i < target->ver; i++) { 
        auto v = topoorder[i];
        r[i] = target->ver + 1;
        for (auto u : target->adj[v]) r[i] = std::min(r[i], topoidx[u]);
    }

    int bad_till_pos = 0;
    for (int i = 0; i < target->ver; i++) {
        int v = topoorder[i];
        if (i >= bad_till_pos) {
            for (auto u : scc_to_vertex[v]) good[u] = true;
        }
        bad_till_pos = std::max(bad_till_pos, r[i]);
    }
}

int main() {
    load();

    if (!is_connected()) {
        std::cout << 0;
        return 0;
    }

    kosaraju();

    make_dag(&nor_dag, true);
    make_dag(&rev_dag, false);

    std::vector<int> tpo;
    find_topo_order(tpo, &nor_dag);

    mark_good(&nor_dag, tpo, good_nor);

    std::reverse(tpo.begin(), tpo.end());
    mark_good(&rev_dag, tpo, good_rev);

    std::vector<int> ans;
    for (int v = 0; v < n; v++) if (good_nor[v] && good_rev[v]) ans.push_back(v + 1);
    
    std::cout << ans.size() << '\n';
    for (int v : ans) std::cout << v << ' ';
}
