#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using ll = long long;

struct edge {
    int tar;
    int dst;
};

struct question {
    int x0, x1;
    int k, idx;
};

constexpr int max_n = 100;
constexpr int max_q = 10'000;
constexpr ll  INF   = 1e18;

std::vector<edge> G[max_n];
question          Q[max_q];
ll                A[max_q];
std::vector<ll>   R;

void djk(int x0, int x1, int k) {
    R.clear();

    std::priority_queue<
        std::pair<ll,int>,
        std::vector<std::pair<ll,int>>,
        std::greater<std::pair<ll,int>>
    > dq;

    std::vector<int> count(max_n, 0);

    dq.push({0, x0});

    while (!dq.empty()) {
        auto [dist, v] = dq.top(); dq.pop();
        count[v]++;

        if (v == x1) {
            R.push_back(dist);
            if (R.size() == k) break;
        }

        if (count[v] <= k) {
            for(auto [to, w] : G[v]) {
                dq.push({dist + w, to});
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);

    int n, m; std::cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x0, x1, d; std::cin >> x0 >> x1 >> d; x0--; x1--;
        G[x0].push_back({x1, d});
    }

    int q; std::cin >> q;
    for (int i = 0; i < q; i++) {
        int x0, x1, k; std::cin >> x0 >> x1 >> k; x0--; x1--;
        if (x0 == x1) k++;
        Q[i] = {x0, x1, k, i};
    }

    std::sort(Q, Q + q, [](const question& a, const question& b){
        if (a.x0 != b.x0) return a.x0 < b.x0;
        if (a.x1 != b.x1) return a.x1 < b.x1;
        return a.k < b.k;
    });

    int beg = 0; // inc
    int itr = 0; // exc

    while (beg != q) {
        while (itr != q && Q[beg].x0 == Q[itr].x0 && Q[beg].x1 == Q[itr].x1) itr++;
        djk(Q[beg].x0, Q[beg].x1, Q[itr - 1].k);

        while (beg != itr) {
            int idx = Q[beg].k - 1;
            A[Q[beg].idx] = R.size() > idx ? R[idx] : -1;
            beg++;
        }
    }

    for (int i = 0; i < q; i++) std::cout << A[i] << '\n';
}
