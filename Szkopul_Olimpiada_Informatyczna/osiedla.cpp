#include <iostream>
#include <vector>
#include <cstring>

constexpr int max = 1'100'000;
int n, m;

// answer
int ans;
int dir[max]; // 0 - edge undirected, 
              // 1 - edge directed x0 to x1, 
              // 2 - edge directed x1 to x0

// undirected
struct edge {
    int  id;
    int  x0;
    int  x1;
};

bool             vis_ver[max];
bool             vis_edg[max];
edge             edg[max];
std::vector<int> adj[max];

// directed
bool             vis_ver_dir[max];
std::vector<int> adj_dir[max];
std::vector<int> adj_dir_rev[max];
std::vector<int> order;

void dfs_orient(int v) {
    if (vis_ver[v]) return;
    vis_ver[v] = true;

    for (auto eid : adj[v]) {
        if (vis_edg[eid]) continue;
        vis_edg[eid] = true;

        auto& e = edg[eid];

        bool cor = e.x0 == v;
        dir[eid] = cor ? 1 : 2;
        int u = cor ? e.x1 : e.x0;

        adj_dir[v].push_back(u);
        adj_dir_rev[u].push_back(v);

        dfs_orient(u);
    }
}

void dfs1(int v) {
    vis_ver_dir[v] = true;
    for (int u : adj_dir[v]) {
        if (!vis_ver_dir[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v) {
    vis_ver_dir[v] = true;
    for (int u : adj_dir_rev[v]) {
        if (!vis_ver_dir[u])
            dfs2(u);
    }
}

void kosaraju(int n) {
    // 1. DFS na oryginalnym grafie
    for (int i = 1; i <= n; i++)
        if (!vis_ver_dir[i])
            dfs1(i);

    // reset visited
    memset(vis_ver_dir, false, sizeof(vis_ver_dir));

    // 2. DFS na grafie odwróconym
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        if (!vis_ver_dir[v]) {
            dfs2(v);
            ans++; // nowa silnie spójna składowa
        }
    }
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        edge e; e.id = i;

        std::cin >> e.x0 >> e.x1; 
        e.x0--; e.x1--;
        edg[i] = e;

        adj[e.x0].push_back(i);
        adj[e.x1].push_back(i);
    }

    for (int v = 0; v < n; v++) {
        if (vis_ver[v]) continue;
        dfs_orient(v);
    }

    kosaraju(n);

    std::cout << ans << '\n';
    for (int i = 0; i < m; i++) {
        std::cout << (dir[i] == 1 ? '>' : '<');
    }
}
